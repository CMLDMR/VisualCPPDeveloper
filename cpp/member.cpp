
#include "member.h"

namespace CPP {

Member::Member(const Type &type )
    :mType(type)
{
    switch (mType) {
    case Type::Constructor:
        this->insert("type","Constructor");
        break;
    case Type::Destructor:
        this->insert("type","Destructor");
        break;
    case Type::Function:
        this->insert("type","Function");
        break;
    case Type::Operator:
        this->insert("type","Operator");
        break;
    case Type::Attribute:
        this->insert("type","Attribute");
        break;
    case Type::Class:
        this->insert("type","Class");
        break;
    case Type::NameSpace:
        this->insert("type","NameSpace");
        break;
    case Type::File:
        this->insert("type","File");
        break;
    default:
        break;
    }
}

Member &Member::setName(const QString &name)
{
    this->insert("name",name);
    return *this;
}

Member &Member::setType(const QString &type)
{
    this->insert("type",type);
    return *this;
}


} // namespace CPP

