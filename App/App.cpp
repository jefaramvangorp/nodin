
// Includes.
#include "App/App.h"
#include "App/Logger.h"
#include "App/FileSystem.h"
#include "App/Nodes/Node.h"
#include "App/Nodes/ConstantNode.h"
#include "App/Boundary/NodeProxy.h"
#include "App/Factories/NodeFactory.h"
#include "App/Factories/LuaNFDelegate.h"
#include "App/BuiltInConnectorTypes.h"
#include "App/Boundary/ConnectionProxy.h"
#include "App/Factories/NodeFactoryDelegate.h"
#include "App/Lua/LuaNodeScript.h"

namespace
{
    const std::string CONSTANT_TYPE = "Constant";
}

class ScriptFileMonitor : public FileMonitor
{
public:

    ScriptFileMonitor(const std::string& fileName, App* app) : file_name_(fileName), app_(app) {}
    virtual ~ScriptFileMonitor() {}

    virtual void fileWasModified()
    {
        app_->reloadScriptNode(file_name_);
    }

private:

    std::string file_name_;
    App* app_;
};


App::App(FileSystem* fileSystem)
    : ui_(nullptr)
    , delegate_(nullptr)
    , file_system_(fileSystem)
{
}

App::~App()
{
    removeAllNodes();

    std::map<std::string, NodeFactory*>::iterator factories_iter;
    for (factories_iter = node_factories_.begin(); factories_iter != node_factories_.end(); ++factories_iter)
    {
        delete (*factories_iter).second;
    }
    node_factories_.clear();

    std::map<std::string, LuaNodeScript*>::iterator scripts_iter;
    for (scripts_iter = scripts_.begin(); scripts_iter != scripts_.end(); ++scripts_iter)
    {
        delete (*scripts_iter).second;
    }
    scripts_.clear();
}

bool App::addNodeFactory(NodeFactoryDelegate *delegate)
{
    if (delegate != nullptr)
    {
        node_factories_[delegate->nodeType()] = new NodeFactory(delegate);

        if (delegate_ != nullptr)
        {
            delegate_->nodeTypeAdded(delegate->nodeType());
        }

        return true;
    }
    else
    {
        Logger::instance().logError("Node factory delegate must not be NULL!");
        return false;
    }
}

std::vector<std::string> App::availableNodeTypes() const
{
    std::vector<std::string> result;
    result.push_back(CONSTANT_TYPE);

    std::map<std::string, NodeFactory*>::const_iterator iter;
    for (iter = node_factories_.begin(); iter != node_factories_.end(); ++iter)
    {
        result.push_back((*iter).first);
    }

    return result;
}

bool App::createNode(const std::string &type)
{
    std::string id = file_system_->generateUUID();

    Node* node = nullptr;

    if (type == CONSTANT_TYPE) // Special case: these nodes cannot be created by the user.
    {
        std::string name, value, output_type;

        if (ui_->promptConstant(&name, &value, &output_type))
        {
            node = new ConstantNode(id, name, value, output_type);
        }
    }
    else
    {
        node = node_factories_[type]->createNode(id);
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
            Logger::instance().logError("Unable to connect to already connected output");
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
            Logger::instance().logError("Unable to connect to already connected input");
            return false;
        }
    }

    std::string output_type = output_node->outputType(outputIndex);
    std::string input_type = input_node->inputType(inputIndex);
    if ( input_type == BuiltInConnectorTypes::ANY || output_type == input_type)
    {
        if (!output_node->connectOutputTo(outputIndex, input_node, inputIndex))
        {
            Logger::instance().logError(output_node->errorMessage());
            return false;
        }

        if (!input_node->connectInputTo(inputIndex, output_node, outputIndex))
        {
            Logger::instance().logError(input_node->errorMessage());
            return false;
        }

        ui_->connectionAdded(ConnectionProxy(outputNodeID, outputIndex, inputNodeID, inputIndex));
        return true;
    }
    else
    {
        Logger::instance().logError("Input and output type do not match");
        return false;
    }

}

void App::executeTerminalNodes() const
{
    if(terminal_nodes_.empty())
    {
        Logger::instance().logError("No terminal nodes, nothing to be done.");
        return;
    }
    else
    {
        std::vector<Node*>::const_iterator iter;
        for (iter = terminal_nodes_.begin(); iter != terminal_nodes_.end(); ++iter)
        {
            Node* terminal_node = *iter;

            bool ok = terminal_node->executeAsTerminal();

            if (!ok)
            {
                Logger::instance().logError(terminal_node->errorMessage());
            }
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

bool App::removeNode(const std::string &id)
{
    Node* node = nodes_[id];

    for (int i = 0; i < node->numInputs(); ++i)
    {
        if (node->isInputConnected(i))
        {
            Connector* c = node->inputConnector(i);
            c->node_->disconnectOutput(c->index_);
            delegate_->connectionRemoved(ConnectionProxy(c->node_->id(), c->index_, id, i));
        }
    }

    for (int i = 0; i < node->numOutputs(); ++i)
    {
        if (node->isOutputConnected(i))
        {
            Connector* c = node->outputConnector(i);
            c->node_->disconnectInput(c->index_);
            delegate_->connectionRemoved(ConnectionProxy(id, i, c->node_->id(), c->index_));
        }
    }

    nodes_.erase(id);
    delete node;
}

void App::loadScriptNode(const std::string &fileName)
{
    if (LuaNodeScript::isValid(fileName))
    {
        LuaNodeScript* script = new LuaNodeScript(fileName);
        scripts_[fileName] = script;
        file_system_->registerFileMonitor(fileName, new ScriptFileMonitor(fileName, this));
        addNodeFactory(new LuaNFDelegate(script));
    }
    else
    {
        Logger::instance().logError("Unable to load script, it is invalid.");
    }
}

void App::loadScriptNodes(const std::string &directory)
{
    std::vector<std::string> scripts = file_system_->listFilesInDir(directory, "lua");

    std::vector<std::string>::const_iterator iter;
    for (iter = scripts.begin(); iter != scripts.end(); ++iter)
    {
        loadScriptNode(*iter);
    }
}

void App::reloadScriptNode(const std::string &fileName)
{
    bool ok = scripts_[fileName]->reload();
    if (!ok)
    {
        Logger::instance().logMessage(std::string("Unable to reload file: ") + fileName );
    }
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
