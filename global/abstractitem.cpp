
#include "abstractitem.h"

namespace Global {

AbstractItem::AbstractItem(const ItemType &type)
    :mItemType(type)
{

}


ItemType AbstractItem::getItemType() const
{
    return mItemType;
}


} // namespace Global

