
// Includes.
#include "UI/MainWindow.h"
#include "UI/NodeItem.h"
#include "UI/ConnectionItem.h"
#include "App/App.h"
#include "App/Boundary/NodeProxy.h"
#include "App/Boundary/ConnectionProxy.h"

// Qt.
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QGraphicsLineItem>

#include <QDebug>
#include <iostream>

MainWindow::MainWindow(App *app, QWidget *parent)
    : QMainWindow(parent)
    , scene_(nullptr)
    , scene_view_(nullptr)
    , app_(app)
    , temp_line_item_(new QGraphicsLineItem)
    , selected_connector_on_press_(false)
    , selected_output_node_id_("")
    , selected_output_index_(-1)
    , selected_input_node_id_("")
    , selected_input_index_(-1)
{
    scene_ = createScene();

    QPushButton* add_node_button = new QPushButton(tr("Add node"));
    connect(add_node_button, &QPushButton::clicked, this, &MainWindow::addNodeClicked);
    QPushButton* execute_button = new QPushButton(tr("Execute"));
    connect(execute_button, &QPushButton::clicked, this, &MainWindow::executeClicked);
    QPushButton* test_button = new QPushButton(tr("Test"));
    connect(test_button, &QPushButton::clicked, this, &MainWindow::testClicked);

    QHBoxLayout* toolbar_layout = new QHBoxLayout;
    toolbar_layout->addWidget(add_node_button);
    toolbar_layout->addWidget(execute_button);
    toolbar_layout->addWidget(test_button);
    toolbar_layout->addStretch();

    scene_view_ = new NetworkSceneView(scene_);
    scene_view_->setDelegate(this);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addLayout(toolbar_layout);
    main_layout->addWidget(scene_view_);

    QWidget* central_widget = new QWidget;
    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);
}

QGraphicsScene *MainWindow::createScene()
{
    QGraphicsScene* scene = new QGraphicsScene;

    return scene;
}

MainWindow::~MainWindow()
{

}

std::string MainWindow::promptString(const std::string &message)
{
    std::string text = QInputDialog::getText(this, tr("Enter Input:"), QString::fromStdString(message)).toStdString();
    return text;
}

bool MainWindow::promptBool(const std::string &message)
{
    QMessageBox::StandardButton button = QMessageBox::question(this, tr("Enter Input:"), QString::fromStdString(message));
    return button == QMessageBox::Yes;
}

void MainWindow::displayError(const std::string &message)
{
    QMessageBox::critical(this, "Error!", QString::fromStdString(message));
}

void MainWindow::connectionRemoved(ConnectionProxy connection)
{
    QString connection_id = createConnectionID(connection.outputNodeID(), connection.outputIndex(),
                                               connection.inputNodeID(), connection.inputIndex());
    ConnectionItem* item = connection_items_[connection_id];
    scene_->removeItem(item);
    scene_->views().at(0)->repaint();
}

void MainWindow::networkSceneViewPressedAt(const QPoint &pos)
{
    selected_input_index_ = -1;
    selected_input_node_id_ = "";
    selected_output_index_ = -1;
    selected_output_node_id_ = "";

    selected_connector_on_press_ = selectInputIfUnderPos(pos) || selectOutputIfUnderPos(pos);

    if (selected_connector_on_press_)
    {
        QPointF item_pos = temp_line_item_->mapFromScene(scene_view_->mapToScene(pos));

        temp_line_.setPoints(item_pos, item_pos);
        temp_line_item_->setLine(temp_line_);
        scene_->addItem(temp_line_item_);
    }
}

void MainWindow::networkSceneViewReleasedAt(const QPoint &pos)
{
    if (temp_line_item_->scene() == scene_)
    {
        scene_->removeItem(temp_line_item_);
    }
    bool selected_connector_on_release = selectInputIfUnderPos(pos) || selectOutputIfUnderPos(pos);

    if (selected_connector_on_press_ && selected_connector_on_release)
    {
        addConnectionBetweenSelectedNodes();
    }

    selected_connector_on_press_ = false;
}

void MainWindow::networkSceneViewMoved(const QPoint &pos)
{
    if (selected_connector_on_press_)
    {
        QPointF item_pos = temp_line_item_->mapFromScene(scene_view_->mapToScene(pos));
        temp_line_.setP2(item_pos);
        temp_line_item_->setLine(temp_line_);
    }
}

bool MainWindow::selectInputIfUnderPos(const QPoint &pos)
{
    QPointF scene_pos = scene_view_->mapToScene(pos);
    NodeItem* item_under_pos = dynamic_cast<NodeItem*>(scene_->itemAt(scene_pos, scene_view_->transform()));

    if (item_under_pos != nullptr)
    {
        QPointF item_pos = item_under_pos->mapFromScene(scene_pos);

        int input_index = item_under_pos->indexOfInputUnder(item_pos);
        if (input_index != -1)
        {
            selected_input_index_ = input_index;
            selected_input_node_id_ = item_under_pos->nodeID();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool MainWindow::selectOutputIfUnderPos(const QPoint& pos)
{
    QPointF scene_pos = scene_view_->mapToScene(pos);
    NodeItem* item_under_pos = dynamic_cast<NodeItem*>(scene_->itemAt(scene_pos, scene_view_->transform()));

    if (item_under_pos != nullptr)
    {
        QPointF item_pos = item_under_pos->mapFromScene(scene_pos);

        int output_index = item_under_pos->indexOfOutputUnder(item_pos);
        if (output_index != -1)
        {
            selected_output_index_ = output_index;
            selected_output_node_id_ = item_under_pos->nodeID();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void MainWindow::addNodeClicked()
{
    std::vector<std::string> node_types = app_->availableNodeTypes();
    QStringList items;
    for (int i = 0; i < (int) node_types.size(); ++i)
    {
        items.append(QString::fromStdString(node_types[i]));
    }

    bool ok_was_clicked = false;
    std::string title = QInputDialog::getItem(this, tr("Add node"), tr("Choose node type"), items, 0, true, &ok_was_clicked).toStdString();


    if (ok_was_clicked)
    {
        const NodeProxy* node = app_->createNode(title);
        NodeItem* node_item = new NodeItem(node);
        scene_->addItem(node_item);
        node_items_.insert(node->id(), node_item);
    }
}

void MainWindow::addConnectionBetweenSelectedNodes()
{
    if (selected_input_node_id_.empty() || selected_input_index_ == -1 ||
        selected_output_node_id_.empty() || selected_output_index_ == -1)
    {
        return;
    }
    else
    {
        bool ok = app_->connectNodes(selected_output_node_id_,
                                     selected_output_index_,
                                     selected_input_node_id_,
                                     selected_input_index_);

        if (ok)
        {
            NodeItem* output_node_item = node_items_.value(selected_output_node_id_);
            NodeItem* input_node_item = node_items_.value(selected_input_node_id_);

            ConnectionItem* item = new ConnectionItem(output_node_item, selected_output_index_,
                                                      input_node_item, selected_input_index_);

            scene_->addItem(item);

            QString connection_id = createConnectionID(selected_output_node_id_, selected_output_index_,
                                                       selected_input_node_id_, selected_input_index_);
            connection_items_.insert(connection_id, item);
        }
    }

}

QString MainWindow::createConnectionID(const std::string& outputNodeID, int outputIndex,
                                       const std::string& inputNodeID, int inputIndex) const
{
    QStringList list;

    list << QString::fromStdString(outputNodeID);
    list << QString::number(outputIndex);
    list << QString::fromStdString(inputNodeID);
    list << QString::number(inputIndex);

    return list.join(",");
}

void MainWindow::executeClicked()
{
    app_->executeTerminalNodes();
}

void MainWindow::testClicked()
{
    app_->addTestScenario();
}
