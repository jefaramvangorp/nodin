#ifndef APP_NODES_TEXTFILENODE_H_
#define APP_NODES_TEXTFILENODE_H_

// Includes.
#include "App/Nodes/Node.h"

class TextFileNode : public Node
{
public:
    TextFileNode(const std::string& id, const std::string &fileName);


private:

    virtual bool computeValueAtOutput(const std::vector<std::string>& inputs, int outputIndex, std::string *output);
    virtual std::string getInputType(int index) const;
    virtual std::string getOutputType(int index) const;

    std::string file_name_;
};

#endif // APP_NODES_TEXTFILENODE_H_
