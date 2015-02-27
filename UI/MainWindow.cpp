
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

MainWindow::MainWindow(App *app, QWidget *parent)
    : QMainWindow(parent)
    , app_(app)
{
    this->scene_ = createScene();

    QPushButton* add_node_button = new QPushButton(tr("Add node"));
    connect(add_node_button, &QPushButton::clicked, this, &MainWindow::addNodeClicked);
    QPushButton* connect_button = new QPushButton(tr("Connect"));
    connect(connect_button, &QPushButton::clicked, this, &MainWindow::connectClicked);
    QPushButton* execute_button = new QPushButton(tr("Execute"));
    connect(execute_button, &QPushButton::clicked, this, &MainWindow::executeClicked);
    QPushButton* test_button = new QPushButton(tr("Test"));
    connect(test_button, &QPushButton::clicked, this, &MainWindow::testClicked);

    QHBoxLayout* toolbar_layout = new QHBoxLayout;
    toolbar_layout->addWidget(add_node_button);
    toolbar_layout->addWidget(connect_button);
    toolbar_layout->addWidget(execute_button);
    toolbar_layout->addWidget(test_button);
    toolbar_layout->addStretch();

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addLayout(toolbar_layout);
    main_layout->addWidget(new QGraphicsView(this->scene_));

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

void MainWindow::nodeInputSelected(const std::string &nodeID, int index)
{
    this->selected_input_node_id_ = nodeID;
    this->selected_input_index_ = index;
}

void MainWindow::nodeOutputSelected(const std::string &nodeID, int index)
{
    this->selected_output_node_id_ = nodeID;
    this->selected_output_index_ = index;
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
        node_item->addDelegate(this);
        this->scene_->addItem(node_item);
        this->node_items.insert(node->id(), node_item);
    }
}

void MainWindow::connectClicked()
{
    if (selected_input_node_id_.empty() || selected_output_node_id_.empty())
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
            NodeItem* output_node_item = this->node_items.value(selected_output_node_id_);
            NodeItem* input_node_item = this->node_items.value(selected_input_node_id_);

            ConnectionItem* item = new ConnectionItem(output_node_item, selected_output_index_,
                                                      input_node_item, selected_input_index_);

            this->scene_->addItem(item);

            QString connection_id = createConnectionID(selected_output_node_id_, selected_output_index_,
                                                       selected_input_node_id_, selected_input_index_);
            this->connection_items_.insert(connection_id, item);
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
