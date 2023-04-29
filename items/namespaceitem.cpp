
#include "namespaceitem.h"

#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>

#include "dialog/addincludedialog.h"

namespace Items {

NamespaceItem::NamespaceItem(const QString &namespaceName)
{
    setFlag(ItemIsMovable);
    mNameSpace = new CPP::NameSpace::NameSpace(namespaceName);
    mFile = new CPP::File::File(namespaceName);
}

NamespaceItem::NamespaceItem(const CPP::NameSpace::NameSpace &nameSpace)
{
    mNameSpace = new CPP::NameSpace::NameSpace(nameSpace);
    mFile = new CPP::File::File(mNameSpace->getName());
    setFlag(ItemIsMovable);
}

} // namespace Items



QRectF Items::NamespaceItem::boundingRect() const
{
    return QRectF(0,0,300,100);

}

void Items::NamespaceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->fillRect(rect,QBrush(QColor(200,200,170)));/* brush, brush style or color */
    painter->drawRect(rect);

    painter->drawText(0,0,"namespace: " + mNameSpace->getName());
}


void Items::NamespaceItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    if( event->button() == Qt::MouseButton::LeftButton ){


        QMenu menu;

        auto editAction = menu.addAction("Düzenle");
                          auto addIncludeFileAction = menu.addAction("add Include");

        menu.addSeparator();
        auto saveAction = menu.addAction("Generate Code");
        auto saveToFileAction = menu.addAction("Save");

        auto selected = menu.exec(event->screenPos());


        if( selected == editAction ){

        }

        if( selected == addIncludeFileAction ){
            auto mDialog = new GeneratorDialog::AddIncludeDialog();
            mDialog->setIncludeFiles(mFile->includeFiles());
            mDialog->exec();
            if( mDialog->isAccepted() ){
                mFile->setIncludeFiles(mDialog->getIncludeFiles());
            }
            delete mDialog;

        }

        if( selected == saveAction ){
            mFile->addMember(*mNameSpace);
            mFile->saveMembers();
        }

        if( selected == saveToFileAction ){
            mFile->saveFiles();
        }

    }
}
