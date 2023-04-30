
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

    auto addIncludeFile = addMenu("Add Include File");
    auto generateCode = addMenu("Generate Code");
    auto saveCode = addMenu("Save Code");
    auto saveProject = addMenu("Save Project");

    QObject::connect(addIncludeFile,&QAction::triggered,[=](){
        auto mDialog = new GeneratorDialog::AddIncludeDialog();
        mDialog->setIncludeFiles(mFile->includeFiles());
        mDialog->exec();
        if( mDialog->isAccepted() ){
            mFile->setIncludeFiles(mDialog->getIncludeFiles());
        }
        delete mDialog;
    });

    QObject::connect(generateCode,&QAction::triggered,[=](){
        mFile->addFunction(*mNameSpace);
        mFile->saveMembers();
    });

    QObject::connect(saveCode,&QAction::triggered,[=](){
        mFile->saveFiles();
    });

}

} // namespace Items



QRectF Items::NamespaceItem::boundingRect() const
{
    return QRectF(0,0,400,100);
}

void Items::NamespaceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->setPen(QPen(QColor(240,240,240)));
    painter->drawRect(rect);

    painter->setPen(QPen(QColor(0,0,0)));
    painter->drawRect(rect.x(),rect.y(),250,rect.height());
    painter->drawText(0,0,"namespace: " + mNameSpace->getName());

    AbstractItem::paint(painter,option,widget);
}
