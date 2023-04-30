
#include "abstractitem.h"
#include "qpainter.h"

#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QRectF>
#include <QMenu>


namespace Items {


class DrawMenu{
public:
    DrawMenu( ){}
    QString mString;
    QRectF mRectF;

private:
};

AbstractItem::AbstractItem()
{
    setFlag(ItemIsMovable);
    this->setAcceptHoverEvents(true);
}

QAction* AbstractItem::addMenu(const QString &menuName)
{
    auto action = new QAction(menuName);
    QFontMetricsF metric(QFont("Tahoma",10));
    auto height = metric.boundingRect(menuName).height();
    auto width = metric.boundingRect(menuName).width();
    mMenuList.append(std::make_tuple(action,QRectF(250,mMenuList.size()*(height*1.20),width,height)));
    return action;
}

} // namespace Items







void Items::AbstractItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    mClickPoint = event->pos();
//    for( const auto &[action,rectf] : mMenuList ){
//        if( rectf.contains(mClickPoint)){
//            update(rectf);
//        }
//    }
    update();
    QGraphicsItem::hoverMoveEvent(event);
}

void Items::AbstractItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mClickPoint = event->pos();
    for( const auto &[action,rectf] : mMenuList ){
        if( rectf.contains(mClickPoint)){
            emit action->triggered();
            break;
        }
    }

    QGraphicsItem::mouseReleaseEvent(event);
}


void Items::AbstractItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto font = painter->font();
    painter->setFont(QFont("Tahoma",10));
    for( const auto &[action,rectf] : mMenuList ){
        if( rectf.contains(mClickPoint) ){
            painter->fillRect(rectf,QBrush(QColor(125,125,125)));/* brush, brush style or color */
            painter->setPen(QPen(QColor(255,255,255)));
        }else{
            painter->fillRect(rectf,QBrush(QColor(200,200,200)));/* brush, brush style or color */
            painter->setPen(QPen(QColor(0,0,0)));
        }
        painter->drawText(rectf.x(),rectf.y()+rectf.height()*.8,action->text());
    }
}
