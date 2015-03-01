
// Includes
#include "NetworkSceneView.h"

// Qt.
#include <QMouseEvent>

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
