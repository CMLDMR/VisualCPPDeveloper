
#include "namespace.h"

namespace CPP {
namespace NameSpace {

NameSpace::NameSpace(const QString &nameSpaceName)
    :CPP::Member(Member::Type::NameSpace)
{
    this->insert(Key::name,nameSpaceName);
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
    auto array = this->value(Key::elements).toArray();
    array.append(member);
    this->insert(Key::elements,array);
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

QString NameSpace::generateHeaderCode() {
    QString code;
    code += "namespace " + getName() + " {\n";
    auto list = memberList();
    for( const auto &_member : list ){
        code += recursiveHeaderFunc(_member);
    }
    code +="\n";
    code +="\n";
    code += "}// end namespace " + getName() +"\n\n";
    return code;
}

QString NameSpace::generateSourceCode()
{
    QString code;
    code += "\n";
    for( const auto &item : memberList() ){
        code += this->recursiveSourceFunc(item);
    }
    code += "\n";
    code += "}\n";
    code += "\n";
    return code;
}

} // namespace NameSpace
} // namespace CPP

