
// Includes.
#include "App/App.h"
#include "App/Nodes/Node.h"
#include "App/Nodes/AdditionNode.h"
#include "App/Nodes/ConstantNode.h"
#include "App/Nodes/PrinterNode.h"
#include "App/Boundary/NodeProxy.h"
#include "App/Boundary/ConnectionProxy.h"
#include "App/Factories/NodeFactory.h"
#include "App/Factories/NodeFactoryDelegate.h"

// Qt. (TODO REMOVE THIS DEPENDENCY ON QT).
#include <QUuid>

App::App()
{
}

App::~App()
{
    removeAllNodes();

    std::vector<NodeFactory*>::iterator factories_iter;
    for (factories_iter = node_factories_.begin(); factories_iter != node_factories_.end(); ++factories_iter)
    {
        delete (*factories_iter);
    }
    node_factories_.clear();
}

bool App::addNodeFactory(NodeFactoryDelegate *delegate)
{
    if (delegate != nullptr)
    {
        node_factories_.push_back(new NodeFactory(delegate));
        available_node_types_.push_back(delegate->nodeType());
    }
    else
    {
        fprintf(stderr, "Node factory delegate must not be NULL!\n");
        return false;
    }
}

bool App::createNode(const std::string &type)
{
    std::string id = QUuid::createUuid().toString().toStdString();

    Node* node = nullptr;

    std::vector<NodeFactory*>::iterator iter;
    for (iter = node_factories_.begin(); iter != node_factories_.end(); ++iter)
    {
        NodeFactory* factory = (*iter);

        if (factory->nodeType() == type)
        {
            const std::vector<std::string>& required_params = factory->requiredParameters();

            if (!required_params.empty())
            {
                std::map<std::string, std::string> param_values = ui_->promptParameters(required_params);

                for (int i = 0; i < required_params.size(); ++i)
                {
                    std::string param = required_params[i];
                    factory->setParameterValue(param, param_values[param]);
                }
            }

            node = factory->createNode(id);
        }
    }

    if (node == nullptr)
    {
        ui_->displayError("Unsupported node type.");
        return false;
    }
    else
    {
        addNode(node);
        ui_->nodeAdded(NodeProxy(node));
        return true;
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
        return false;
    }

    if (!input_node->connectInputTo(inputIndex, output_node, outputIndex))
    {
        fprintf(stderr, "%s\n", input_node->errorMessage().c_str());
        return false;
    }

    ui_->connectionAdded(ConnectionProxy(outputNodeID, outputIndex, inputNodeID, inputIndex));
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

bool App::clearAllNodes()
{
    bool ok = ui_->promptBool("Are you certain you want to remove all nodes?");

    if (ok)
    {
        removeAllNodes();
    }

    return ok;
}

void App::removeAllNodes()
{
    std::map<std::string, Node*>::iterator nodes_iter;
    for (nodes_iter = nodes_.begin(); nodes_iter != nodes_.end(); ++nodes_iter)
    {
        delete (*nodes_iter).second;
    }
    nodes_.clear();
    terminal_nodes_.clear();
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
