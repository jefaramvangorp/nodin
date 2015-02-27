#ifndef APP_FACTORIES_NODEFACTORY_H_
#define APP_FACTORIES_NODEFACTORY_H_

// STD.
#include <map>
#include <vector>
#include <string>

// Forward declarations.
class Node;
class NodeFactoryDelegate;

class NodeFactory
{
public:

    NodeFactory(NodeFactoryDelegate* delegate);
    ~NodeFactory();

    std::string nodeType() const;
    const std::vector<std::string>& requiredParameters() const { return required_parameters_; }
    void setParameterValue(const std::string& parameter, const std::string& value);

    Node* createNode(const std::string& id);

private:

    bool allParametersAreValid();

    NodeFactoryDelegate* delegate_;
    std::vector<std::string> required_parameters_;
    std::map<std::string, std::string> parameters_;
};

#endif // APP_FACTORIES_NODEFACTORY_H_
