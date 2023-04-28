
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

QList<Member> Class::privateMemberList() const
{
    QList<Member> list;
    auto array = this->value(Key::privateArea).toArray();
    for( const auto &item : array ){
        CPP::Member member;
        member.setJsonObject(item.toObject());
        list.push_back(member);
    }
    return list;
}

QList<Member> Class::protectedMemberList() const
{
    QList<Member> list;
    auto array = this->value(Key::protectedArea).toArray();
    for( const auto &item : array ){
        CPP::Member member;
        member.setJsonObject(item.toObject());
        list.push_back(member);
    }
    return list;
}

QString Class::generateHeaderCode()
{


    QString code;

    code += "class "+getName()+"\n";
    code += "{\n";
    code += "private:\n";
    auto list = privateMemberList();
    for( const auto &_member : list ){
        code += this->recursiveHeaderFunc(_member);
    }
    code += "\n";
    code += "protected:\n";
    list = protectedMemberList();
    for( const auto &_member : list ){
        code += this->recursiveHeaderFunc(_member);
    }
    code += "\n";
    code += "public:\n";
    list = publicMemberList();
    for( const auto &_member : list ){
        code += this->recursiveHeaderFunc(_member);
    }
    code += "\n";
    code += "};// end class " + getName() + "\n\n";

    return code;

}

QString Class::generateSourceCode()
{
    QString code;

    code += "#include \""+getName().toLower()+".h\"\n";
    code += "\n";
    code += "\n";

    auto list = privateMemberList();
    for( const auto &_member : list ){
        code += this->recursiveSourceFunc(_member);
    }
    code += "\n";

    return code;
}

//QString Class::recursiveHeaderFunc(const Member &member)
//{
//    QString code;

//    if( member.getType() == CPP::Member::Type::NameSpace ){


//    }else if( member.getType() == CPP::Member::Type::Class ){
//        CPP::Class::Class _class(member);
//        code += "class "+_class.getName()+"\n";
//        code += "{\n";
//        code += "\tprivate:\n";
//        auto list = _class.privateMemberList();
//        for( const auto &_member : list ){
//            code +="\t"+ this->recursiveHeaderFunc(_member);
//        }
//        code += "\n";
//        code += "\tprotected:\n";
//        list = _class.protectedMemberList();
//        for( const auto &_member : list ){
//            code += "\t"+this->recursiveHeaderFunc(_member);
//        }
//        code += "\n";
//        code += "public:\n";
//        list = _class.publicMemberList();
//        for( const auto &_member : list ){
//            code += "\t"+this->recursiveHeaderFunc(_member);
//        }
//        code += "\n";
//        code += "};// end class " + _class.getName() + "\n\n";


//    }else if( member.getType() == CPP::Member::Type::Function ){

//        CPP::Function::Function _function(member);
//        code += _function.generateHeaderCode();

//    }else if( member.getType() == CPP::Member::Type::Attribute ){

//    }

//    return code;
//}

//QString Class::recursiveSourceFunc(const Member &member)
//{
//    QString code;

//    if( member.getType() == CPP::Member::Type::NameSpace ){


//    }else if( member.getType() == CPP::Member::Type::Class ){


//    }else if( member.getType() == CPP::Member::Type::Function ){

//        CPP::Function::Function _function(member);
//        code += _function.getReturnType() + " " +getName()+"::"+_function.getDeclaration()+"( " + _function.getParameter() +" ){\n\n";
//        code += "\t"+_function.getDefination()+"\n";
//        code += "}\n";

//    }else if( member.getType() == CPP::Member::Type::Attribute ){

//    }

//    return code;
//}



} // namespace Class
} // namespace CPP

