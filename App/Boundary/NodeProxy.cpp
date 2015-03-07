
// Includes
#include "App/Boundary/NodeProxy.h"
#include "App/Nodes/Node.h"

NodeProxy::NodeProxy(const Node *node)
    : node_(node)
{
}

const std::string &NodeProxy::id() const
{
    return node_->id();
}

const std::string &NodeProxy::name() const
{
    return node_->name();
}

int NodeProxy::numInputs() const
{
    return node_->numInputs();
}

int NodeProxy::numOutputs() const
{
    return node_->numOutputs();
}

std::string NodeProxy::inputName(int index) const
{
    return node_->inputType(index);
}

std::string NodeProxy::outputName(int index) const
{
    return node_->outputType(index);
}

bool NodeProxy::isTerminal() const
{
    return node_->isTerminal();
}
