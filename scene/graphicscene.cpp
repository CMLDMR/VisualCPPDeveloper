
#include "graphicscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "dialog/functiondialog.h"
#include "dialog/classdialog.h"

#include "items/functionitem.h"
#include "items/classitem.h"

#include "cpp/function.h"
#include "cpp/class.h"

#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMouseEvent>

namespace Scene {

GraphicScene::GraphicScene(QObject *parent)
    : QGraphicsScene{parent}
{

}

} // namespace Scene



void Scene::GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{


//    qDebug() << event->pos().x() << event->pos().y() << event->scenePos();

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

            qDebug() << "Class Code: "<<mClassItem->generateHeaderCode();

            this->addItem(new Items::Class(*mClassItem));
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
    menu.addAction("Kapat");
    menu.exec(event->screenPos());
}

