
// Includes.
#include "App/Factories/PrinterNodeFactoryDelegate.h"
#include "App/Nodes/PrinterNode.h"

PrinterNodeFactoryDelegate::PrinterNodeFactoryDelegate()
{
}

PrinterNodeFactoryDelegate::~PrinterNodeFactoryDelegate()
{

}

std::string PrinterNodeFactoryDelegate::nodeType() const
{
    return "Printer";
}

std::vector<std::string> PrinterNodeFactoryDelegate::requiredParameters()
{
    return std::vector<std::string>();
}

bool PrinterNodeFactoryDelegate::isValidParameter(const std::string &parameter, const std::string &value) const
{
    return true;
}

Node *PrinterNodeFactoryDelegate::createNode(const std::string &id, const std::map<std::string, std::string> &parameters)
{
    return new PrinterNode(id);
}
