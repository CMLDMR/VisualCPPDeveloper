
#include "graphicview.h"
#include "scene/graphicscene.h"
#include "items/classitem.h"
#include "items/functionitem.h"


#include <QMenu>
#include <QContextMenuEvent>


namespace Widget {

GraphicView::GraphicView()
{

    this->setUpdatesEnabled(true);

    this->setViewportUpdateMode(ViewportUpdateMode::FullViewportUpdate);



}

Scene::GraphicScene *GraphicView::graphicScene()
{
    if( !mScene ){
        mScene = new Scene::GraphicScene();
        this->setScene(mScene);
    }
    return mScene;
}

} // namespace Widget



void Widget::GraphicView::contextMenuEvent(QContextMenuEvent *event)
{

    qDebug() << "Selected Size: " << mScene->selectedItems().size();

    if( mScene->selectedItems().size() ){
        return;
    }

    QMenu menu(this);

//    menu.addAction("Class Ekle",[=](){
//        this->mScene->addItem(new Items::Class());
//    });

    menu.addAction("add Function",[=](){




        this->mScene->addItem(new Items::Function("main"));
    });

    menu.addAction("Kapat");

    menu.exec(event->globalPos());

//    QGraphicsView::contextMenuEvent(event);

}
