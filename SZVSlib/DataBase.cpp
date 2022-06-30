#include "DataBase.h"
#include <OSAPI/Process/OSAPISemaphore.h>

#include <CDP2SQL/CDP2SQL.h>
#include <CppSQLite3/SQLite3Factory.h>

#include <sstream>

using namespace SZVSlib;
using namespace CDP2SQL;

/*!
  \class SZVSlib::DataBase
  \inmodule SZVSlib

  \section1 Usage

  Add documentation for DataBase here.
*/

DataBase::DataBase()
{
}

DataBase::~DataBase()
{
}

void DataBase::Create(const char* fullName)
{
    CDPComponent::Create(fullName);

    VnesiImePrezime.Create("VnesiImePrezime",this,CDPPropertyBase::e_Element,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)&DataBase::VnesiVoQueueIme);
    VnesiSelektirano.Create("VnesiSelektirano",this,CDPPropertyBase::e_Element,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)&DataBase::VnesiVoQueueSelektirano);
    OutPut.Create("OutPut",this,CDPPropertyBase::e_Element,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);

}

void DataBase::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&DataBase::ProcessNull, "Initial Null state");
}

void DataBase::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
    VnesiImePrezime.Connect("DataBase.ImePrezimeQueue");
    VnesiSelektirano.Connect("DataBase.SelektiranoQueue");
}

void DataBase::ProcessNull()
{

}

void DataBase::Activate()
{
    CDPComponent::Activate();
    // Start the Main() thread with name of the component and normal priority:
    Start(CDPTHREAD_PRIORITY_NORMAL,ShortName());
}

void DataBase::Suspend()
{
    CDPComponent::Suspend();
    Stop();           // set Stop flag
    m_event.Set();    // set event so that Wait in Main() completes.
    Delete();         // will block until thread is no longer running (for max. 2 seconds)
}



/*!
  \internal
  \brief Main thread function, runs asynchronously from state-machine.

  Note that it is not safe to access cdp signals, parameters, alarms etc. from a thread.
  The helper RunInComponentThread() and the component member access mutex ( GetMemberAccessMutex() )
  can be used to safely access cdp objects. As in the process functions, any timeconsuming processing
  performed while the member access mutex is locked may impact the scheduling of other components running
  at the same priority as this component.
*/
void DataBase::Main()
{
    try
    {
        Database db(SQLite3Factory().Create(), "database.db");
        db.Execute("CREATE TABLE IF NOT EXISTS VRABOTENI (Ime TEXT, Selektirano TEXT, timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP);");
        st.SetDatabase(db);
        st.Compile("INSERT INTO VRABOTENI (Ime, Selektirano) VALUES (?, ?)");

        while (!Stopped())
        {
          //  if(QueueSelektirano.compare("") && QueueImePrezime.compare("")){
                VnesiVoBaza();
                ProcitajOdBaza();
           // }

            m_event.Wait();
            m_event.Reset();

        }
    }
    catch (const SQLException& e)
    {
        CDPMessage("Error in ChatComponent::Main(): %s\n", e.GetFormattedMessage().c_str());

    }
}

/*!
  \internal
  \brief Shows how to safely access cdp objects using the memberaccess mutex
*/

void DataBase::VnesiVoBaza()
{
    OSAPIMutexLocker locker(GetMemberAccessMutex(), "DataBase::VnesiVoBaza()");
    std::istringstream messageStreamIme(QueueImePrezime); // Lock mutex when accessing CDPProperties
    std::istringstream messageStreamSelektirano(QueueSelektirano); // Lock mutex when accessing CDPProperties
    QueueImePrezime.clear();
    QueueSelektirano.clear();
    locker.Release(); // Release mutex before "slow" database access

    std::string Ime;
    std::string Selektirano;


        while(std::getline(messageStreamIme, Ime))
        {
            std::getline(messageStreamSelektirano, Selektirano);
            CDPMessage("%s\n", Ime.c_str());
            CDPMessage("%s\n", Selektirano.c_str());
            st.Bind(1, Ime);
            st.Bind(2, Selektirano);
            st.Execute();
        }

        Database db2(SQLite3Factory().Create(), "database.db");
        st2.SetDatabase(db2);
        st2.Compile("DELETE FROM VRABOTENI WHERE trim(Ime) = '';");
        st2.Execute();

}

void DataBase::ProcitajOdBaza()
{
    Database db(SQLite3Factory().Create(), "database.db");
    Query q(db, "SELECT Ime, Selektirano, timestamp FROM VRABOTENI ORDER BY timestamp DESC LIMIT 100;");
    std::string messages;
    while (!q.IsEof())
    {
        messages = q.FieldValueStr(0) + "," + q.FieldValueStr(1) + "," + q.FieldValueStr(2) + ","+ messages;
        q.NextRow();
    }
    OSAPIMutexLocker locker(GetMemberAccessMutex(), "DataBase::ReadDataBase()");
    OutPut = messages; // Lock mutex when accessing CDPProperties
}

bool DataBase::VnesiVoQueueIme(CDP::StudioAPI::CDPVariantValue& validateValue,CDPPropertyBase*)
{
    QueueImePrezime = validateValue.GetConvertedValue<std::string>();
    //QueueImePrezime += '\n';
    m_event.Set(); // Triggers Main thread causing it to write to database
    return false;
}

bool DataBase::VnesiVoQueueSelektirano(CDP::StudioAPI::CDPVariantValue& validateValue,CDPPropertyBase*)
{
    QueueSelektirano = validateValue.GetConvertedValue<std::string>();
    //QueueSelektirano += '\n';
    //m_event.Set(); // Triggers Main thread causing it to write to database
    return false;
}
