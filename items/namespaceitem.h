
#ifndef ITEMS_NAMESPACE_H
#define ITEMS_NAMESPACE_H

#include <QGraphicsItem>

#include "cpp/class.h"
#include "cpp/file.h"
#include "cpp/function.h"
#include "cpp/namespace.h"
#include <QBrush>

#include <QColor>

#include "abstractitem.h"

namespace Items {

class NamespaceItem : public AbstractItem
{
public:
    NamespaceItem(const QString &namespaceName);
    NamespaceItem(const CPP::NameSpace::NameSpace &nameSpace);


private:
    CPP::NameSpace::NameSpace* mNameSpace;
    CPP::File::File* mFile;

    bool mPressed{false};


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

} // namespace Items

#endif // ITEMS_NAMESPACE_H
