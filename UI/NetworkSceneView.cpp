
// Includes
#include "NetworkSceneView.h"

// Qt.
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

NetworkSceneView::NetworkSceneView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
    , delegate_(nullptr)
{
}

void NetworkSceneView::mousePressEvent(QMouseEvent *event)
{
    if (delegate_ != nullptr)
    {
        delegate_->networkSceneViewPressedAt(event->pos());
    }

    QGraphicsView::mousePressEvent(event);
}

void NetworkSceneView::mouseReleaseEvent(QMouseEvent *event)
{
    if (delegate_ != nullptr)
    {
        delegate_->networkSceneViewReleasedAt(event->pos());
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void NetworkSceneView::mouseMoveEvent(QMouseEvent *event)
{
    if (delegate_ != nullptr)
    {
        delegate_->networkSceneViewMoved(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void NetworkSceneView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("node/type"))
    {
        event->acceptProposedAction();
    }
}

void NetworkSceneView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("node/type"))
    {
        event->acceptProposedAction();
    }
}

void NetworkSceneView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("node/type"))
    {
        if (delegate_ != nullptr)
        {
            QString type(event->mimeData()->data("node/type"));
            delegate_->networkSceneViewNodeTypeDroppedAt(type, event->pos());
        }
        event->acceptProposedAction();
    }
}
