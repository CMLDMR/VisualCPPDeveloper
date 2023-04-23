
#include "namespace.h"

namespace CPP {
namespace NameSpace {

NameSpace::NameSpace(const QString &nameSpaceName)
    :CPP::Member(Member::Type::NameSpace)
{
    this->insert(Key::name,nameSpaceName);
    this->insert(Key::elements,mArray);
}

NameSpace::NameSpace(const NameSpace &other)
{
    this->setJsonObject(other);
}

NameSpace::NameSpace(const Member &other)
{
    this->setJsonObject(other);
}

void NameSpace::appendMember(const Member &member)
{
    mArray.append(member);
    this->insert(Key::elements,mArray);
}

QList<Member> NameSpace::memberList() const
{
    auto array = this->value(Key::elements).toArray();
    QList<Member> list;
    for( const auto &item : array ){
        CPP::Member obj;
        obj.setJsonObject(item.toObject());
        list.append(obj);
    }
    return list;
}

} // namespace NameSpace
} // namespace CPP

