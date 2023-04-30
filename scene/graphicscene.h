
#ifndef SCENE_GRAPHICSCENE_H
#define SCENE_GRAPHICSCENE_H

#include <QGraphicsScene>

#include <QObject>
#include <QList>
#include "menu/menu.h"


namespace Scene {

class GraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicScene(QObject *parent = nullptr);

    void setMenuPos(const QRectF &viewScene);



    QVector<Menu::Menu *> menu() const;

    Menu::Menu* addMenu(const QString &menuName );

    void closeSubMenu();

private:
    QVector<Menu::Menu*> mMenu;

    Menu::Menu* mContextMenu{nullptr};


    // QGraphicsScene interface
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsScene interface
protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;


    // QGraphicsScene interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

} // namespace Scene

#endif // SCENE_GRAPHICSCENE_H
