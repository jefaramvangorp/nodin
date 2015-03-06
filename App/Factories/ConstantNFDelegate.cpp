
// Includes
#include "App/Factories/ConstantNFDelegate.h"
#include "App/Nodes/ConstantNode.h"

ConstantNFDelegate::ConstantNFDelegate()
{
}

ConstantNFDelegate::~ConstantNFDelegate()
{

}

std::string ConstantNFDelegate::nodeType() const
{
    return "Constant";
}

std::vector<std::string> ConstantNFDelegate::requiredParameters()
{
    std::vector<std::string> result;
    result.push_back("value");
    return result;
}

bool ConstantNFDelegate::isValidParameter(const std::string &parameter, const std::string &value) const
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

Node *ConstantNFDelegate::createNode(const std::string &id, const std::map<std::string, std::string> &parameters)
{
    return new ConstantNode(id, parameters.at("value"));
}
