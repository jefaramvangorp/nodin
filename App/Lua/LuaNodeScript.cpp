
// Includes.
#include "App/Lua/LuaNodeScript.h"
#include "App/Lua/Lua.h"
#include "App/Logger.h"


LuaNodeScript::LuaNodeScript(const std::string &fileName)
{
    luaL_dofile(Lua::state(), fileName.c_str());
    lua_pcall(Lua::state(), 0, 0, 0);
}

std::string LuaNodeScript::name() const { return getGlobal(Lua::state(), "name"); }

int LuaNodeScript::numInputs() const { return getGlobal(Lua::state(), "num_inputs"); }

int LuaNodeScript::numOutputs() const { return getGlobal(Lua::state(), "num_outputs"); }

std::vector<std::string> LuaNodeScript::inputTypes() const { return stringVectorFromLuaTable("input_types"); }

std::vector<std::string> LuaNodeScript::outputTypes() const { return stringVectorFromLuaTable("output_types"); }

std::vector<std::string> LuaNodeScript::requiredParameters() const { return stringVectorFromLuaTable("required_parameters"); }

bool LuaNodeScript::validateParameter(const std::string &name, const std::string &value) const
{
    luabridge::LuaRef validate = getGlobal(Lua::state(), "validateParameter");
    return validate(name.c_str(), value.c_str());
}

std::string LuaNodeScript::evaluateAtOutput(const std::vector<std::string> &inputs, int outputIndex) const
{
    std::string inputs_as_string = join(inputs, ",");
    luabridge::LuaRef evaluateForOutput = getGlobal(Lua::state(), "evaluateForOutput");
    return evaluateForOutput(inputs_as_string, outputIndex);
}

bool LuaNodeScript::isValid() const
{
    std::vector<std::string> required_vars;
    required_vars.push_back("name");
    required_vars.push_back("num_inputs");
    required_vars.push_back("num_outputs");
    required_vars.push_back("input_types");
    required_vars.push_back("output_types");
    required_vars.push_back("evaluateForOutput");
    required_vars.push_back("required_parameters");
    required_vars.push_back("validateParameter");

    for (size_t i = 0; i < required_vars.size(); ++i)
    {
        std::string& var = required_vars[i];
        if (getGlobal(Lua::state(), var.c_str()).isNil())
        {
            std::ostringstream stream;
            stream << "\"" << var << "\" variable not found.";
            Logger::instance().logError(stream.str());
            return false;
        }
    }

    return true;
}

std::vector<std::string> LuaNodeScript::stringVectorFromLuaTable(const char *varName) const
{
    std::vector<std::string> result;
    luabridge::LuaRef lua_table = getGlobal(Lua::state(), varName);
    int i = 1;
    while (!lua_table[i].isNil())
    {
        std::string type = lua_table[i].cast<std::string>();
        result.push_back(type);
        ++i;
    }
    return result;
}

std::string LuaNodeScript::join(const std::vector<std::string> &list, const std::string &separator) const
{
    std::ostringstream stream;
    for (size_t i = 0; i < list.size(); ++i)
    {
        stream << list[i];
        if (i < list.size() - 1)
        {
            stream << separator;
        }
    }
    return stream.str();
}
