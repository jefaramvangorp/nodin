#ifndef UI_CONNECTIONITEM_H_
#define UI_CONNECTIONITEM_H_

// Qt.
#include <QGraphicsItem>
#include <QPainterPath>

// Forward declarations.
class NodeItem;

class ConnectionItem : public QGraphicsItem
{
public:
    ConnectionItem(NodeItem* outputItem, int outputIndex,
                   NodeItem* inputItem, int inputIndex);
    virtual ~ConnectionItem();

    // QGraphicsItem interface.
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    QPainterPath connectionLine() const;

    NodeItem* output_item_;
    NodeItem* input_item_;
    const int output_index_;
    const int input_index_;
};

#endif // UI_CONNECTIONITEM_H_
