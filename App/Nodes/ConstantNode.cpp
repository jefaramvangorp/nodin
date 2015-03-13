
// Includes.
#include "App/Nodes/ConstantNode.h"
#include "App/BuiltInConnectorTypes.h"

ConstantNode::ConstantNode(const std::string& id, const std::string& name, const std::string& value, const std::string &type)
    : Node(id, name, 0, 1)
    , value_(value)
    , type_(type)
{
}

bool ConstantNode::computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output)
{
    (*output) = value_;
    return true;
}

std::string ConstantNode::getOutputType(int index) const
{
    if (index == 0)
    {
        return type_;
    }
    else
    {
        return "";
    }
}
