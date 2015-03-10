#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Includes.
#include "NodeItem.h"
#include "App/App.h"
#include "App/Logger.h"
#include "UI/NetworkSceneView.h"

// STD.
#include <string>

// Qt.
#include <QMainWindow>
#include <QMap>
#include <QHash>

// Forward declarations.
class QGraphicsScene;
class QGraphicsLineItem;
class ConnectionItem;
class QListWidget;
class QTextEdit;
class QCheckBox;

class MainWindow : public QMainWindow, public App::UI, public App::Delegate, public NetworkSceneView::Delegate, public NodeItem::Delegate, public Logger::Delegate
{
    Q_OBJECT

public:
    MainWindow(App* app, QWidget *parent = 0);
    virtual ~MainWindow();

    // App::UI interface.
    virtual std::string promptString(const std::string& message);
    virtual bool promptBool(const std::string& message);
    virtual std::map<std::string, std::string> promptParameters(const std::vector<std::string>& parameters);
    virtual void displayError(const std::string& message);
    virtual void nodeAdded(NodeProxy node);
    virtual void connectionAdded(ConnectionProxy connection);

    // App::Delegate interface.
    virtual void nodeTypeAdded(const std::string& type);
    virtual void connectionRemoved(ConnectionProxy connection);

    // NetworkSceneView::Delegate inteface.
    virtual void networkSceneViewPressedAt(const QPoint& pos);
    virtual void networkSceneViewReleasedAt(const QPoint& pos);
    virtual void networkSceneViewMoved(const QPoint& pos);
    virtual void networkSceneViewNodeTypeDroppedAt(const QString& type, const QPoint& pos);

    // NodeItem::Delegate interface.
    virtual void nodeMoved(NodeItem* item);

    // Logger::Delegate interface.
    virtual void logMessage(const std::string &message);
    virtual void logError(const std::string &message);

private slots:

    void addNodeClicked();
    void executeClicked();
    void clearClicked();
    void loadScriptNodeClicked();
    void showTypes(int state);

private:

    QString createConnectionID(const std::string &outputNodeID, int outputIndex,
                               const std::string &inputNodeID, int inputIndex) const;
    bool selectInputIfUnderPos(const QPoint &pos);
    bool selectOutputIfUnderPos(const QPoint &pos);
    void addConnectionBetweenSelectedNodes();
    void addNode(const NodeProxy &node, const QPoint &pos);

    QListWidget* types_list_;
    NetworkSceneView* scene_view_;
    QTextEdit* log_view_;
    QCheckBox* show_types_box_;

    QGraphicsScene* scene_;
    App* app_;
    QMap<std::string, NodeItem*> node_items_;
    QMap<QString, ConnectionItem*> connection_items_;
    QGraphicsLineItem* temp_line_item_;
    QLineF temp_line_;
    QPoint last_drop_pos_;

    bool selected_connector_on_press_;
    std::string selected_output_node_id_;
    int selected_output_index_;
    std::string selected_input_node_id_;
    int selected_input_index_;
};

#endif // MAINWINDOW_H
