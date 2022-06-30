#ifndef SZVSLIB_BUTTONS_H
#define SZVSLIB_BUTTONS_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

namespace SZVSlib {

class Buttons : public CDPComponent
{
public:
    Buttons();
    ~Buttons() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    CDPSignal<std::string> Selektirano;
    CDPSignal<bool> Pauza;
    CDPSignal<bool> SluzbenIzlez;
    CDPSignal<bool> PrivatenIzlez;
    CDPSignal<bool> Izlez;
    CDPSignal<bool> Vlez;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;

    CDPTimer myTimer;
    CDPSignal<std::string> ImePrezimeOutput;
    CDPSignal<std::string> ImePrezimeInput;
    std::string ImePrezime;
    std::string pomni;
    bool flag;
    bool vlez;
};

} // namespace SZVSlib

#endif
