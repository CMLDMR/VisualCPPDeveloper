
#ifndef GLOBAL_ABSTRACTITEM_H
#define GLOBAL_ABSTRACTITEM_H

#include <QGraphicsItem>

#include <QObject>


namespace Global {

enum class ItemType{
    menuItem = 0,
    objectItem
};

class AbstractItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    AbstractItem(const ItemType &type = ItemType::objectItem);

    ItemType getItemType() const;

private:
    ItemType mItemType;

};

} // namespace Global

#endif // GLOBAL_ABSTRACTITEM_H
