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

    bool isValid() const;
    std::string name() const;
    int numInputs() const;
    int numOutputs() const;
    std::vector<std::string> inputTypes() const;
    std::vector<std::string> outputTypes() const;
    std::vector<std::string> requiredParameters() const;
    bool validateParameter(const std::string& name, const std::string& value) const;
    std::string evaluateAtOutput(const std::vector<std::string>& inputs, int outputIndex) const;

private:

    std::vector<std::string> stringVectorFromLuaTable(const char* varName) const;
    std::string join(const std::vector<std::string>& list, const std::string& separator) const;

    SeleneHelper* selene_;
};



#endif // APP_LUA_LUANODESCRIPT_H_
