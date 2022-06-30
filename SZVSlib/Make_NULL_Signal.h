#ifndef SZVSLIB_MAKE_NULL_SIGNAL_H
#define SZVSLIB_MAKE_NULL_SIGNAL_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

namespace SZVSlib {

class Make_NULL_Signal : public CDPComponent
{
public:
    Make_NULL_Signal();
    ~Make_NULL_Signal() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace SZVSlib

#endif
