
#include "attribute.h"

namespace CPP {
namespace Attribute {

Attribute::Attribute(const QString &name)
    :CPP::Member(CPP::Member::Type::Attribute)
{
    this->setName(name);
}

Attribute::Attribute(const Member &other)
{
    this->setJsonObject(other);
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

bool Attribute::getIsReadOnly() const
{
    return this->value(Key::isReadOnly).toBool();
}

QString Attribute::getInitialValue() const
{
    return this->value(Key::defaultValue).toString();
}

QString Attribute::getType() const
{
    return this->value(Key::Type).toString();
}

} // namespace Attribute
} // namespace CPP

