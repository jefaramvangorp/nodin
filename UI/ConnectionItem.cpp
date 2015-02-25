
// Includes.
#include "ConnectionItem.h"

// Qt.
#include <QPainter>

ConnectionItem::ConnectionItem(NodeItem *outputItem, int outputIndex, NodeItem *inputItem, int inputIndex)
    : output_item_(outputItem)
    , output_index_(outputIndex)
    , input_item_(inputItem)
    , input_index_(inputIndex)
{
    this->output_item_->addDelegate(this);
    this->input_item_->addDelegate(this);
}

ConnectionItem::~ConnectionItem()
{
    this->output_item_->removeDelegate(this);
    this->input_item_->removeDelegate(this);
}

QRectF ConnectionItem::boundingRect() const
{
    return connectionLine().boundingRect();
}

void ConnectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPath(connectionLine());
}

void ConnectionItem::nodeMoved(NodeItem *item)
{
    prepareGeometryChange();
    update(boundingRect());
}

QPainterPath ConnectionItem::connectionLine() const
{
    QPointF output_pos = this->output_item_->outputPos(this->output_index_);
    QPointF input_pos = this->input_item_->inputPos(this->input_index_);

    QPainterPath path;
    path.moveTo(output_pos);
    path.lineTo(input_pos);
    return path;
}
