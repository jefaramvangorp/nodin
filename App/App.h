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

class App
{
public:

    class UI
    {
    public:
        virtual ~UI() {}
        virtual std::string promptString(const std::string& message) = 0;
        virtual void displayError(const std::string& message) = 0;
    };

    App();
    ~App();

    void setUI(UI* ui) { ui_ = ui; }

    std::vector<std::string> availableNodeTypes() const;
    const NodeProxy* createNode(const std::string& type);
    bool connectNodes(const std::string& outputNodeID, int outputIndex,
                                   const std::string& inputNodeID, int inputIndex);
    void executeTerminalNodes() const;

private:

    UI* ui_;
    std::map<std::string, Node*> nodes_;
    std::vector<Node*> terminal_nodes_;
};

#endif // APP_APP_H_
