#ifndef APP_APP_H_
#define APP_APP_H_

// Includes.
#include "App/Boundary/NodeProxy.h"
#include "App/Boundary/ConnectionProxy.h"

// STD.
#include <map>
#include <vector>
#include <string>

// Forward declarations.
class Node;
class NodeFactory;
class NodeFactoryDelegate;
class FileSystem;
class LuaNodeScript;

class App
{
public:

    class UI
    {
    public:
        virtual ~UI() {}

        // Required.
        virtual std::string promptString(const std::string& message) = 0;
        virtual bool promptBool(const std::string& message) = 0;
        virtual std::map<std::string, std::string> promptParameters(const std::vector<std::string>& parameters) = 0;
        virtual void displayError(const std::string& message) = 0;

        // Optional.
        virtual void nodeAdded(NodeProxy node) {}
        virtual void connectionAdded(ConnectionProxy connection) {}
    };

    class Delegate
    {
    public:
        virtual ~Delegate() {}
        virtual void nodeTypeAdded(const std::string& type) = 0;
        virtual void connectionRemoved(ConnectionProxy connection) = 0;
    };


    App(FileSystem *fileSystem);
    ~App();

    static std::string appName() { return "Nodin"; }
    static std::string appVersion() { return "0.2"; }

    void setUI(UI* ui) { ui_ = ui; }
    void setDelegate(Delegate* delegate) { delegate_ = delegate; }

    bool addNodeFactory(NodeFactoryDelegate* delegate); // Takes ownership of delegate!
    std::vector<std::string> availableNodeTypes() const { return available_node_types_; }
    bool createNode(const std::string& type);
    bool connectNodes(const std::string& outputNodeID, int outputIndex,
                                   const std::string& inputNodeID, int inputIndex);
    void executeTerminalNodes() const;
    bool clearAllNodes();
    void loadScriptNode(const std::string& fileName);
    void loadScriptNodes(const std::string& directory);
    void reloadScriptNode(const std::string& fileName);

private:

    void addNode(Node* node);
    void removeAllNodes();

    UI* ui_;
    Delegate* delegate_;
    FileSystem* file_system_;
    std::map<std::string, LuaNodeScript*> scripts_;
    std::vector<NodeFactory*> node_factories_;
    std::vector<std::string> available_node_types_;
    std::map<std::string, Node*> nodes_;
    std::vector<Node*> terminal_nodes_;
};

#endif // APP_APP_H_
