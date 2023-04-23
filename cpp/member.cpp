
#include "member.h"

namespace CPP {

Member::Member()
{

}

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

Member::Member(const Member &other)
{
    this->setJsonObject(other);
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

Member::Type Member::getType() const
{
    if( this->value("type").toString() == "NameSpace" ){
        return Type::NameSpace;
    }else if( this->value("type").toString() == "Class" ){
        return Type::Class;
    }else if( this->value("type").toString() == "Function" ){
        return Type::Function;
    }else{
        return Type::Attribute;
    }
}

QString Member::getName() const
{
    return this->value("name").toString();
}

void Member::setJsonObject(const Member &obj)
{
    while ( this->keys().size() ) {
        for( const auto &key : this->keys() ){
            this->remove(key);
        }
    }
    for( const auto &key : obj.keys() ){
        this->insert(key,obj.value(key));
    }
}

void Member::setJsonObject(const QJsonObject &obj)
{
    while ( this->keys().size() ) {
        for( const auto &key : this->keys() ){
            this->remove(key);
        }
    }
    for( const auto &key : obj.keys() ){
        this->insert(key,obj.value(key));
    }
}

Member &Member::operator=(const Member &other)
{
    this->setJsonObject(other);
    return *this;
}


} // namespace CPP

