
#ifndef ITEMS_FUNCTION_H
#define ITEMS_FUNCTION_H

#include <QGraphicsItem>

#include "abstractitem.h"

namespace CPP {

class Member;

namespace Function{
class Function;
}

namespace File {
class File;
}

}


namespace Items {

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


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

} // namespace Items

#endif // ITEMS_FUNCTION_H
