#ifndef APP_NODES_ADDITIONNODE_H_
#define APP_NODES_ADDITIONNODE_H_

// Includes.
#include "Node.h"

class AdditionNode : public Node
{
public:
    AdditionNode(const std::string &id);

private:

    virtual bool computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output);
    virtual std::string getInputType(int index) const;
    virtual std::string getOutputType(int index) const;
};

#endif // APP_NODES_ADDITIONNODE_H_
