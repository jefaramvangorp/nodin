#ifndef APP_FACTORIES_NODEFACTORYDELEGATE_H_
#define APP_FACTORIES_NODEFACTORYDELEGATE_H_

// STD.
#include <map>
#include <string>
#include <vector>

// Forward declarations.
class Node;

class NodeFactoryDelegate
{
public:
    virtual ~NodeFactoryDelegate() {}

    virtual std::string nodeType() const = 0;
    virtual std::vector<std::string> requiredParameters() = 0;
    virtual bool isValidParameter(const std::string& parameter, const std::string& value) const = 0;
    virtual Node* createNode(const std::string& id, const std::map<std::string, std::string>& parameters) = 0;
};

#endif // APP_FACTORIES_NODEFACTORYDELEGATE_H_
