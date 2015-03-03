
// Includes.
#include "UI/ConnectionItem.h"
#include "UI/NodeItem.h"

// Qt.
#include <QPainter>

ConnectionItem::ConnectionItem(NodeItem *outputItem, int outputIndex, NodeItem *inputItem, int inputIndex)
    : output_item_(outputItem)
    , input_item_(inputItem)
    , output_index_(outputIndex)
    , input_index_(inputIndex)
{

}

ConnectionItem::~ConnectionItem()
{

}

QRectF ConnectionItem::boundingRect() const
{
    return connectionLine().boundingRect();
}

void ConnectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPath(connectionLine());
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
