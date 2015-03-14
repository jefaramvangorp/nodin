#ifndef UI_NETWORKSCENEVIEW_H_
#define UI_NETWORKSCENEVIEW_H_

// Qt.
#include <QGraphicsView>

class NetworkSceneView : public QGraphicsView
{
public:

    class Delegate
    {
    public:
        virtual ~Delegate() {}
        virtual void networkSceneViewPressedAt(const QPoint& pos) = 0;
        virtual void networkSceneViewReleasedAt(const QPoint& pos) = 0;
        virtual void networkSceneViewMoved(const QPoint& pos) = 0;
        virtual void networkSceneViewNodeTypeDroppedAt(const QString& type, const QPoint& pos) = 0;
        virtual void networkSceneViewBackspacePressed() = 0;
    };

    NetworkSceneView(QGraphicsScene* scene, QWidget* parent = nullptr);

    void setDelegate(Delegate* delegate) { delegate_ = delegate; }

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dragMoveEvent(QDragMoveEvent* event);
    virtual void dropEvent(QDropEvent* event);

private:
    Delegate* delegate_;

};

#endif // UI_NETWORKSCENEVIEW_H_
