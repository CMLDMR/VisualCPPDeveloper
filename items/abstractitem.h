
#ifndef ITEMS_ABSTRACTITEM_H
#define ITEMS_ABSTRACTITEM_H

#include <QGraphicsItem>

#include <QObject>
#include <tuple>
#include <QAction>


namespace Items {

class AbstractItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    AbstractItem();

    QAction* addMenu( const QString &menuName );

signals:
    void addClicked();


private:
    QPointF mClickPoint;
    QVector<std::tuple<QAction*,QRectF>> mMenuList;
    bool mPressed{false};


protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

} // namespace Items

#endif // ITEMS_ABSTRACTITEM_H
