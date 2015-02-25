#ifndef APP_APP_H_
#define APP_APP_H_

// Includes.
#include "Node.h"

// STD.
#include <map>
#include <vector>
#include <string>

struct Connection
{
    std::string output_node_id_;
    int output_index_;
    std::string input_node_id_;
    int input_index_;

    Connection(const std::string& outputNodeID, int outputIndex,
               const std::string& inputNodeID, int inputIndex)
        : output_node_id_(outputNodeID)
        , output_index_(outputIndex)
        , input_node_id_(inputNodeID)
        , input_index_(inputIndex)
    {}
};

class App
{
public:

    class UI
    {
    public:
        virtual ~UI() {}
        virtual std::string promptString(const std::string& message) = 0;
    };

    App();

    void setUI(UI* ui) { ui_ = ui; }

    std::vector<std::string> availableNodeTypes() const;
    const Node& createNode(const std::string& type);
    const Connection& connectNodes(const std::string& outputNodeID, int outputIndex,
                                   const std::string& inputNodeID, int inputIndex);

private:

    UI* ui_;
    std::map<std::string, Node> nodes;
    std::vector<Connection> network;

};

#endif // APP_APP_H_
