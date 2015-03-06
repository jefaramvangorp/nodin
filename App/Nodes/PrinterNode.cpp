
// Includes.
#include "App/Nodes/PrinterNode.h"
#include "App/Logger.h"

// STD.
#include <iostream>

PrinterNode::PrinterNode(const std::string &id)
    : Node(id, "Printer", 1, 0)
{
}

bool PrinterNode::computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output)
{
    Logger::instance().logMessage(inputs[0]);
    return true;
}

std::string PrinterNode::getInputType(int index) const
{
    switch (index) {
    case 0:
        return "any";
    default:
        return "";
    }
}

std::string PrinterNode::getOutputType(int index) const
{
    return "";
}
