
// Includes
#include "App/Factories/TextFileNFDelegate.h"
#include "App/Nodes/TextFileNode.h"
#include "App/Logger.h"

// STD.
#include <fstream>

TextFileNFDelegate::TextFileNFDelegate()
{
}

TextFileNFDelegate::~TextFileNFDelegate()
{

}

std::string TextFileNFDelegate::nodeType() const
{
    return "TextFile";
}

std::vector<std::string> TextFileNFDelegate::requiredParameters()
{
    std::vector<std::string> result;
    result.push_back("fileName");
    return result;
}

bool TextFileNFDelegate::isValidParameter(const std::string &parameter, const std::string &value) const
{
    if (parameter == "fileName")
    {
        std::ifstream file(value.c_str());
        if (file.is_open())
        {
            file.close();
            return true;
        }
        else
        {
            file.close();
            Logger::instance().logError("File with given file name cannot be opened.");
            return false;
        }
    }
    else
    {
        return false;
    }
}

Node *TextFileNFDelegate::createNode(const std::string &id, const std::map<std::string, std::string> &parameters)
{
    return new TextFileNode(id, parameters.at("fileName"));
}
