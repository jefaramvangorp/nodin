#ifndef APP_NODE_H_
#define APP_NODE_H_

#include <string>

class Node
{
public:
    Node();
    Node(const std::string &id, const std::string& name, int numInputs, int numOutputs);

    const std::string& id() const { return id_; }
    const std::string& name() const { return name_; }

    int numInputs() const { return num_inputs_; }
    int numOutputs() const { return num_outputs_; }

private:

    std::string id_;
    std::string name_;
    int num_inputs_;
    int num_outputs_;
};

#endif // APP_NODE_H_
