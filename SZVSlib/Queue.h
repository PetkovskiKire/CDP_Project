#ifndef SZVSLIB_QUEUE_H
#define SZVSLIB_QUEUE_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include <OSAPI/Process/OSAPIThread.h>
#include <CDPSystem/Base/CDPProperty.h>
#include <OSAPI/Process/OSAPIEvent.h>

namespace SZVSlib {

class Queue : public CDPComponent, public OSAPIThread
{
public:
    Queue();
    ~Queue() override;

    virtual void Create(const char* fullName) override;
    virtual void CreateModel() override;
    virtual void Configure(const char* componentXML) override;
    void ProcessNull() override;
    virtual void Activate() override;
    virtual void Suspend() override;
protected:
    bool VnesiVoImePrezimeQueue(CDP::StudioAPI::CDPVariantValue& validateValue,CDPPropertyBase* pProperty);
    bool VnesiVoSelektiranoQueue(CDP::StudioAPI::CDPVariantValue& validateValue,CDPPropertyBase* pProperty);
    virtual void Main() override;

    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
    OSAPIEvent m_event;

    CDPSignal<std::string> ImePrezimeSignal;
    CDPSignal<std::string> SelektiranoSignal;
    CDPSignal<bool> ActiveDataBase;
    CDPProperty<std::string> ImePrezimeQueue;
    CDPProperty<std::string> SelektiranoQueue;

    std::string QueueImePrezime;
    std::string QueueSelektirano;
};

} // namespace SZVSlib

#endif
