#ifndef APP_APP_H_
#define APP_APP_H_

// Includes.
#include "App/Nodes/Node.h"

// STD.
#include <map>
#include <vector>
#include <string>

// Forward declarations.
class NodeProxy;
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

    void setUI(UI* ui) { ui_ = ui; }
    void setDelegate(Delegate* delegate) { delegate_ = delegate; }

    std::vector<std::string> availableNodeTypes() const;
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
    std::map<std::string, Node*> nodes_;
    std::vector<Node*> terminal_nodes_;
};

#endif // APP_APP_H_
