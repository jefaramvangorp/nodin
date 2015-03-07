
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
    const int SPACING = 20; // Space between node title and input and output type texts.
}

NodeItem::NodeItem(const NodeProxy &node, bool showIONames)
    : node_(node)
    , selected_input_index_(-1)
    , selected_output_index_(-1)
    , show_io_names_(showIONames)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

NodeItem::~NodeItem()
{

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

void NodeItem::setShowIONames(bool show)
{
    if (show_io_names_ != show)
    {
        show_io_names_ = show;
        prepareGeometryChange();
    }
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    drawNodeBox(painter);
    drawText(painter);
    drawInputs(painter);
    drawOutputs(painter);

    if (show_io_names_)
    {
        drawInputNames(painter);
        drawOutputNames(painter);
    }

//    painter->setPen(QPen(QColor(Qt::red)));
//    painter->drawRect(textRect());
//    painter->setPen(QPen(QColor(Qt::green)));
//    painter->drawRect(nodeBoxRect());
//    painter->setPen(QPen(QColor(Qt::blue)));
//    painter->drawRect(boundingRect());
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
    QFontMetrics metrics(font());
    QString name = QString::fromStdString(node_.name());

    qreal x = 0.0;
    if (show_io_names_)
    {
        x = textRect().left() + maxInputNameWidth() + SPACING;
    }
    else
    {
        x = textRect().center().x() - 0.5 * metrics.width(name);
    }

    qreal y = textRect().center().y() + 0.35 * metrics.lineSpacing();
    painter->drawText(x, y, name);
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

void NodeItem::drawInputNames(QPainter* painter) const
{
    QFont original_font = painter->font();
    QFont font(painter->font());
    font.setItalic(true);
    painter->setFont(font);

    QPen original_pen = painter->pen();
    painter->setPen(QPen(QColor(Qt::lightGray)));

    for (int i = 0; i < node_.numInputs(); ++i)
    {
        qreal x = textRect().left();
        qreal y = pathForInput(i).boundingRect().bottom();
        painter->drawText(x, y, QString::fromStdString((node_.inputName(i))));
    }

    painter->setFont(original_font);
    painter->setPen(original_pen);
}

void NodeItem::drawOutputNames(QPainter *painter) const
{
    QFont original_font = painter->font();
    QFont font(painter->font());
    font.setItalic(true);
    painter->setFont(font);

    QPen original_pen = painter->pen();
    painter->setPen(QPen(QColor(Qt::lightGray)));

    for (int i = 0; i < node_.numOutputs(); ++i)
    {
        QString name = QString::fromStdString((node_.outputName(i)));
        qreal x = textRect().right() - painter->fontMetrics().width(name);
        qreal y = pathForOutput(i).boundingRect().bottom();
        painter->drawText(x, y, name);
    }

    painter->setFont(original_font);
    painter->setPen(original_pen);
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

QRectF NodeItem::boundingRect() const
{
    QRectF node_box = nodeBoxRect();
    return QRectF(node_box.left() - OUTER_MARGIN,
                  node_box.top() - OUTER_MARGIN,
                  node_box.width() + 2 * OUTER_MARGIN,
                  node_box.height() + 2 * OUTER_MARGIN);
}

QRectF NodeItem::nodeBoxRect() const
{
    QRectF text_rect = textRect();
    return QRectF(text_rect.left() - INNER_MARGIN,
                  text_rect.top() - INNER_MARGIN,
                  text_rect.width() + 2 * INNER_MARGIN,
                  text_rect.height() + 2 * INNER_MARGIN);
}

QRectF NodeItem::textRect() const
{
    QFontMetrics metrics(font());
    qreal name_width = metrics.width(QString::fromStdString(node_.name()));
    qreal width = name_width;

    if (show_io_names_)
    {
        width += 2 * SPACING + maxInputNameWidth() + maxOutputNameWidth();
    }
    else
    {
        width += SPACING;
    }

    int max_connections = qMax(node_.numInputs(), node_.numOutputs());
    qreal height = qMax((int)(metrics.height() * 1.25f),  max_connections * OUTER_MARGIN + (max_connections-1) * OUTER_MARGIN);

    return QRectF(-width / 2, -height / 2, width, height);
}

qreal NodeItem::maxInputNameWidth() const
{
    QFontMetrics metrics(font());
    qreal result = 0.0f;
    for (int i = 0; i < node_.numInputs(); ++i)
    {
        qreal input_name_width = metrics.width(QString::fromStdString(node_.inputName(i)));
        result  = qMax(result, input_name_width);
    }
    return result ;
}

qreal NodeItem::maxOutputNameWidth() const
{
    QFontMetrics metrics(font());
    qreal result = 0.0f;
    for (int i = 0; i < node_.numOutputs(); ++i)
    {
        qreal output_name_width = metrics.width(QString::fromStdString(node_.outputName(i)));
        result = qMax(result, output_name_width);
    }
    return result;
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
