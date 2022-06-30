/**
SZVSlibBuilder header file.
*/

#ifndef SZVSLIB_SZVSLIBBUILDER_H
#define SZVSLIB_SZVSLIBBUILDER_H

#include <CDPSystem/Application/CDPBuilder.h>

namespace SZVSlib {

class SZVSlibBuilder : public CDPBuilder
{
public:
    SZVSlibBuilder(const char* libName);
    CDPComponent* CreateNewComponent(const std::string& type) override;
    CDPBaseObject* CreateNewCDPOperator(const std::string& modelName,const std::string& type,const CDPPropertyBase* inputProperty) override;
    CDPObject* CreateNewObject(const std::string& type) override;
    CDP::StudioAPI::CDPNode* CreateNewCDPNode(const std::string& type) override;
};

}

#endif
