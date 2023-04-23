
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Widget{
class GraphicView;
class Widget;
}

namespace Layout{
class VBoxLayout;
class HBoxLayout;
}

namespace Scene{
class GraphicScene;
}

class QVBoxLayout;
class QWidget;
class QToolBar;
class QMenu;
class QAction;


class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Widget::GraphicView* mGraphicView;
    Scene::GraphicScene* mScene;

    QVBoxLayout* mMainLayout;

    Widget::Widget* mMainWidget;

    QToolBar* mToolBar;

    QMenu *mAddMenu;
    QAction* mClassAddAction;
private slots:
    void addClassAction();


};

#endif // MAINWINDOW_H
