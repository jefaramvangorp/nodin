#ifndef APP_NODES_CONSTANTNODE_H_
#define APP_NODES_CONSTANTNODE_H_

// Includes.
#include "App/Nodes/Node.h"

// STD.
#include <string>

class ConstantNode : public Node
{
public:
    ConstantNode(const std::string &id, const std::string &name, const std::string& value, const std::string& type);

private:

    virtual bool computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output);
    virtual std::string getOutputType(int index) const;

    std::string value_;
    std::string type_;
};

#endif // APP_NODES_CONSTANTNODE_H_
