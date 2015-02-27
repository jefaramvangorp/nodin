
// Includes
#include "App/Factories/ConstantNodeFactoryDelegate.h"
#include "App/Nodes/ConstantNode.h"

ConstantNodeFactoryDelegate::ConstantNodeFactoryDelegate()
{
}

ConstantNodeFactoryDelegate::~ConstantNodeFactoryDelegate()
{

}

std::string ConstantNodeFactoryDelegate::nodeType() const
{
    return "Constant";
}

std::vector<std::string> ConstantNodeFactoryDelegate::requiredParameters()
{
    std::vector<std::string> result;
    result.push_back("value");
    return result;
}

bool ConstantNodeFactoryDelegate::isValidParameter(const std::string &parameter, const std::string &value) const
{
    if (parameter == "value")
    {
        try
        {
            std::stof(value);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

Node *ConstantNodeFactoryDelegate::createNode(const std::string &id, const std::map<std::string, std::string> &parameters)
{
    return new ConstantNode(id, parameters.at("value"));
}
