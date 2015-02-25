
// Includes.
#include "App.h"

// Qt. (TODO REMOVE THIS DEPENDENCY ON QT).
#include <QUuid>

App::App()
{
}

std::vector<std::string> App::availableNodeTypes() const
{
    std::vector<std::string> types;

    types.push_back("Add");
    types.push_back("Subtract");
    types.push_back("Multiply");
    types.push_back("Divide");
    types.push_back("Constant");

    return types;
}

const Node& App::createNode(const std::string &type)
{
    std::string id = QUuid::createUuid().toString().toStdString();

    Node node;

    if (type == "Constant")
    {
        std::string value = this->ui_->promptString("Enter value of constant:");
        node = Node(id, value, 0, 1);
    }
    else
    {
        node = Node(id, type, 2, 1);
    }

    this->nodes[id] = node;
    return this->nodes[id];
}

const Connection& App::connectNodes(const std::string &outputNodeID, int outputIndex, const std::string &inputNodeID, int inputIndex)
{
    Connection c = Connection(outputNodeID, outputIndex, inputNodeID, inputIndex);
    this->network.push_back(c);
    return this->network.back();
}
