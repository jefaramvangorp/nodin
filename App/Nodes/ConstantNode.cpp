
// Includes.
#include "App/Nodes/ConstantNode.h"

ConstantNode::ConstantNode(const std::string& id, const std::string& value)
    : Node(id, value, 0, 1)
    , value_(value)
{
}

bool ConstantNode::computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output)
{
    (*output) = value_;
    return true;
}
