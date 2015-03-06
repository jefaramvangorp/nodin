
// Includes
#include "App/Nodes/AdditionNode.h"
#include "App/BuiltInConnectorTypes.h"

// STD.
#include <sstream>

AdditionNode::AdditionNode(const std::string& id)
    : Node(id, "Add", 2, 1)
{
}

bool AdditionNode::computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output)
{
    float a = atof(inputs[0].c_str());
    float b = atof(inputs[1].c_str());

    std::ostringstream stream;
    stream << (a+b);
    (*output) = stream.str();

    return true;
}

std::string AdditionNode::getInputType(int index) const
{
    switch (index) {
    case 0:
    case 1:
        return BuiltInConnectorTypes::FLOAT;
    default:
        return "";
    }
}

std::string AdditionNode::getOutputType(int index) const
{
    switch (index) {
    case 0:
        return BuiltInConnectorTypes::FLOAT;
    default:
        return "";
    }
}
