
#include "mainwindow.h"
#include "widget/graphicview.h"

#include "scene/graphicscene.h"



#include <QLabel>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    mMainWidget = new QWidget();
    this->setCentralWidget(mMainWidget);

    mMainLayout = new QVBoxLayout();
    mMainWidget->setLayout(mMainLayout);

    mGraphicView = new Widget::GraphicView();

    mMainLayout->addWidget(mGraphicView);


    mScene = mGraphicView->graphicScene();

    this->setMinimumHeight(640);
    this->setMinimumWidth(1024);
}

MainWindow::~MainWindow()
{
}



