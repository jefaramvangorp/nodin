#ifndef UI_CONNECTIONITEM_H_
#define UI_CONNECTIONITEM_H_

// Includes.
#include "NodeItem.h"

// Qt.
#include <QGraphicsItem>
#include <QPainterPath>

class ConnectionItem : public QGraphicsItem, public NodeItem::Delegate
{
public:
    ConnectionItem(NodeItem* outputItem, int outputIndex,
                   NodeItem* inputItem, int inputIndex);
    virtual ~ConnectionItem();

    // QGraphicsItem interface.
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // NodeItem::Delegate interface.
    virtual void nodeMoved(NodeItem* item);

private:

    QPainterPath connectionLine() const;

    NodeItem* output_item_;
    NodeItem* input_item_;
    const int output_index_;
    const int input_index_;
};

#endif // UI_CONNECTIONITEM_H_
