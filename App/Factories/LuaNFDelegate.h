#ifndef APP_FACTORIES_LUANFDELEGATE_H_
#define APP_FACTORIES_LUANFDELEGATE_H_

// Includes.
#include "App/Factories/NodeFactoryDelegate.h"

// Forward declarations.
class LuaNodeScript;

class LuaNFDelegate : public NodeFactoryDelegate
{
public:
    LuaNFDelegate(const LuaNodeScript* script);
    virtual ~LuaNFDelegate();

    virtual std::string nodeType() const;
    virtual std::vector<std::string> requiredParameters();
    virtual bool isValidParameter(const std::string& parameter, const std::string& value) const;
    virtual Node* createNode(const std::string& id, const std::map<std::string, std::string>& parameters);

private:

    const LuaNodeScript* script_;
};

#endif // APP_FACTORIES_LUANFDELEGATE_H_
