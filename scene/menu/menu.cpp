
#include "menu.h"
#include <QGraphicsSceneMouseEvent>
#include <QFontMetricsF>
#include <QPainter>
#include <QFont>
#include <QEvent>
#include <QGraphicsScene>

namespace Menu {

Menu::Menu(const QString &menuName)
    :mMenuName(menuName)
{
    mFont = QFont("Tahoma",12);//TODO: System FONT
    this->setAcceptHoverEvents(true);
    QFontMetricsF metric(mFont);

    mWidth = metric.boundingRect(mMenuName).width()+10;
    mHeight = metric.boundingRect(mMenuName).height();
}

Menu *Menu::addAction(const QString &actionName)
{

    auto mMenuAction = new Menu(actionName);
    mMenuAction->isSubMenu = true;
    mMenuAction->setFont(QFont("Tahoma",10));
    mMenuList.append(mMenuAction);
    mMenuAction->setVisible(false);
    mMenuAction->mParent = this;
    this->scene()->addItem(mMenuAction);

    QObject::connect(this,&Menu::Menu::closeOtherMenu,[=](){
        mMenuAction->closeMenu();
    });

    QObject::connect(mMenuAction,&Menu::clicked,[=](){
        mMouseHover = false;
        mPressed = false;
        for ( auto item : mMenuList ){
            item->setVisible(false);
        }
    });

    return mMenuAction;
}

void Menu::openMenu()
{
    int i = 0;
    for ( auto item : mMenuList ){
        item->setPos(this->scenePos().x(),this->scenePos().y()+i*(item->boundingRect().height()+2)+(item->boundingRect().height()+5));
        item->setVisible(true);
        i++;
    }
}

void Menu::closeMenu()
{
    for ( auto item : mMenuList ){
        item->setVisible(false);
    }
    mPressed = false;

}

void Menu::setPosition(const qreal x, const qreal &y)
{
    this->setPos(x,y);
    int i = 0;
    for ( auto item : mMenuList ){
        item->setPos(this->scenePos().x(),this->scenePos().y()+i*(item->boundingRect().height()+2)+(item->boundingRect().height()+5));
        i++;
    }
}

QString Menu::menuName() const
{
    return mMenuName;
}

void Menu::setFont(const QFont &newFont)
{
    mFont = newFont;
}

} // namespace Menu



QRectF Menu::Menu::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
}

void Menu::Menu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF menuRect = boundingRect();
    painter->setFont(mFont);
    if( mMouseHover ){
        if( mPressed ){
            painter->fillRect(menuRect,QBrush(QColor(0,0,0)));/* brush, brush style or color */
        }else{
            painter->fillRect(menuRect,QBrush(QColor(175,175,175)));/* brush, brush style or color */
        }
        painter->setPen(QPen(QColor(255,255,255)));
    }else{
        painter->fillRect(menuRect,QBrush(QColor(225,225,225)));/* brush, brush style or color */
        painter->setPen(QPen(QColor(0,0,0)));
    }
    menuRect.setX(menuRect.x()+5);
    painter->drawText(menuRect,mMenuName);

}

void Menu::Menu::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    //    this->update();
    QGraphicsItem::hoverMoveEvent(event);
}

void Menu::Menu::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mPressed = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

void Menu::Menu::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if( mPressed ){
        mMouseHover = false;
        mPressed = false;
        closeMenu();
    }else{
        mPressed = true;
        if( !mMenuList.size() ){
            emit clicked();
            mMouseHover = false;
        }else{
            mMouseHover = false;
            openMenu();
        }
    }
    emit closeOtherMenu();
//    qDebug() << mMenuName <<"mPressed" << mPressed;

    this->update();
    QGraphicsItem::mousePressEvent(event);
}


void Menu::Menu::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mMouseHover = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void Menu::Menu::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mMouseHover = false;
    this->update();
    QGraphicsItem::hoverLeaveEvent(event);
}

