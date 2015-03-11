
// Includes.
#include "App/Factories/LuaNFDelegate.h"
#include "App/Nodes/LuaNode.h"
#include "App/Lua/LuaNodeScript.h"

LuaNFDelegate::LuaNFDelegate(const LuaNodeScript *script)
    : script_(script)
{
}

LuaNFDelegate::~LuaNFDelegate()
{

}

std::string LuaNFDelegate::nodeType() const
{
    return script_->name();
}

std::vector<std::string> LuaNFDelegate::requiredParameters()
{
    return script_->requiredParameters();
}

bool LuaNFDelegate::isValidParameter(const std::string &parameter, const std::string &value) const
{
    return script_->validateParameter(parameter, value);
}

Node *LuaNFDelegate::createNode(const std::string &id, const std::map<std::string, std::string> &parameters)
{
    // TODO: handle parameters that are passed in!
    return new LuaNode(id, script_);
}
