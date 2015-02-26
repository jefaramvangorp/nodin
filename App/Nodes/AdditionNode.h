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

};

#endif // APP_NODES_ADDITIONNODE_H_
