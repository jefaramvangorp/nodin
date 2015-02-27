
// Includes.
#include "App/Factories/AdditionNodeFactoryDelegate.h"
#include "App/Nodes/AdditionNode.h"

AdditionNodeFactoryDelegate::AdditionNodeFactoryDelegate()
{
}

AdditionNodeFactoryDelegate::~AdditionNodeFactoryDelegate()
{

}

std::string AdditionNodeFactoryDelegate::nodeType() const
{
    return "Add";
}

std::vector<std::string> AdditionNodeFactoryDelegate::requiredParameters()
{
    return std::vector<std::string>();
}

bool AdditionNodeFactoryDelegate::isValidParameter(const std::string &parameter, const std::string &value) const
{
    return true;
}

Node *AdditionNodeFactoryDelegate::createNode(const std::string &id, const std::map<std::string, std::string> &parameters)
{
    return new AdditionNode(id);
}
