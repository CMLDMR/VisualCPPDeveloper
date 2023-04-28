
#ifndef SCENE_GRAPHICSCENE_H
#define SCENE_GRAPHICSCENE_H

#include <QGraphicsScene>

#include <QObject>


namespace Scene {

class GraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicScene(QObject *parent = nullptr);

    // QGraphicsScene interface
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsScene interface
protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

};

} // namespace Scene

#endif // SCENE_GRAPHICSCENE_H
