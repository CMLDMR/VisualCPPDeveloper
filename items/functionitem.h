
#ifndef ITEMS_FUNCTION_H
#define ITEMS_FUNCTION_H

#include <QGraphicsItem>

namespace CPP {
class Member;
namespace Function{
class Function;
}

namespace File {
namespace legacy{
class File;
}
class File;
}
}


namespace Items {

class Function : public QGraphicsItem
{
public:
    Function(const QString &functionName);



private:

    CPP::Function::Function* mFunction;
    CPP::File::File* mFile;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

} // namespace Items

#endif // ITEMS_FUNCTION_H
