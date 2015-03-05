
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
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QListWidget>
#include <QStringListModel>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

class ParametersDialog : public QDialog
{
public:

    ParametersDialog(const std::vector<std::string>& parameters, QWidget* parent = 0)
        : QDialog(parent)
    {
        QGridLayout* param_layout = new QGridLayout;

        for (int i = 0; i < (int)parameters.size(); ++i)
        {
            std::string parameter = parameters.at(i);
            QLabel* parameter_label = new QLabel(QString::fromStdString(parameter));
            QLineEdit* parameter_field = new QLineEdit;

            param_layout->addWidget(parameter_label, i, 0);
            param_layout->addWidget(parameter_field, i, 1);

            parameter_fields_.insert(parameter, parameter_field);
        }

        QPushButton* ok_button = new QPushButton(tr("Ok"));
        connect(ok_button, &QPushButton::clicked, this, &QDialog::accept);
        QPushButton* cancel_button = new QPushButton(tr("Cancel"));
        connect(cancel_button, &QPushButton::clicked, this, &QDialog::reject);

        ok_button->setFocus();

        QHBoxLayout* button_layout = new QHBoxLayout;
        button_layout->addStretch();
        button_layout->addWidget(ok_button);
        button_layout->addWidget(cancel_button);
        button_layout->addStretch();

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addLayout(param_layout);
        layout->addLayout(button_layout);
        setLayout(layout);
    }

    std::map<std::string, std::string> parameterValues() const
    {
        std::map<std::string, std::string> result;

        foreach (std::string param, parameter_fields_.keys())
        {
            result[param] = parameter_fields_.value(param)->text().toStdString();
        }

        return result;
    }

    std::string valueForParameter(const std::string& parameter) const
    {
        return parameter_fields_[parameter]->text().toStdString();
    }

private:

    QMap<std::string, QLineEdit*> parameter_fields_;

};

class TypesWidget : public QListWidget
{
public:
    TypesWidget(QWidget* parent = nullptr) : QListWidget(parent) {}

protected:

    virtual void mousePressEvent(QMouseEvent* e)
    {
        QListWidget::mousePressEvent(e);
        if (e->button() == Qt::LeftButton)
        {
            drag_start_position_ = e->pos();
        }
    }

    virtual void mouseMoveEvent(QMouseEvent *e)
    {
        QListWidget::mouseMoveEvent(e);

        if ((e->buttons() & Qt::LeftButton) == 0)
        {
            return;
        }
        else
        {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;

            QListWidgetItem* item = itemAt(e->pos());
            if (item != nullptr)
            {
                QString text = item->text();
                mimeData->setData("node/type", text.toUtf8());
                drag->setMimeData(mimeData);
                drag->exec(Qt::CopyAction | Qt::MoveAction);
            }
        }
    }

private:

    QPoint drag_start_position_;

};

MainWindow::MainWindow(App *app, QWidget *parent)
    : QMainWindow(parent)
    , types_list_(nullptr)
    , scene_view_(nullptr)
    , log_view_(nullptr)
    , scene_(nullptr)
    , app_(app)
    , temp_line_item_(new QGraphicsLineItem)
    , selected_connector_on_press_(false)
    , selected_output_node_id_("")
    , selected_output_index_(-1)
    , selected_input_node_id_("")
    , selected_input_index_(-1)
{
    scene_ = new QGraphicsScene;

    QPushButton* add_node_button = new QPushButton(tr("Add node"));
    connect(add_node_button, &QPushButton::clicked, this, &MainWindow::addNodeClicked);
    QPushButton* execute_button = new QPushButton(tr("Execute"));
    connect(execute_button, &QPushButton::clicked, this, &MainWindow::executeClicked);
    QPushButton* clear_button = new QPushButton(tr("Clear"));
    connect(clear_button, &QPushButton::clicked, this, &MainWindow::clearClicked);
    QPushButton* test_button = new QPushButton(tr("Test"));
    connect(test_button, &QPushButton::clicked, this, &MainWindow::testClicked);

    QHBoxLayout* toolbar_layout = new QHBoxLayout;
    toolbar_layout->addWidget(add_node_button);
    toolbar_layout->addWidget(execute_button);
    toolbar_layout->addWidget(clear_button);
    toolbar_layout->addWidget(test_button);
    toolbar_layout->addStretch();

    scene_view_ = new NetworkSceneView(scene_);
    scene_view_->setDelegate(this);
    scene_view_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    scene_view_->setAcceptDrops(true);

    QStringList types;
    std::vector<std::string> available_types = app->availableNodeTypes();
    for (int i = 0; i < (int)available_types.size(); ++i)
    {
        types << QString::fromStdString(available_types[i]);
    }
    types_list_ = new TypesWidget;
    types_list_->setMaximumWidth(150);
    types_list_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    types_list_->addItems(types);
    types_list_->setSelectionMode(QAbstractItemView::SingleSelection);

    QHBoxLayout* central_layout = new QHBoxLayout;
    central_layout->addWidget(types_list_);
    central_layout->addWidget(scene_view_);

    log_view_ = new QTextEdit();
    log_view_->setReadOnly(true);
    log_view_->setMaximumHeight(200);
    log_view_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addLayout(toolbar_layout);
    main_layout->addLayout(central_layout);
    main_layout->addWidget(log_view_);

    QWidget* central_widget = new QWidget;
    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);

    Logger::instance().addDelegate(this);
}

MainWindow::~MainWindow()
{
    scene_view_->setScene(nullptr);
    delete scene_;
    delete temp_line_item_;
    node_items_.clear();
    connection_items_.clear();

    Logger::instance().removeDelegate(this);
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

std::map<std::string, std::string> MainWindow::promptParameters(const std::vector<std::string> &parameters)
{
    ParametersDialog dialog(parameters, this);
    dialog.setWindowTitle(tr("Enter parameters:"));

    int result = dialog.exec();
    if (result == QDialog::Accepted)
    {
        return dialog.parameterValues();
    }
    else
    {
        return std::map<std::string, std::string>();
    }
}

void MainWindow::displayError(const std::string &message)
{
    QMessageBox::critical(this, "Error!", QString::fromStdString(message));
}

void MainWindow::nodeAdded(NodeProxy node)
{
    addNode(node, this->last_drop_pos_);
}

void MainWindow::connectionAdded(ConnectionProxy connection)
{
    NodeItem* output_node_item = node_items_.value(connection.outputNodeID());
    NodeItem* input_node_item = node_items_.value(connection.inputNodeID());

    ConnectionItem* item = new ConnectionItem(output_node_item, connection.outputIndex(),
                                              input_node_item, connection.inputIndex());
    scene_->addItem(item);

    QString connection_id = createConnectionID(connection.outputNodeID(), connection.outputIndex(),
                                               connection.inputNodeID(), connection.inputIndex());
    connection_items_.insert(connection_id, item);
}

void MainWindow::connectionRemoved(ConnectionProxy connection)
{
    QString connection_id = createConnectionID(connection.outputNodeID(), connection.outputIndex(),
                                               connection.inputNodeID(), connection.inputIndex());
    ConnectionItem* item = connection_items_[connection_id];
    connection_items_.remove(connection_id);

    scene_->removeItem(item);
    scene_->views().at(0)->repaint();

    delete item;
}

void MainWindow::logMessage(const std::string &message)
{
    log_view_->setTextColor(QColor(Qt::black));
    log_view_->append(QString::fromStdString(message));
}

void MainWindow::logError(const std::string &message)
{
    log_view_->setTextColor(QColor(Qt::red));
    log_view_->append(QString::fromStdString(message));
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

void MainWindow::networkSceneViewNodeTypeDroppedAt(const QString &type, const QPoint &pos)
{
    std::string type_str = type.toStdString();
    last_drop_pos_ = pos;
    app_->createNode(type_str);
}

void MainWindow::nodeMoved(NodeItem *item)
{
    scene_->update(scene_view_->sceneRect());
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
    foreach (QListWidgetItem* item, types_list_->selectedItems())
    {
        std::string type = item->text().toStdString();
        last_drop_pos_ = QPoint(0,0);
        app_->createNode(type);
    }
}

void MainWindow::addNode(const NodeProxy &node, const QPoint &pos)
{
    NodeItem* node_item = new NodeItem(node);

    QPointF scene_pos = scene_view_->mapToScene(pos);
    QTransform transform;
    transform.translate(scene_pos.x(),scene_pos.y());
    node_item->setTransform(transform);

    scene_->addItem(node_item);
    node_items_.insert(node.id(), node_item);
    node_item->addDelegate(this);
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
        app_->connectNodes(selected_output_node_id_,
                           selected_output_index_,
                           selected_input_node_id_,
                           selected_input_index_);
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

void MainWindow::clearClicked()
{
    bool ok = app_->clearAllNodes();

    if (ok)
    {
        scene_view_->setScene(nullptr);
        delete scene_;
        node_items_.clear();
        connection_items_.clear();
        
        scene_ = new QGraphicsScene;
        scene_view_->setScene(scene_);
    }
}

void MainWindow::testClicked()
{
    app_->addTestScenario();
}
