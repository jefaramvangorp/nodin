
// Includes.
#include "App/App.h"
#include "App/Nodes/AdditionNode.h"
#include "App/Nodes/ConstantNode.h"
#include "App/Nodes/PrinterNode.h"
#include "App/Boundary/NodeProxy.h"

// Qt. (TODO REMOVE THIS DEPENDENCY ON QT).
#include <QUuid>

App::App()
{
}

App::~App()
{
    std::map<std::string, Node*>::iterator iter;
    for (iter = nodes_.begin(); iter != nodes_.end(); ++iter)
    {
        delete (*iter).second;
    }
    nodes_.clear();
    terminal_nodes_.clear();
}

std::vector<std::string> App::availableNodeTypes() const
{
    std::vector<std::string> types;

    types.push_back("Add");
    types.push_back("Constant");
    types.push_back("Printer");

    return types;
}

const NodeProxy* App::createNode(const std::string &type)
{
    std::string id = QUuid::createUuid().toString().toStdString();

    Node* node = 0;

    if (type == "Add")
    {
        node = new AdditionNode(id);
    }
    else if (type == "Constant")
    {
        std::string value = ui_->promptString("Enter constant value:");
        node = new ConstantNode(id, value);
    }
    else if (type == "Printer")
    {
        node = new PrinterNode(id);
    }
    else
    {
        ui_->displayError("Unsupported node type.");
    }

    if (node != 0)
    {
        this->nodes_[id] = node;

        if (node->isTerminal())
        {
            terminal_nodes_.push_back(node);
        }

        return new NodeProxy(node);
    }
    else
    {
        return 0;
    }
}

bool App::connectNodes(const std::string &outputNodeID, int outputIndex, const std::string &inputNodeID, int inputIndex)
{
    // TODO: add rules for connections (i.e. no duplicate connections, no two connections to one input, etc.)

    Node* output_node = nodes_[outputNodeID];
    Node* input_node = nodes_[inputNodeID];

    bool ok = true;
    ok = output_node->connectOutputTo(outputIndex, input_node, inputIndex);
    if (!ok)
    {
        fprintf(stderr, "%s\n", output_node->errorMessage().c_str());
    }

    ok = input_node->connectInputTo(inputIndex, output_node, outputIndex);
    if (!ok)
    {
        fprintf(stderr, "%s\n", input_node->errorMessage().c_str());
    }

    return ok;
}

void App::executeTerminalNodes() const
{
    std::vector<Node*>::const_iterator iter;
    for (iter = terminal_nodes_.begin(); iter != terminal_nodes_.end(); ++iter)
    {
        Node* terminal_node = *iter;

        bool ok = terminal_node->executeAsTerminal();

        if (!ok)
        {
            fprintf(stderr, "%s\n", terminal_node->errorMessage().c_str());
        }
    }
}
