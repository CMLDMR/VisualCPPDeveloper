
#include "namespaceitem.h"

#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

#include "dialog/addincludedialog.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsView>
#include <QApplication>

namespace Items {

NamespaceItem::NamespaceItem(const QString &namespaceName)
{
    mNameSpace = new CPP::NameSpace::NameSpace(namespaceName);
    mFile = new CPP::File::File(namespaceName);
}

NamespaceItem::NamespaceItem(const CPP::NameSpace::NameSpace &nameSpace)
{
    mNameSpace = new CPP::NameSpace::NameSpace(nameSpace);
    mFile = new CPP::File::File(mNameSpace->getName());


    auto addAction = addMenu("Add Public Function");

    QObject::connect(addAction,&QAction::triggered,[=](){
        qDebug() << "Add Public Function";
    });

    auto addMember = addMenu("Add Public Member");

}

} // namespace Items



QRectF Items::NamespaceItem::boundingRect() const
{
    return QRectF(0,0,400,100);
}

void Items::NamespaceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->drawRect(rect);

    painter->drawText(0,0,"namespace: " + mNameSpace->getName());

    AbstractItem::paint(painter,option,widget);
}

