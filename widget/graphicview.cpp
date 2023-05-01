
#include "graphicview.h"
#include "cpp/function.h"
#include "scene/graphicscene.h"
#include "items/functionitem.h"
#include "dialog/functiondialog.h"
#include "dialog/newprojectdialog.h"

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

    auto MainMenu = mScene->addMenu("Project");

    auto newProject = MainMenu->addAction("New Project");
    MainMenu->addAction("Open Folder");
    MainMenu->addAction("Save");
    MainMenu->addAction("Save As");
    auto closeMenu = MainMenu->addAction("Quit");

    QObject::connect(newProject,&Menu::Menu::clicked,this,&GraphicView::newProjectDialog);
    QObject::connect(closeMenu,&Menu::Menu::clicked,[=](){
        qDebug() << "Close Menu Clicked";
    });

    auto editMenu = mScene->addMenu("Edit");

    editMenu->addAction("Font Change");



    QObject::connect(editMenu,&Menu::Menu::clicked,[=](){
        qDebug() << "Close Menu Clicked";
    });


    auto viewMenu = mScene->addMenu("View Settings");

    viewMenu->addAction("Show Grid");

    QObject::connect(viewMenu,&Menu::Menu::clicked,[=](){
        qDebug() << "Close Menu Clicked";
    });


    return mScene;
}

void GraphicView::newProjectDialog()
{

    auto mDialog = new GeneratorDialog::NewProjectDialog();

    mDialog->exec();

    delete mDialog;

}

} // namespace Widget


void Widget::GraphicView::resizeEvent(QResizeEvent *event)
{
    mScene->setMenuPos(this->mapToScene(this->viewport()->geometry()).boundingRect());
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
