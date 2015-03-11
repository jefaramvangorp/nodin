#ifndef APP_LUA_LUANODESCRIPT_H_
#define APP_LUA_LUANODESCRIPT_H_

// STD.
#include <vector>
#include <string>

// Forward declarations.
class SeleneHelper;

class LuaNodeScript
{
public:

    LuaNodeScript(const std::string& fileName);
    ~LuaNodeScript();

    std::string name() const;
    int numInputs() const;
    int numOutputs() const;
    std::vector<std::string> inputTypes() const;
    std::vector<std::string> outputTypes() const;
    std::vector<std::string> requiredParameters() const;
    bool validateParameter(const std::string& name, const std::string& value) const;
    std::string evaluateAtOutput(const std::vector<std::string>& inputs, int outputIndex) const;

    bool reload();

    static bool isValid(const std::string &fileName);

private:

    std::vector<std::string> stringVectorFromLuaTable(const char* varName) const;

    std::string script_file_;
    SeleneHelper* selene_;
};



#endif // APP_LUA_LUANODESCRIPT_H_
