
#include "graphicview.h"
#include "scene/graphicscene.h"

#include <QMenu>
#include <QContextMenuEvent>

namespace Widget {

GraphicView::GraphicView()
{

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
    QMenu menu(this);


    menu.addAction("Class Ekle",this,&Widget::GraphicView::classAddClicked);

    menu.addAction("Kapat");

    menu.exec(event->globalPos());

    QGraphicsView::contextMenuEvent(event);

}
