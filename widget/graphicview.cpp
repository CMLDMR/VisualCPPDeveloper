
#include "graphicview.h"
#include "cpp/function.h"
#include "scene/graphicscene.h"
#include "items/functionitem.h"
#include "dialog/functiondialog.h"

#include <QMenu>
#include <QContextMenuEvent>
#include <QResizeEvent>

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
    mScene->addMenu("Project");
    return mScene;
}

} // namespace Widget


void Widget::GraphicView::resizeEvent(QResizeEvent *event)
{
//    mScene->setMenuPos(this->mapToScene(this->viewport()->geometry()).boundingRect());
//    qDebug() << event;
    QGraphicsView::resizeEvent(event);
}


bool Widget::GraphicView::viewportEvent(QEvent *event)
{
    mScene->setMenuPos(getVisibleRect());
    return QGraphicsView::viewportEvent(event);
}

void Widget::GraphicView::scrollContentsBy(int dx, int dy)
{
//    mScene->setMenuPos(this->mapToScene(this->viewport()->geometry()).boundingRect());
    QGraphicsView::scrollContentsBy(dx,dy);
}
