
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
