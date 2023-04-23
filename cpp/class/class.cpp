
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

Class::Class(const Member &member)
{
    this->setJsonObject(member);
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

QList<Member> Class::publicMemberList() const
{
    QList<Member> list;
    auto array = this->value(Key::publicArea).toArray();
    for( const auto &item : array ){
        CPP::Member member;
        member.setJsonObject(item.toObject());
        list.push_back(member);
    }
    return list;
}



} // namespace Class
} // namespace CPP

