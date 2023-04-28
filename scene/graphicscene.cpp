
#include "graphicscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>


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
