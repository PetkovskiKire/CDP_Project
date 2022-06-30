#ifndef SZVSLIB_DATABASE_H
#define SZVSLIB_DATABASE_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include <OSAPI/Process/OSAPIThread.h>
#include <CDPSystem/Base/CDPProperty.h>
#include <OSAPI/Process/OSAPIEvent.h>

#include <CDP2SQL/CDP2SQL.h>

namespace SZVSlib {

class DataBase : public CDPComponent, public OSAPIThread
{
public:
    DataBase();
    ~DataBase() override;

    virtual void Create(const char* fullName) override;
    virtual void CreateModel() override;
    virtual void Configure(const char* componentXML) override;
    void ProcessNull() override;
    virtual void Activate() override;
    virtual void Suspend() override;
protected:
    bool VnesiVoQueueIme(CDP::StudioAPI::CDPVariantValue& ,CDPPropertyBase* pProperty);
    bool VnesiVoQueueSelektirano(CDP::StudioAPI::CDPVariantValue& ,CDPPropertyBase* pProperty);
    virtual void Main() override;
    void VnesiVoBaza();
    void ProcitajOdBaza();

    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
    OSAPIEvent m_event;

    CDPProperty<std::string> VnesiImePrezime;
    CDPProperty<std::string> VnesiSelektirano;
    CDPProperty<std::string> OutPut;

    std::string QueueImePrezime;
    std::string QueueSelektirano;
    CDP2SQL::Statement st;
    CDP2SQL::Statement st2;
};

} // namespace SZVSlib

#endif
