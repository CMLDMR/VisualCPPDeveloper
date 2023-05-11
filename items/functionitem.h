
#ifndef ITEMS_FUNCTION_H
#define ITEMS_FUNCTION_H

#include <QGraphicsItem>

#include <QVector>
#include <QRectF>
#include <QMap>
#include <tuple>

#include "abstractitem.h"

namespace CPP {

class Member;


namespace File {
class File;
}


namespace Function{
class Function;
}

}


namespace Items {

inline const QColor functionBackGroundColor(200,170,170);




class Function : public AbstractItem
{
public:
    Function(const QString &functionName);
    Function(const CPP::Function::Function &function);


private:

    CPP::Function::Function* mFunction;
    CPP::File::File* mFile;

    void initMenu();

    void editFunction();

    QMap<std::tuple<qreal,qreal,qreal,qreal>,int> mMenuRectList;


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface
protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
};

} // namespace Items

#endif // ITEMS_FUNCTION_H
