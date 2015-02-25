
// Includes.
#include "UI/MainWindow.h"
#include "UI/NodeItem.h"
#include "UI/ConnectionItem.h"
#include "App/App.h"

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

    QHBoxLayout* toolbar_layout = new QHBoxLayout;
    toolbar_layout->addWidget(add_node_button);
    toolbar_layout->addWidget(connect_button);
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
    this->selected_input_node = nodeID;
    this->selected_input_index = index;
}

void MainWindow::nodeOutputSelected(const std::string &nodeID, int index)
{
    this->selected_output_node = nodeID;
    this->selected_output_index = index;
}

std::string MainWindow::promptString(const std::string &message)
{
    std::string text = QInputDialog::getText(this, tr("Enter Input:"), QString::fromStdString(message)).toStdString();
    return text;
}

void MainWindow::addNodeClicked()
{
    std::vector<std::string> node_types = app_->availableNodeTypes();
    QStringList items;
    for (int i = 0; i < (int) node_types.size(); ++i)
    {
        items.append(QString::fromStdString(node_types[i]));
    }

    std::string title = QInputDialog::getItem(this, tr("Add node"), tr("Choose node type"), items).toStdString();

    const Node& node = app_->createNode(title);
    NodeItem* node_item = new NodeItem(node);
    node_item->addDelegate(this);
    this->scene_->addItem(node_item);
    this->node_items.insert(node.id(), node_item);
}

void MainWindow::connectClicked()
{
    if (this->selected_input_node.empty() || this->selected_output_node.empty())
    {
        return;
    }
    else
    {
        Connection connection = this->app_->connectNodes(this->selected_output_node,
                                                         this->selected_output_index,
                                                         this->selected_input_node,
                                                         this->selected_input_index);

        NodeItem* output_node_item = this->node_items.value(connection.output_node_id_);
        NodeItem* input_node_item = this->node_items.value(connection.input_node_id_);

        ConnectionItem* item = new ConnectionItem(output_node_item, connection.output_index_,
                                                  input_node_item, connection.input_index_);

        this->scene_->addItem(item);
    }

}
