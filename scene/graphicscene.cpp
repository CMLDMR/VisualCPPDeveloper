
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
    qreal LastWidth = 0;
    for( int i = 0 ; i < mMenu.size() ; i++ ){
        auto item = mMenu[i];
        item->setPosition(10+viewScene.x() + LastWidth,10+viewScene.y());
        LastWidth += item->boundingRect().width();
    }
}

QVector<Menu::Menu *> GraphicScene::menu() const
{
    return mMenu;
}

Menu::Menu *GraphicScene::addMenu(const QString &menuName)
{
    auto mMenuItem = new Menu::Menu(menuName);

    QObject::connect(mMenuItem,&Menu::Menu::closeOtherMenu,[=](){
        for( auto &item : mMenu ){
            if(item->menuName() != menuName ){
                item->closeMenu();
            }
        }
    });

    this->addItem(mMenuItem);

    mMenu.append(mMenuItem);

    return mMenuItem;
}

void GraphicScene::closeSubMenu()
{

    for( auto &item : mMenu ){
        item->closeMenu();
    }

}

} // namespace Scene



void Scene::GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}


void Scene::GraphicScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    auto clickPos = event->scenePos();
    closeSubMenu();
    bool exist = false;
    for( auto item : this->items() ){

        QRectF rectf(item->pos().x(),item->pos().y(),item->boundingRect().width(),item->boundingRect().height());
        if( rectf.contains(event->scenePos()) ){
            qDebug() << "item contains" ;
            exist = true;
            break;
        }
    }

    if( exist ) return;


    if( mContextMenu ){
        this->removeItem(mContextMenu);
        mContextMenu = nullptr;
    }

    mContextMenu = new Menu::Menu("Context Menü");
                   this->addItem(mContextMenu);

    auto addClass = mContextMenu->addAction("Add Class ");
    addClass->setVisible(true);
    QObject::connect(addClass,&Menu::Menu::clicked,[=](){
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
            item->setPos(clickPos);
        }
    });

    auto addFunction = mContextMenu->addAction("Add Function ");
    addFunction->setVisible(true);
    QObject::connect(addFunction,&Menu::Menu::clicked,[=](){
        auto mDialog = new GeneratorDialog::FunctionDialog();
        mDialog->exec();
        if( mDialog->isAccepted() ){

            CPP::Function::Function mFuction = mDialog->getFunction();
            auto item = new Items::Function(mFuction);

            this->addItem(item);
            item->setPos(clickPos);

        }
    });
    auto addNamespace = mContextMenu->addAction("Add Namespace ");
    addNamespace->setVisible(true);
    QObject::connect(addNamespace,&Menu::Menu::clicked,[=](){
        auto mDialog = new GeneratorDialog::NameSpaceDialog();
        mDialog->exec();
        if( mDialog->isAccepted() ){
            CPP::NameSpace::NameSpace* mNameSpaceItem = new CPP::NameSpace::NameSpace(mDialog->getNameSpace());
            auto item = new Items::NamespaceItem(*mNameSpaceItem);

            this->addItem(item);
            item->setPos(clickPos);

        }
    });

    mContextMenu->setPosition(event->scenePos().x(),event->scenePos().y());




    //    auto mMenuItem = new Menu::Menu("menuName");

    //    mMenuItem->setPosition(event->scenePos().x(),event->scenePos().y());

    //    this->addItem(mMenuItem);



    QGraphicsScene::contextMenuEvent(event);


    return;

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



void Scene::GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    closeSubMenu();
    if( mContextMenu ){
        this->removeItem(mContextMenu);
        mContextMenu->deleteLater();
        mContextMenu = nullptr;
    }
    QGraphicsScene::mousePressEvent(event);
}
