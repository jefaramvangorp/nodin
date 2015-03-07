#ifndef NODE_H
#define NODE_H

// Includes.
#include "App/Boundary/NodeProxy.h"

// Qt.
#include <QGraphicsItem>
#include <QPainterPath>

// STD.
#include <string>
#include <vector>
#include <QPointF>

class NodeItem : public QGraphicsItem
{
public:

    class Delegate
    {
    public:
        virtual ~Delegate() {}
        virtual void nodeMoved(NodeItem* item) {}
    };

    NodeItem(const NodeProxy& node_);
    virtual ~NodeItem();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    const std::string& nodeID() const;
    void addDelegate(Delegate* delegate);
    void removeDelegate(Delegate* delegate);
    QPointF inputPos(int index) const;
    QPointF outputPos(int index) const;
    int indexOfInputUnder(const QPointF& pos);
    int indexOfOutputUnder(const QPointF& pos);
    void setHighlightInput(int index);
    void setHighlightOutput(int index);

protected:

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:

    void drawNodeBox(QPainter* painter) const;
    void drawText(QPainter* painter) const;
    void drawInputs(QPainter* painter) const;
    void drawOutputs(QPainter* painter) const;
    void drawInputNames(QPainter *painter) const;
    void drawOutputNames(QPainter *painter) const;

    QPainterPath pathForInput(int index) const;
    QPainterPath pathForOutput(int index) const;
    qreal maxInputNameWidth() const;
    qreal maxOutputNameWidth() const;

    QFont font() const;
    QRectF nodeBoxRect() const;
    QRectF textRect() const;

    NodeProxy node_;
    std::vector<Delegate*> delegates_;
    int selected_input_index_;
    int selected_output_index_;
};



#endif // NODE_H
