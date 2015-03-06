
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

std::string ConstantNode::getInputType(int index) const
{
    return "";
}

std::string ConstantNode::getOutputType(int index) const
{
    switch (index) {
    case 0:
        return "float";
    default:
        return "";
    }
}
