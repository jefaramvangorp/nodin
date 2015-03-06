#ifndef APP_FACTORIES_PRINTERNODEFACTORYDELEGATE_H_
#define APP_FACTORIES_PRINTERNODEFACTORYDELEGATE_H_

// Includes.
#include "App/Factories/NodeFactoryDelegate.h"

class PrinterNodeFactoryDelegate : public NodeFactoryDelegate
{
public:
    PrinterNodeFactoryDelegate();
    virtual ~PrinterNodeFactoryDelegate();

    virtual std::string nodeType() const;
    virtual std::vector<std::string> requiredParameters();
    virtual bool isValidParameter(const std::string& parameter, const std::string& value) const;
    virtual Node* createNode(const std::string& id, const std::map<std::string, std::string>& parameters);
};

#endif // APP_FACTORIES_PRINTERNODEFACTORYDELEGATE_H_
