#ifndef APP_FACTORIES_NODEFACTORY_H_
#define APP_FACTORIES_NODEFACTORY_H_

// STD.
#include <map>
#include <vector>
#include <string>

// Forward declarations.
class Node;

class NodeFactory
{
public:

    class Delegate
    {
    public:
        virtual ~Delegate() {}
        virtual std::vector<std::string> requiredParameters() = 0;
        virtual bool isValidParameter(const std::string& parameter, const std::string& value) const = 0;
        virtual Node* createNode(const std::map<std::string, std::string>& parameters) = 0;
    };

    NodeFactory(Delegate* delegate);
    ~NodeFactory();

    const std::vector<std::string>& requiredParameters() const { return required_parameters_; }
    void setParameterValue(const std::string& parameter, const std::string& value);

    Node* createNode();

private:

    bool allParametersAreValid();

    Delegate* delegate_;
    std::vector<std::string> required_parameters_;
    std::map<std::string, std::string> parameters_;
};

#endif // APP_FACTORIES_NODEFACTORY_H_
