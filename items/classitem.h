
#ifndef ITEMS_CLASS_H
#define ITEMS_CLASS_H

#include <QGraphicsItem>
#include <QRectF>
#include <QObject>
#include <QPainter>
#include <QBrush>

#include "cpp/class.h"
#include "cpp/file.h"

#include "items/abstractitem.h"

namespace Items {

class Class : public AbstractItem
{

public:
    Class(const QString &className);
    Class(const CPP::Class::Class &className);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    CPP::Class::Class *mClass;
    CPP::File::File *mFile;

    void initMenu();

};

} // namespace Items

#endif // ITEMS_CLASSITEMS_H
