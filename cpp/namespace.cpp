
#include "namespace.h"

namespace CPP {
namespace NameSpace {

NameSpace::NameSpace(const QString &nameSpaceName)
    :CPP::Member(Member::Type::NameSpace)
{
    this->insert(Key::name,nameSpaceName);
    this->insert(Key::elements,mArray);
}

void NameSpace::appendMember(const Member &member)
{
    mArray.append(member);
    this->insert(Key::elements,mArray);
}

} // namespace NameSpace
} // namespace CPP

