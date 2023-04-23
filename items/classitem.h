
#ifndef ITEMS_CLASS_H
#define ITEMS_CLASS_H

#include <QGraphicsItem>
#include <QRectF>
#include <QObject>
#include <QPainter>
#include <QBrush>

namespace Items {

class Class : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Class();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QBrush mBackGround;

};

} // namespace Items

#endif // ITEMS_CLASSITEMS_H
