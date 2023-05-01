
#ifndef WIDGET_GRAPHICVIEW_H
#define WIDGET_GRAPHICVIEW_H

#include <QGraphicsView>

#include <QObject>
#include <QtMath>


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


    QRectF getVisibleRect()
    {
        QPointF A = this->mapToScene( QPoint(0, 0) );
        QPointF B = this->mapToScene( QPoint(
            this->viewport()->width(),
            this->viewport()->height() ));
        return QRectF( A, B );
    }

signals:
    void classAddClicked();

private:
    Scene::GraphicScene* mScene{nullptr};

    void newProjectDialog();

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;

    // QAbstractScrollArea interface
protected:
    virtual bool viewportEvent(QEvent *event) override;
    virtual void scrollContentsBy(int dx, int dy) override;
};

} // namespace Widget

#endif // WIDGET_GRAPHICVIEW_H
