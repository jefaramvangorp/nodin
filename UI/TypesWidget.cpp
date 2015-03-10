
// Includes.
#include "UI/TypesWidget.h"

// Qt.
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QListWidgetItem>

TypesWidget::TypesWidget(QWidget *parent)
    : QListWidget(parent)
{

}

void TypesWidget::mousePressEvent(QMouseEvent *e)
{
    QListWidget::mousePressEvent(e);
    if (e->button() == Qt::LeftButton)
    {
        drag_start_position_ = e->pos();
    }
}

void TypesWidget::mouseMoveEvent(QMouseEvent *e)
{
    QListWidget::mouseMoveEvent(e);

    if ((e->buttons() & Qt::LeftButton) == 0)
    {
        return;
    }
    else
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        QListWidgetItem* item = itemAt(e->pos());
        if (item != nullptr)
        {
            QString text = item->text();
            mimeData->setData("node/type", text.toUtf8());
            drag->setMimeData(mimeData);
            drag->exec(Qt::CopyAction | Qt::MoveAction);
        }
    }
}
