
#include "classitem.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>


#include "cpp/class.h"
#include "cpp/file.h"
#include "cpp/namespace.h"
#include "cpp/function.h"

namespace Items {

Class::Class()
{
    setFlag(ItemIsMovable);

}

} // namespace Items



QRectF Items::Class::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void Items::Class::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    painter->setBackground(mBackGround);
    painter->drawRect(rect);
    painter->drawText(0,0,"Class");
}



void Items::Class::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QMenu menu;

    auto editAction = menu.addAction("Düzenle");

    menu.addAction("Sil");

    auto selected = menu.exec(event->screenPos());

    if( selected == editAction ){

    }

    QGraphicsItem::mouseDoubleClickEvent(event);
}


