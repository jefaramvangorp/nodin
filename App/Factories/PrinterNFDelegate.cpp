
// Includes.
#include "App/Factories/PrinterNFDelegate.h"
#include "App/Nodes/PrinterNode.h"

PrinterNFDelegate::PrinterNFDelegate()
{
}

PrinterNFDelegate::~PrinterNFDelegate()
{

}

std::string PrinterNFDelegate::nodeType() const
{
    return "Printer";
}

std::vector<std::string> PrinterNFDelegate::requiredParameters()
{
    return std::vector<std::string>();
}

bool PrinterNFDelegate::isValidParameter(const std::string &parameter, const std::string &value) const
{
    return true;
}

Node *PrinterNFDelegate::createNode(const std::string &id, const std::map<std::string, std::string> &parameters)
{
    return new PrinterNode(id);
}
