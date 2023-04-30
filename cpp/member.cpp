
#include "member.h"

#include "class.h"
#include "function.h"

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

Member::Member(Member &&other)
{
    this->setJsonObject(other);
}

Member::Member(const QJsonObject &other)
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
    }else if( this->value("type").toString() == "Attribute" ){
        return Type::Attribute;
    }else{
        return Type::Constructor;
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

Member &Member::operator=(Member &&other)
{
    this->setJsonObject(other);
    return *this;
}


QString Member::recursiveHeaderFunc(const Member &member ){
    QString code;

    if( member.getType() == CPP::Member::Type::NameSpace ){


    }else if( member.getType() == CPP::Member::Type::Class ){
        CPP::Class::Class _class(member);
        code += "class "+_class.getName()+"\n";
        code += "{\n";
        code += "\tprivate:\n";
        auto list = _class.privateMemberList();
        for( const auto &_member : list ){
            code +="\t"+ this->recursiveHeaderFunc(_member);
        }
        code += "\n";
        code += "\tprotected:\n";
        list = _class.protectedMemberList();
        for( const auto &_member : list ){
            code += "\t"+this->recursiveHeaderFunc(_member);
        }
        code += "\n";
        code += "public:\n";
        list = _class.publicMemberList();
        for( const auto &_member : list ){
            code += "\t"+this->recursiveHeaderFunc(_member);
        }
        code += "\n";
        code += "};// end class " + _class.getName() + "\n\n";


    }else if( member.getType() == CPP::Member::Type::Function ){

        CPP::Function::Function _function(member);
        code += _function.generateHeaderCode();

    }else if( member.getType() == CPP::Member::Type::Attribute ){

    }

    return code;
}
QString Member::recursiveSourceFunc(const Member &member ){
    QString code;

    if( member.getType() == CPP::Member::Type::NameSpace ){


    }else if( member.getType() == CPP::Member::Type::Class ){


    }else if( member.getType() == CPP::Member::Type::Function ){

        CPP::Function::Function _function(member);
        code += _function.getReturnType() + " " +getName()+"::"+_function.getDeclaration()+"( " + _function.getParameter() +" ){\n\n";
        code += "\t"+_function.getDefination()+"\n";
        code += "}\n";

    }else if( member.getType() == CPP::Member::Type::Attribute ){

    }

    return code;
}




} // namespace CPP

