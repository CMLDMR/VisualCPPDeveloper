
#include "class.h"
#include "cpp/function.h"

namespace CPP {
namespace Class {

Class::Class(const QString &className)
    :Member(Member::Type::Class)
{
    this->insert(Key::name,className);



    this->insert(Key::publicArea,mPublic);
    this->insert(Key::protectedArea,mProtected);
    this->insert(Key::privateArea,mPrivate);
}

Class &Class::appendPublic(const Member &member)
{

    mPublic.append(member);
    this->insert(Key::publicArea,mPublic);
    return *this;
}

Class &Class::appendPrivate(const Member &member)
{
    mPrivate.append(member);
    this->insert(Key::privateArea,mPrivate);
    return *this;
}



} // namespace Class
} // namespace CPP

