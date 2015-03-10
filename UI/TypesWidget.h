#ifndef UI_TYPESWIDGET_H_
#define UI_TYPESWIDGET_H_

// Qt.
#include <QListWidget>
#include <QPoint>

class TypesWidget : public QListWidget
{
public:

    TypesWidget(QWidget* parent = nullptr);

protected:

    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent *e);

private:

    QPoint drag_start_position_;

};

#endif // UI_TYPESWIDGET_H_
