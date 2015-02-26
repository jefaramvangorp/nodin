#ifndef NODE_H
#define NODE_H

// Qt.
#include <QGraphicsItem>
#include <QPainterPath>

// STD.
#include <string>
#include <vector>

// Forward declarations.
class NodeProxy;

class NodeItem : public QGraphicsItem
{
public:

    class Delegate
    {
    public:
        virtual ~Delegate() {}
        virtual void nodeInputSelected(const std::string& nodeID, int index) {}
        virtual void nodeOutputSelected(const std::string& nodeID, int index) {}
        virtual void nodeMoved(NodeItem* item) {}
    };

    NodeItem(const NodeProxy* node_);
    virtual ~NodeItem();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addDelegate(Delegate* delegate);
    void removeDelegate(Delegate* delegate);
    QPointF inputPos(int index) const;
    QPointF outputPos(int index) const;

protected:

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:

    void drawNodeBox(QPainter* painter) const;
    void drawText(QPainter* painter) const;
    void drawInputs(QPainter* painter) const;
    void drawOutputs(QPainter* painter) const;

    QPainterPath pathForInput(int index) const;
    QPainterPath pathForOutput(int index) const;

    QFont font() const;
    QRectF nodeBoxRect() const;
    QRectF textRect() const;

    const NodeProxy* node_;
    std::vector<Delegate*> delegates_;
    int selected_input_index_;
    int selected_output_index_;
};



#endif // NODE_H
