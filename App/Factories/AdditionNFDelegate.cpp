
// Includes.
#include "App/Factories/AdditionNFDelegate.h"
#include "App/Nodes/AdditionNode.h"

AdditionNFDelegate::AdditionNFDelegate()
{
}

AdditionNFDelegate::~AdditionNFDelegate()
{

}

std::string AdditionNFDelegate::nodeType() const
{
    return "Add";
}

std::vector<std::string> AdditionNFDelegate::requiredParameters()
{
    return std::vector<std::string>();
}

bool AdditionNFDelegate::isValidParameter(const std::string &parameter, const std::string &value) const
{
    return true;
}

Node *AdditionNFDelegate::createNode(const std::string &id, const std::map<std::string, std::string> &parameters)
{
    return new AdditionNode(id);
}
