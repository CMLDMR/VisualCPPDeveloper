
#ifndef ITEMS_NAMESPACE_H
#define ITEMS_NAMESPACE_H

#include <QGraphicsItem>

#include "cpp/class.h"
#include "cpp/file.h"
#include "cpp/function.h"
#include "cpp/namespace.h"


namespace Items {

class NamespaceItem : public QGraphicsItem
{
public:
    NamespaceItem(const QString &namespaceName);
    NamespaceItem(const CPP::NameSpace::NameSpace &nameSpace);


private:
    CPP::NameSpace::NameSpace* mNameSpace;
    CPP::File::File* mFile;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

} // namespace Items

#endif // ITEMS_NAMESPACE_H
