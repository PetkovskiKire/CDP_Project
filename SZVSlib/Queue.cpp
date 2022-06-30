#include "Queue.h"
#include <OSAPI/Process/OSAPISemaphore.h>

#include <sstream>

using namespace SZVSlib;
using namespace std;


/*!
  \class SZVSlib::Queue
  \inmodule SZVSlib

  \section1 Usage

  Add documentation for Queue here.
*/

Queue::Queue()
{
}

Queue::~Queue()
{
}

void Queue::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    ImePrezimeSignal.Create("ImePrezimeSignal",this);
    SelektiranoSignal.Create("SelektiranoSignal",this);
    ActiveDataBase.Create("ActiveDataBase",this);
    ImePrezimeQueue.Create("ImePrezimeQueue",this,CDPPropertyBase::e_Element,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)&Queue::VnesiVoImePrezimeQueue);
    SelektiranoQueue.Create("SelektiranoQueue",this,CDPPropertyBase::e_Element,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)&Queue::VnesiVoSelektiranoQueue);


}

void Queue::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&Queue::ProcessNull, "Initial Null state");
}

void Queue::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);

    ImePrezimeQueue.Connect("GUIApp.Copy.Output2");
    SelektiranoQueue.Connect("GUIApp.Copy1.Output2");
}

void Queue::ProcessNull()
{

}

void Queue::Activate()
{
    CDPComponent::Activate();
    // Start the Main() thread with name of the component and normal priority:
    Start(CDPTHREAD_PRIORITY_NORMAL,ShortName());
}

void Queue::Suspend()
{
    CDPComponent::Suspend();
    Stop();           // set Stop flag
    m_event.Set();    // set event so that Wait in Main() completes.
    Delete();         // will block until thread is no longer running (for max. 2 seconds)
}

void Queue::Main()
{
    while(!Stopped())
    {
        if(ActiveDataBase)
        {
            OSAPIMutexLocker locker(GetMemberAccessMutex(), "Queue::Main()");
            SelektiranoSignal.SetVariantValue(QueueSelektirano);
            QueueSelektirano.clear();
            ImePrezimeSignal.SetVariantValue(QueueImePrezime);
            QueueImePrezime.clear();
            locker.Release();
            //CDPMessage("Vleze vo ActiveDataBase\n");
        }
        else
        {
            m_event.Wait();
        }
        m_event.Reset();
    }
}

/*!
  \internal
  \brief Shows how to safely access cdp objects using the memberaccess mutex
*/
bool Queue::VnesiVoImePrezimeQueue(CDP::StudioAPI::CDPVariantValue& validateValue,CDPPropertyBase* )
{
    std::string str = validateValue.GetConvertedValue<std::string>();
    std::string pom = "----------                      ";
    if(str.compare(pom))
    {
        QueueImePrezime += str;
        QueueImePrezime += '\n';
        m_event.Set(); // Triggers Main thread causing it to write to database
        CDPMessage("Ime Prezime Queue \n %s", QueueImePrezime.c_str());
    }
    return false;
}

bool Queue::VnesiVoSelektiranoQueue(CDP::StudioAPI::CDPVariantValue& validateValue,CDPPropertyBase* )
{
    std::string str = validateValue.GetConvertedValue<std::string>();
    std::string pom = "----------";
    if(str.compare(pom))
    {
        QueueSelektirano += str;
        QueueSelektirano += '\n';
        CDPMessage("Slektirano Queue \n %s", QueueSelektirano.c_str());
    }
    return false;
}
