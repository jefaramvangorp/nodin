#ifndef APP_BOUNDARY_NODEPROXY_H_
#define APP_BOUNDARY_NODEPROXY_H_

// STD.
#include <string>

// Forward declarations.
class Node;

class NodeProxy
{
public:
    NodeProxy(const Node* node);

    const std::string& id() const;
    const std::string& name() const;
    int numInputs() const;
    int numOutputs() const;
    std::string inputName(int index) const;
    std::string outputName(int index) const;
    bool isSource() const;
    bool isTerminal() const;

private:
    const Node* node_;
};

#endif // APP_BOUNDARY_NODEPROXY_H_
