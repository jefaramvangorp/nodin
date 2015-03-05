
// Includes.
#include "App/Nodes/PrinterNode.h"

// STD.
#include <iostream>

PrinterNode::PrinterNode(const std::string &id)
    : Node(id, "Printer", 1, 0)
{
}

bool PrinterNode::computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output)
{
    fprintf(stderr, "%s\n", inputs[0].c_str());
    return true;
}
