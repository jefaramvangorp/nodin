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
    };

    NetworkSceneView(QGraphicsScene* scene, QWidget* parent = nullptr);

    void setDelegate(Delegate* delegate) { delegate_ = delegate; }

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);

private:
    Delegate* delegate_;

};

#endif // UI_NETWORKSCENEVIEW_H_
