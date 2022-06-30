#ifndef SZVSLIB_COPY_H
#define SZVSLIB_COPY_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

namespace SZVSlib {

class Copy : public CDPComponent
{
public:
    Copy();
    ~Copy() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    CDPSignal<std::string> Output1;
    CDPSignal<std::string> Output2;
    CDPSignal<std::string> Input;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace SZVSlib

#endif
