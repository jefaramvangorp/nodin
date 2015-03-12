
// Includes.
#include "TextFileNode.h"
#include "App/BuiltInConnectorTypes.h"

// STD.
#include <fstream>
#include <sstream>

TextFileNode::TextFileNode(const std::string &id, const std::string &fileName)
    : Node(id, fileName, 0, 1)
    , file_name_(fileName)
{

}

bool TextFileNode::computeValueAtOutput(const std::vector<std::string> &inputs, int outputIndex, std::string *output)
{
    if (outputIndex == 0)
    {
        std::ifstream infile(file_name_.c_str());
        if (infile.is_open())
        {
            std::ostringstream stream;
            std::string line;

            while (std::getline(infile, line))
            {
                stream << line;
            }

            (*output) = stream.str();
            return true;
        }
        else
        {
            setErrorMessage("File cannot be read.");
            return false;
        }
    }
    else
    {
        setErrorMessage("This node only accepts requests at outputIndex 0.");
        return false;
    }
}

std::string TextFileNode::getOutputType(int index) const
{
    switch (index) {
    case 0:
        return BuiltInConnectorTypes::TEXT_LINES;
    default:
        return "";
    }
}
