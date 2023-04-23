
#include "attribute.h"

namespace CPP {
namespace Attribute {

Attribute::Attribute(const QString &name)
    :CPP::Member(CPP::Member::Type::Attribute)
{

}

void Attribute::setInitialValue(const QString &value)
{
    this->insert(Key::defaultValue,value);
}

void Attribute::setReadOnly(const bool value)
{
    this->insert(Key::isReadOnly,value);
}

void Attribute::setType(const QString type)
{
    this->insert(Key::Type,type);
}

} // namespace Attribute
} // namespace CPP

