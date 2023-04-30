
#include "graphicscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "dialog/functiondialog.h"
#include "dialog/classdialog.h"
#include "dialog/namespacedialog.h"

#include "items/functionitem.h"
#include "items/classitem.h"
#include "items/namespaceitem.h"

#include "cpp/function.h"
#include "cpp/class.h"

#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

namespace Scene {

GraphicScene::GraphicScene(QObject *parent)
    : QGraphicsScene{parent}
{



}

void GraphicScene::setMenuPos(const QRectF &viewScene )
{
    for( auto &item : mMenu ){
        item->setPos(viewScene.x(),viewScene.y());
    }
}

QVector<Menu::Menu *> GraphicScene::menu() const
{
    return mMenu;
}

Menu::Menu *GraphicScene::addMenu(const QString &menuName)
{
    auto mMenuItem = new Menu::Menu(menuName);
    this->addItem(mMenuItem);
    mMenuItem->addAction("File");
    mMenuItem->addAction("EWdit");
    mMenuItem->addAction("Save");
    mMenuItem->addAction("Save As");
    auto cloneMenu = mMenuItem->addAction("Close");

    QObject::connect(cloneMenu,&Menu::Menu::clicked,[=](){
        qDebug() << "Close Menu Clicked";
    });
    if( mMenu.size() ){

    }
    mMenu.append(mMenuItem);

    return mMenuItem;
}

} // namespace Scene



void Scene::GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}


void Scene::GraphicScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction("add Class",[=](){

        auto mDialog = new GeneratorDialog::ClassDialog();
        mDialog->exec();
        if( mDialog->isAccepted() ){
            CPP::Class::Class* mClassItem = new CPP::Class::Class(mDialog->getClassName());

            for( const auto &item : mDialog->getPrivateFunctionMemberList() ){
                mClassItem->appendPrivate(item);
            }

            for( const auto &item : mDialog->getPublicFunctionMemberList() ){
                mClassItem->appendPublic(item);
            }
            auto item = new Items::Class(*mClassItem);
            this->addItem(item);
            item->setPos(event->scenePos());
        }
    });

    menu.addAction("add Function",[=](){
        auto mDialog = new GeneratorDialog::FunctionDialog();
        mDialog->exec();
        if( mDialog->isAccepted() ){

            CPP::Function::Function mFuction = mDialog->getFunction();

            this->addItem(new Items::Function(mFuction));
        }
    });

    menu.addAction("add namespace",[=](){

        auto mDialog = new GeneratorDialog::NameSpaceDialog();
        mDialog->exec();
        if( mDialog->isAccepted() ){
            CPP::NameSpace::NameSpace* mNameSpaceItem = new CPP::NameSpace::NameSpace(mDialog->getNameSpace());

            this->addItem(new Items::NamespaceItem(*mNameSpaceItem));
        }
    });

    menu.addAction("Close");
    menu.exec(event->screenPos());

    QGraphicsScene::contextMenuEvent(event);

}

