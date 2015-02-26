#ifndef APP_NODES_PRINTERNODE_H_
#define APP_NODES_PRINTERNODE_H_

// Includes.
#include "App/Nodes/Node.h"

class PrinterNode : public Node
{
public:
    PrinterNode(const std::string& id);

private:

    virtual bool computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output);
};

#endif // APP_NODES_PRINTERNODE_H_
