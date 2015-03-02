#ifndef APP_APP_H_
#define APP_APP_H_

// STD.
#include <map>
#include <vector>
#include <string>

// Forward declarations.
class Node;
class NodeProxy;
class NodeFactory;
class NodeFactoryDelegate;
class ConnectionProxy;

class App
{
public:

    class UI
    {
    public:
        virtual ~UI() {}
        virtual std::string promptString(const std::string& message) = 0;
        virtual bool promptBool(const std::string& message) = 0;
        virtual std::map<std::string, std::string> promptParameters(const std::vector<std::string>& parameters) = 0;
        virtual void displayError(const std::string& message) = 0;

    };

    class Delegate
    {
    public:
        virtual ~Delegate() {}
        virtual void connectionRemoved(ConnectionProxy connection) = 0;
    };


    App();
    ~App();

    static std::string appName() { return "Nodin"; }
    static std::string appVersion() { return "0.2"; }

    void setUI(UI* ui) { ui_ = ui; }
    void setDelegate(Delegate* delegate) { delegate_ = delegate; }

    bool addNodeFactory(NodeFactoryDelegate* delegate); // Takes ownership of delegate!
    std::vector<std::string> availableNodeTypes() const { return available_node_types_; }
    const NodeProxy* createNode(const std::string& type);
    bool connectNodes(const std::string& outputNodeID, int outputIndex,
                                   const std::string& inputNodeID, int inputIndex);
    void executeTerminalNodes() const;

    // For debugging purposes, do not use.
    void addTestScenario();

private:

    void addNode(Node* node);

    UI* ui_;
    Delegate* delegate_;
    std::vector<NodeFactory*> node_factories_;
    std::vector<std::string> available_node_types_;
    std::map<std::string, Node*> nodes_;
    std::vector<Node*> terminal_nodes_;
};

#endif // APP_APP_H_
