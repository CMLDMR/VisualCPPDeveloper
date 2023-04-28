
#ifndef WIDGET_GRAPHICVIEW_H
#define WIDGET_GRAPHICVIEW_H

#include <QGraphicsView>

#include <QObject>


namespace Scene {
class GraphicScene;

}


namespace Widget {

class GraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicView();

    Scene::GraphicScene *graphicScene();



signals:
    void classAddClicked();

private:
    Scene::GraphicScene* mScene{nullptr};

//    // QWidget interface
//protected:
//    virtual void contextMenuEvent(QContextMenuEvent *event) override;





};

} // namespace Widget

#endif // WIDGET_GRAPHICVIEW_H
