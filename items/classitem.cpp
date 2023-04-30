
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
    this->initMenu();
}

Class::Class(const CPP::Class::Class &className)
{
    setFlag(ItemIsMovable);

    mClass = new CPP::Class::Class(className);
    mFile = new CPP::File::File(className.getName());
    this->initMenu();
}

} // namespace Items



QRectF Items::Class::boundingRect() const
{
    return QRectF(0,0,400,100);
}

void Items::Class::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    QRectF rect = boundingRect();
    painter->fillRect(rect,QColor(175,200,175));
    painter->drawRect(rect);
    painter->drawText(0,0,mClass->getName());

    AbstractItem::paint(painter,option,widget);

}


void Items::Class::initMenu()
{


    auto editAction = addMenu("Düzenle");

    //TODO: add include file
    auto addIncludeFileAction = addMenu("add Include");

    auto saveAction = addMenu("Generate Code");
    auto saveToFileAction = addMenu("Save");


    QObject::connect(addIncludeFileAction,&QAction::triggered,[=](){
        auto mDialog = new GeneratorDialog::AddIncludeDialog();
        mDialog->setIncludeFiles(mFile->includeFiles());
        mDialog->exec();
        if( mDialog->isAccepted() ){
            mFile->setIncludeFiles(mDialog->getIncludeFiles());
        }
        delete mDialog;
    });

    QObject::connect(editAction,&QAction::triggered,[=](){
        auto mDialog = new GeneratorDialog::ClassDialog();
        mDialog->exec();
        if( mDialog->isAccepted() ){
            for( const auto &item : mDialog->getPrivateFunctionMemberList() ){
                mClass->appendPrivate(item);
            }
            for( const auto &item : mDialog->getPublicFunctionMemberList() ){
                mClass->appendPublic(item);
            }
        }
    });


    QObject::connect(saveAction,&QAction::triggered,[=](){
        mFile->addFunction(*mClass);
        mFile->saveMembers();
    });

    QObject::connect(saveToFileAction,&QAction::triggered,[=](){
        mFile->saveFiles();
    });

}


