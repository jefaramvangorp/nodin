#ifndef APP_NODES_NODE_H_
#define APP_NODES_NODE_H_

// STD.
#include <string>
#include <vector>

// Forward declarations.
struct Connector;

class Node
{
public:
    virtual ~Node();

    const std::string& id() const { return id_; }
    const std::string& name() const { return name_; }

    int numInputs() const { return num_inputs_; }
    int numOutputs() const { return num_outputs_; }
    const std::string& errorMessage() const { return error_message_; }
    bool isTerminal() const { return num_outputs_ == 0; }

    bool connectOutputTo(int outputIndex, Node* node, int inputIndex);
    bool connectInputTo(int inputIndex, Node* node, int outputIndex);
    bool valueAtOutput(int index, std::string *output);
    bool executeAsTerminal();

protected:

    Node(const std::string &id, const std::string& name, int numInputs, int numOutputs);

    void setErrorMessage(const std::string& errorMessage);

private:

    virtual bool computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output) = 0;

    bool retrieveInputs(std::vector<std::string>* inputs);

    std::string id_;
    std::string name_;
    int num_inputs_;
    int num_outputs_;
    Connector** inputs_;
    Connector** outputs_;
    std::string error_message_;

};

#endif // APP_NODES_NODE_H_
