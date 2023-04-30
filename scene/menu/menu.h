
#ifndef MENU_MENU_H
#define MENU_MENU_H

#include <QGraphicsItem>

#include <QObject>
#include <QAction>
#include <QFont>

#include <QGraphicsTextItem>

#include "items/abstractitem.h"

// TODO: set MenuType customContextMenu

namespace Menu {

class Menu : public QObject,  public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Menu(const QString &menuName);
    virtual ~Menu();

    Menu* addAction( const QString &actionName );

    void openMenu();
    void closeMenu();

    void setPosition(const qreal x,const qreal &y);

signals:
    void clicked();
    void closeOtherMenu();

private:
//    QPointF mClickPoint;
    QVector<Menu*> mMenuList;

    QString mMenuName;
    bool mPressed{false};
    bool mMouseHover{false};
    int mWidth;
    int mHeight;
    QFont mFont;
    bool isSubMenu{false};
    Menu *mParent{nullptr};

    const Items::ItemType mItemType{Items::ItemType::menuItem};


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setFont(const QFont &newFont);

    QString menuName() const;

    Items::ItemType getItemType() const;

    bool isPressed() const;

    bool getIsSubMenu() const;

protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

};

} // namespace Menu

#endif // MENU_MENU_H
