
#include "mainwindow.h"
#include "widget/graphicview.h"
#include "widget/widget.h"
#include "widget/vboxlayout.h"

#include "scene/graphicscene.h"

#include "items/classitem.h"


#include <QLabel>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QMenuBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    mMainWidget = new Widget::Widget();
    this->setCentralWidget(mMainWidget);

    auto hLayout = mMainWidget->setMainLayout<Layout::VBoxLayout>();

    mGraphicView = hLayout->addWidgetItem<Widget::GraphicView>();
    mScene = mGraphicView->graphicScene();


    QObject::connect(mGraphicView,&Widget::GraphicView::classAddClicked,this,&MainWindow::addClassAction);


    this->setMinimumHeight(450);
    this->setMinimumWidth(720);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addClassAction()
{
    qDebug() << "AddAction";

    mScene->addItem(new Items::Class());

}


