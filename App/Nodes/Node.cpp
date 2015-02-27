
// Includes.
#include "Node.h"

// STD.
#include <sstream>


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

Connector *Node::inputConnector(int index) const
{
    if (index >= 0 && index < num_inputs_)
    {
        return inputs_[index];
    }
    else
    {
        return 0;
    }
}

Connector *Node::outputConnector(int index) const
{
    if (index >= 0 && index < num_outputs_)
    {
        return outputs_[index];
    }
    else
    {
        return 0;
    }
}

void Node::setErrorMessage(const std::string &errorMessage)
{
    std::ostringstream stream;
    stream << "Node (" << name_ << ", " << id_ << ") : " << errorMessage;
    error_message_ = stream.str();
}

bool Node::disconnectInput(int index)
{
    if (index >= 0 && index < num_inputs_)
    {
        delete inputs_[index];
        inputs_[index] = nullptr;
        return true;
    }
    else
    {
        setErrorMessage("Input index out of bounds.");
        return false;
    }
}

bool Node::disconnectOutput(int index)
{
    if (index >= 0 && index < num_outputs_)
    {
        delete outputs_[index];
        outputs_[index] = nullptr;
        return true;
    }
    else
    {
        setErrorMessage("Output index out of bounds.");
        return false;
    }
}

bool Node::connectInputTo(int index, Node *outputNode, int outputIndex)
{
    if (index >= 0 && index < num_inputs_)
    {
        if (inputs_[index] != nullptr)
        {
            setErrorMessage("Input[i] is already connected to a node.");
            return false;
        }
        else
        {
            inputs_[index] = new Connector(outputNode, outputIndex);
            return true;
        }
    }
    else
    {
        setErrorMessage("Input index out of bounds.");
        return false;
    }
}

bool Node::connectOutputTo(int index, Node *inputNode, int inputIndex)
{
    if (index >= 0 && index < num_outputs_)
    {
        if (outputs_[index] != nullptr)
        {
            setErrorMessage("Output[i] is already connected to a node.");
            return false;
        }
        else
        {
            outputs_[index] = new Connector(inputNode, inputIndex);
            return true;
        }
    }
    else
    {
        setErrorMessage("Output index out of bounds.");
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
        if (inputs_[i] == nullptr)
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

