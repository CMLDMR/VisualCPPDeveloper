
#include "classitem.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>




#include "dialog/classdialog.h"
#include "dialog/addincludedialog.h"

namespace Items {

Class::Class(const QString &className)
{
    setFlag(ItemIsMovable);

    mClass = new CPP::Class::Class(className);
    mFile = new CPP::File::File(className);

}

Class::Class(const CPP::Class::Class &className)
{
    setFlag(ItemIsMovable);

    mClass = new CPP::Class::Class(className);
    mFile = new CPP::File::File(className.getName());
}

} // namespace Items



QRectF Items::Class::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void Items::Class::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    QRectF rect = boundingRect();
    painter->fillRect(rect,QColor(175,200,175));
    painter->drawRect(rect);
    painter->drawText(0,0,mClass->getName());
}



void Items::Class::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QMenu menu;

    auto editAction = menu.addAction("Düzenle");

    //TODO: add include file
    auto addIncludeFileAction = menu.addAction("add Include");

    menu.addSeparator();
    auto saveAction = menu.addAction("Generate Code");
    auto saveToFileAction = menu.addAction("Save");

    auto selected = menu.exec(event->screenPos());

    if( selected == editAction ){
        auto mDialog = new GeneratorDialog::ClassDialog();
        mDialog->exec();
        if( mDialog->isAccepted() ){
            for( const auto &item : mDialog->getPrivateFunctionMemberList() ){
                mClass->appendPrivate(item);
            }
        }
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
        mFile->addMember(*mClass);
        mFile->saveMembers();
    }

    if( selected == saveToFileAction ){
        mFile->saveFiles();
    }

    QGraphicsItem::mouseDoubleClickEvent(event);
}


