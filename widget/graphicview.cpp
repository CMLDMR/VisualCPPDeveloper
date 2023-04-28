
#include "graphicview.h"
#include "cpp/function.h"
#include "scene/graphicscene.h"
#include "items/functionitem.h"
#include "dialog/functiondialog.h"

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

    if( mScene->selectedItems().size() ){
        return;
    }

    QMenu menu(this);

    menu.addAction("add Function",[=](){
        auto mDialog = new GeneratorDialog::FunctionDialog();
        mDialog->exec();
        if( mDialog->isAccepted() ){
            CPP::Function::Function mFuction(mDialog->getFunctionName());
            mFuction.setDeclaration(mDialog->getDeclaration());
            mFuction.setDefination(mDialog->getDefination());
            this->mScene->addItem(new Items::Function(mFuction));
        }
    });
    menu.addAction("Kapat");
    menu.exec(event->globalPos());

}
