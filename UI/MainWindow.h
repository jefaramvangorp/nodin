#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Includes.
#include "NodeItem.h"
#include "App/App.h"

// Qt.
#include <QMainWindow>
#include <QMap>
#include <QHash>

// Forward declarations.
class QGraphicsScene;
class QGraphicsLineItem;

class MainWindow : public QMainWindow, public NodeItem::Delegate, public App::UI
{
    Q_OBJECT

public:
    MainWindow(App* app, QWidget *parent = 0);
    virtual ~MainWindow();

    // NodeItem interface.
    virtual void nodeInputSelected(const std::string& nodeID, int index);
    virtual void nodeOutputSelected(const std::string& nodeID, int index);

    // App::UI interface.
    virtual std::string promptString(const std::string& message);
    virtual void displayError(const std::string& message);

private slots:

    void addNodeClicked();
    void connectClicked();
    void executeClicked();

private:

    QGraphicsScene* createScene();

    QGraphicsScene* scene_;
    App* app_;
    QMap<std::string, NodeItem*> node_items;


    std::string selected_output_node_id_;
    int selected_output_index_;
    std::string selected_input_node_id_;
    int selected_input_index_;
};

#endif // MAINWINDOW_H
