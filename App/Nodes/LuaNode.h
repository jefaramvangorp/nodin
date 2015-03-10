#ifndef APP_NODES_LUANODE_H_
#define APP_NODES_LUANODE_H_

// Includes.
#include "App/Nodes/Node.h"

// Forward declarations.
class LuaNodeScript;

class LuaNode : public Node
{
public:
    LuaNode(const std::string& id, const LuaNodeScript* script);

private:

    virtual bool computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output);
    virtual std::string getInputType(int index) const;
    virtual std::string getOutputType(int index) const;

    const LuaNodeScript* script_;
};

#endif // APP_NODES_LUANODE_H_
