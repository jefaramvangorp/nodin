
// Includes.
#include "App/Factories/NodeFactory.h"


NodeFactory::NodeFactory(Delegate *delegate)
    : delegate_(delegate)
    , required_parameters_(delegate_->requiredParameters())
{

}

NodeFactory::~NodeFactory()
{

}

std::string NodeFactory::nodeType() const
{
    return delegate_->nodeType();
}

void NodeFactory::setParameterValue(const std::string &parameter, const std::string &value)
{
    parameters_[parameter] = value;
}

Node* NodeFactory::createNode(const std::string &id)
{
    if (allParametersAreValid())
    {
        return delegate_->createNode(id, parameters_);
    }
    else
    {
        return 0;
    }
}

bool NodeFactory::allParametersAreValid()
{
    std::vector<std::string>::const_iterator iter;
    for (iter = required_parameters_.begin(); iter != required_parameters_.end(); ++iter)
    {
        const std::string& parameter_name = (*iter);
        if (!delegate_->isValidParameter(parameter_name, parameters_[parameter_name]))
        {
            return false;
        }
    }

    return true;
}

