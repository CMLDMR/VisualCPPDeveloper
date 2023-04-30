
#ifndef MENU_MENU_H
#define MENU_MENU_H

#include <QGraphicsItem>

#include <QObject>
#include <QAction>
#include <QFont>

#include <QGraphicsTextItem>


namespace Menu {






class Menu : public QObject,  public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Menu(const QString &menuName);


    Menu* addAction( const QString &actionName );

signals:
    void clicked();

private:
//    QPointF mClickPoint;
    QVector<Menu*> mMenuList;

    QString mMenuName;
    bool mPressed{false};
    bool mMouseHover{false};
    int mWidth;
    int mHeight;
    QFont mFont;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setFont(const QFont &newFont);

protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

};

} // namespace Menu

#endif // MENU_MENU_H
