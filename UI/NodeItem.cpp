
// Includes.
#include "UI/NodeItem.h"
#include "App/Boundary/NodeProxy.h"

// Qt.
#include <QPen>
#include <QPainter>
#include <QString>
#include <QFontMetrics>
#include <QtGlobal>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace
{
    // Constants.
    const int OUTER_MARGIN = 10; // Margin between bounding rect and node box.
    const int INNER_MARGIN = 10; // Margin between node box and text rect.
}

NodeItem::NodeItem(const NodeProxy &node)
    : node_(node)
    , selected_input_index_(-1)
    , selected_output_index_(-1)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

NodeItem::~NodeItem()
{

}

QRectF NodeItem::boundingRect() const
{
    int max_connections = qMax(node_.numInputs(), node_.numOutputs());
    qreal height = max_connections * OUTER_MARGIN + (max_connections-1) * OUTER_MARGIN + 4 * OUTER_MARGIN;

    QFontMetrics metrics(font());
    qreal width = metrics.width(QString::fromStdString(node_.name())) + 2 * INNER_MARGIN + 4 * OUTER_MARGIN;

    return QRectF(-width / 2, -height / 2, width, height);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    drawNodeBox(painter);
    drawText(painter);
    drawInputs(painter);
    drawOutputs(painter);
}

const std::string &NodeItem::nodeID() const
{
    return node_.id();
}

void NodeItem::addDelegate(NodeItem::Delegate *delegate)
{
    if (delegate != nullptr)
    {
        delegates_.push_back(delegate);
    }
}

void NodeItem::removeDelegate(NodeItem::Delegate *delegate)
{
    std::vector<Delegate*>::iterator to_be_erased_delegate = std::find(delegates_.begin(), delegates_.end(), delegate);
    delegates_.erase(to_be_erased_delegate);
}

QPointF NodeItem::inputPos(int index) const
{
    QPainterPath path = pathForInput(index);
    return mapToScene(path.boundingRect().center());
}

QPointF NodeItem::outputPos(int index) const
{
    QPainterPath path = pathForOutput(index);
    return mapToScene(path.boundingRect().center());
}

int NodeItem::indexOfInputUnder(const QPointF &pos)
{
    for (int i = 0; i < node_.numInputs(); ++i)
    {
        QPainterPath path = pathForInput(i);
        if (path.contains(pos))
        {
            return i;
        }
    }

    return -1;
}

int NodeItem::indexOfOutputUnder(const QPointF &pos)
{
    for (int i = 0; i < node_.numOutputs(); ++i)
    {
        QPainterPath path = pathForOutput(i);
        if (path.contains(pos))
        {
            return i;
        }
    }

    return -1;
}

void NodeItem::setHighlightInput(int index)
{
    if (index >= 0 && index < node_.numInputs())
    {
        selected_input_index_ = index;
    }
    else
    {
        selected_input_index_ = -1;
    }
    update(boundingRect());
}

void NodeItem::setHighlightOutput(int index)
{
    if (index >= 0 && index < node_.numOutputs())
    {
        selected_output_index_ = index;
    }
    else
    {
        selected_output_index_ = -1;
    }
    update(boundingRect());
}

void NodeItem::drawNodeBox(QPainter *painter) const
{
    QPainterPath path;
    path.addRoundedRect(nodeBoxRect(), 5, 5);
    painter->fillPath(path, QBrush(Qt::white));
    painter->drawPath(path);
}

void NodeItem::drawText(QPainter *painter) const
{
    painter->setFont(font());
    painter->drawText(textRect(), Qt::AlignCenter, QString::fromStdString(node_.name()));
}

void NodeItem::drawInputs(QPainter *painter) const
{
    for (int i = 0; i < node_.numInputs(); ++i)
    {
        QPainterPath path = pathForInput(i);
        painter->fillPath(path, QBrush(Qt::white));
        painter->drawPath(path);
    }
}

void NodeItem::drawOutputs(QPainter *painter) const
{
    for (int i = 0; i < node_.numOutputs(); ++i)
    {
        QPainterPath path = pathForOutput(i);
        painter->fillPath(path, QBrush(Qt::white));
        painter->drawPath(path);
    }
}

QPainterPath NodeItem::pathForInput(int index) const
{
    qreal start_y = -(node_.numInputs() * OUTER_MARGIN + (node_.numInputs()-1) * OUTER_MARGIN) / 2;
    qreal x = boundingRect().left();
    qreal y = start_y + index * 2 * OUTER_MARGIN;

    QPainterPath path;
    path.addPolygon(QPolygonF() << QPointF(x, y) << QPointF(x+OUTER_MARGIN, y + OUTER_MARGIN / 2) << QPointF(x, y + OUTER_MARGIN) );
    path.closeSubpath();
    return path;
}

QPainterPath NodeItem::pathForOutput(int index) const
{
    qreal start_y = -(node_.numOutputs() * OUTER_MARGIN + (node_.numOutputs()-1) * OUTER_MARGIN) / 2;
    qreal x = boundingRect().right() - OUTER_MARGIN / 2;
    qreal radius = OUTER_MARGIN / 2;
    qreal y = start_y + (index * 2 * OUTER_MARGIN) + (OUTER_MARGIN / 2);

    QPainterPath path;
    path.addEllipse(QPointF(x, y), radius, radius);
    return path;
}

QFont NodeItem::font() const
{
    return QFont("Arial");
}

QRectF NodeItem::nodeBoxRect() const
{
    QRectF bounding_rect = boundingRect();
    return QRectF(bounding_rect.left() + OUTER_MARGIN,
                  bounding_rect.top() + OUTER_MARGIN,
                  bounding_rect.width() - 2 * OUTER_MARGIN,
                  bounding_rect.height() - 2 * OUTER_MARGIN);
}

QRectF NodeItem::textRect() const
{
    QRectF node_box_rect = nodeBoxRect();
    return QRectF(node_box_rect.left() + INNER_MARGIN,
                  node_box_rect.top() + INNER_MARGIN,
                  node_box_rect.width() - 2 * INNER_MARGIN,
                  node_box_rect.height() - 2 * INNER_MARGIN);
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ( (event->modifiers() & Qt::AltModifier) == 0)
    {
        QGraphicsItem::mouseMoveEvent(event);

        for (size_t j = 0; j < delegates_.size(); ++j)
        {
            delegates_[j]->nodeMoved(this);
        }
    }
}
