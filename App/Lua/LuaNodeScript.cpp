
// Includes.
#include "App/Lua/LuaNodeScript.h"
#include "App/Logger.h"

// Selene.
#include <selene.h>

// STD.
#include <string>
#include <sstream>
#include <iostream>

class InputList
{
public:
    InputList() {}
    InputList(const std::vector<std::string>& inputs)
        : inputs_(inputs)
    {

    }

    int count() { return (int)inputs_.size(); }
    const std::string& getString(int i) { return inputs_.at(i); }
    float getFloat(int i) { return std::stof(inputs_.at(i)); }

private:
    std::vector<std::string> inputs_;
};

class SeleneHelper
{
public:
    SeleneHelper() {}
    sel::State& state() { return state_; }
private:
    sel::State state_{true};
};


LuaNodeScript::LuaNodeScript(const std::string &fileName)
    : selene_(new SeleneHelper)
{
    selene_->state().Load(fileName);
}

LuaNodeScript::~LuaNodeScript()
{
    delete selene_;
}

std::string LuaNodeScript::name() const
{
    return selene_->state()["name"];
}

int LuaNodeScript::numInputs() const
{
    return selene_->state()["num_inputs"];
}

int LuaNodeScript::numOutputs() const
{
    return selene_->state()["num_outputs"];
}

std::vector<std::string> LuaNodeScript::inputTypes() const
{
    return stringVectorFromLuaTable("input_types");
}

std::vector<std::string> LuaNodeScript::outputTypes() const
{
    return stringVectorFromLuaTable("output_types");
}

std::vector<std::string> LuaNodeScript::requiredParameters() const
{
    return stringVectorFromLuaTable("required_parameters");
}

bool LuaNodeScript::validateParameter(const std::string &name, const std::string &value) const
{
    return selene_->state()["validateParameter"](name, value);
}

std::string LuaNodeScript::evaluateAtOutput(const std::vector<std::string> &inputs, int outputIndex) const
{
    InputList list(inputs);

    // Register the instance "list" instead of the class.
    selene_->state()["ndn_inputs"].SetObj(list,
                                          "count", &InputList::count,
                                          "string", &InputList::getString,
                                          "float", &InputList::getFloat);

    return selene_->state()["evaluateForOutput"](outputIndex);
}

bool LuaNodeScript::isValid(const std::string& fileName)
{
    sel::State state;
    if (!state.Load(fileName))
    {
        Logger::instance().logError(state.errorMessage());
        return false;
    }

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
        std::string var = required_vars[i];
        if ( state.CheckNil(var) )
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

    sel::Selector table = selene_->state()[varName];

    int i = 1;
    std::string type = table[i];
    while (!type.empty())
    {
        result.push_back(type);
        std::string next_type = table[++i];
        type = next_type;
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
