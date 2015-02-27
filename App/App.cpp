
// Includes.
#include "App/App.h"
#include "App/Nodes/AdditionNode.h"
#include "App/Nodes/ConstantNode.h"
#include "App/Nodes/PrinterNode.h"
#include "App/Boundary/NodeProxy.h"
#include "App/Boundary/ConnectionProxy.h"

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
        addNode(node);
        return new NodeProxy(node);
    }
    else
    {
        return 0;
    }
}

void App::addNode(Node *node)
{
    this->nodes_[node->id()] = node;

    if (node->isTerminal())
    {
        terminal_nodes_.push_back(node);
    }
}

bool App::connectNodes(const std::string &outputNodeID, int outputIndex, const std::string &inputNodeID, int inputIndex)
{
    Node* output_node = nodes_[outputNodeID];
    Node* input_node = nodes_[inputNodeID];

    if (output_node->isOutputConnected(outputIndex))
    {
        bool remove_existing_connection = ui_->promptBool("Remove existing connection?");
        if (remove_existing_connection)
        {
            // TODO : fix this ugly code (connector is not valid anymore after the disconnect calls, but can still be used.
            //        It would be better to be able to query a connection (proxy) from the node and not know anything about connectors.
            Connector* connector = output_node->outputConnector(outputIndex);

            ConnectionProxy existing_connection(outputNodeID, outputIndex, connector->node_->id(), connector->index_);
            delegate_->connectionRemoved(existing_connection);

            connector->node_->disconnectInput(connector->index_);
            output_node->disconnectOutput(outputIndex);
        }
        else
        {
            fprintf(stderr, "%s\n", "Unable to connect to already connected output");
            return false;
        }
    }

    if (input_node->isInputConnected(inputIndex))
    {
        bool remove_existing_connection = ui_->promptBool("Remove existing connection?");
        if (remove_existing_connection)
        {
            Connector* connector = input_node->inputConnector(inputIndex);

            ConnectionProxy existing_connection(connector->node_->id(), connector->index_, inputNodeID, inputIndex);
            delegate_->connectionRemoved(existing_connection);

            connector->node_->disconnectOutput(connector->index_);
            input_node->disconnectInput(inputIndex);
        }
        else
        {
            fprintf(stderr, "%s\n", "Unable to connect to already connected input");
            return false;
        }
    }

    if (!output_node->connectOutputTo(outputIndex, input_node, inputIndex))
    {
        fprintf(stderr, "%s\n", output_node->errorMessage().c_str());
    }

    if (!input_node->connectInputTo(inputIndex, output_node, outputIndex))
    {
        fprintf(stderr, "%s\n", input_node->errorMessage().c_str());
    }

    return true;
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

void App::addTestScenario()
{
    ConstantNode* node_1 = new ConstantNode("01", "1");
    ConstantNode* node_2 = new ConstantNode("02", "2");
    PrinterNode* printer = new PrinterNode("03");

    addNode(node_1);
    addNode(node_2);
    addNode(printer);

    connectNodes("01", 0, "03", 0);
    connectNodes("02", 0, "03", 0);
}
