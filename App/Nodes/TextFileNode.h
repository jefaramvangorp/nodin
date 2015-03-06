#ifndef APP_NODES_TEXTFILENODE_H_
#define APP_NODES_TEXTFILENODE_H_

// Includes.
#include "App/Nodes/Node.h"

class TextFileNode : public Node
{
public:
    TextFileNode(const std::string& id, const std::string &fileName);

    virtual bool computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output);

private:

    std::string file_name_;
};

#endif // APP_NODES_TEXTFILENODE_H_
