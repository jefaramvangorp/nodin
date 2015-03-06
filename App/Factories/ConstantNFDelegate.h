#ifndef APP_FACTORIES_CONSTANTNFDELEGATE_H_
#define APP_FACTORIES_CONSTANTNFDELEGATE_H_

// Includes.
#include "App/Factories/NodeFactoryDelegate.h"

class ConstantNFDelegate : public NodeFactoryDelegate
{
public:
    ConstantNFDelegate();
    virtual ~ConstantNFDelegate();

    virtual std::string nodeType() const;
    virtual std::vector<std::string> requiredParameters();
    virtual bool isValidParameter(const std::string& parameter, const std::string& value) const;
    virtual Node* createNode(const std::string& id, const std::map<std::string, std::string>& parameters);
};

#endif // APP_FACTORIES_CONSTANTNFDELEGATE_H_
