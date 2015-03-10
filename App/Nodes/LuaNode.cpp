
// Includes.
#include "App/Nodes/LuaNode.h"
#include "App/Lua/LuaNodeScript.h"


LuaNode::LuaNode(const std::string &id, const LuaNodeScript* script)
    : Node(id, script->name(), script->numInputs(), script->numOutputs())
    , script_(script)
{

}

bool LuaNode::computeValueAtOutput(const std::vector<std::string> &inputs, int outputIndex, std::string *output)
{
    (*output) = script_->evaluateAtOutput(inputs, outputIndex);
    return true;
}

std::string LuaNode::getInputType(int index) const
{
    return script_->inputTypes().at(index);
}

std::string LuaNode::getOutputType(int index) const
{
    return script_->outputTypes().at(index);
}
