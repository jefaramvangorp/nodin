
// Includes.
#include "Node.h"

// STD.
#include <sstream>


struct Connector
{
    Node* node_;
    int index_;

    Connector(Node* node, int index) : node_(node), index_(index) {}
};


Node::Node(const std::string& id, const std::string &name, int numInputs, int numOutputs)
    : id_(id)
    , name_(name)
    , num_inputs_(numInputs)
    , num_outputs_(numOutputs)
    , inputs_(new Connector*[num_inputs_])
    , outputs_(new Connector*[num_outputs_])
{
    memset(inputs_, 0, num_inputs_ * sizeof(Connector*));
    memset(outputs_, 0, num_outputs_ * sizeof(Connector*));
}

Node::~Node()
{
    for (int i = 0; i < num_inputs_; ++i)
    {
        delete inputs_[i];
    }

    for (int i = 0; i < num_outputs_; ++i)
    {
        delete outputs_[i];
    }

    delete [] inputs_;
    delete [] outputs_;
}

void Node::setErrorMessage(const std::string &errorMessage)
{
    std::ostringstream stream;
    stream << "Node (" << name_ << ", " << id_ << ") : " << errorMessage;
    error_message_ = stream.str();
}

bool Node::connectOutputTo(int outputIndex, Node *node, int inputIndex)
{
    if (outputIndex >= 0 && outputIndex < num_outputs_)
    {
        outputs_[outputIndex] = new Connector(node, inputIndex);
        return true;
    }
    else
    {
        setErrorMessage("Output index out of bounds.");
        return false;
    }
}

bool Node::connectInputTo(int inputIndex, Node *node, int outputIndex)
{
    if (inputIndex >= 0 && inputIndex < num_inputs_)
    {
        inputs_[inputIndex] = new Connector(node, outputIndex);
        return true;
    }
    else
    {
        setErrorMessage("Input index out of bounds.");
        return false;
    }
}

bool Node::valueAtOutput(int index, std::string* output)
{
    if (index >= 0 && index < num_outputs_)
    {
        std::vector<std::string> inputs;
        bool ok = retrieveInputs(&inputs);

        return ok && computeValueAtOutput(inputs, index, output);
    }
    else
    {
        setErrorMessage("Output index out of bounds.");
        return false;
    }
}

bool Node::executeAsTerminal()
{
    std::vector<std::string> inputs;
    bool ok = retrieveInputs(&inputs);
    return ok && computeValueAtOutput(inputs, 0, 0);
}

bool Node::retrieveInputs(std::vector<std::string> *inputs)
{
    for (int i = 0; i < num_inputs_; ++i)
    {
        if (inputs_[i] == 0)
        {
            setErrorMessage("Not all inputs are connected.");
            return false;
        }
    }

    for (int i = 0; i < num_inputs_; ++i)
    {
        Connector* c = inputs_[i];
        std::string value;
        bool ok = c->node_->valueAtOutput(c->index_, &value);
        if (ok)
        {
            inputs->push_back(value);
        }
        else
        {
            setErrorMessage("Node failure for input[i]");
            return false;
        }
    }

    return true;
}

