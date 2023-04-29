
#ifndef ITEMS_NAMESPACE_H
#define ITEMS_NAMESPACE_H

#include <QGraphicsItem>

#include "cpp/class.h"
#include "cpp/file.h"
#include "cpp/function.h"
#include "cpp/namespace.h"
#include <QBrush>

#include <QColor>

namespace Items {

class NamespaceItem : public QGraphicsItem
{
public:
    NamespaceItem(const QString &namespaceName);
    NamespaceItem(const CPP::NameSpace::NameSpace &nameSpace);


private:
    CPP::NameSpace::NameSpace* mNameSpace;
    CPP::File::File* mFile;

    bool mPressed{false};

    enum class BUTTONSTATE{
        ENTER,
        LEAVE,

        RIGHTPRESSED,
        RIGHTRELEASE,
        LEFTPRESSED,
        LEFTRELEASED,

        IDLE
    };

    BUTTONSTATE mState{BUTTONSTATE::IDLE};

    QPointF mCLickedPoint;

    QRectF mAddFunctionMemberRect{0,0,80,20};

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface
protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

} // namespace Items

#endif // ITEMS_NAMESPACE_H
