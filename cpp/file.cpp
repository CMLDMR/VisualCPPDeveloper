
#include "file.h"
#include "cpp/namespace.h"
#include "cpp/class/class.h"
#include "cpp/function.h"
#include "cpp/attribute.h"

namespace CPP {

File::File::File(const QString &fileName)
    :CPP::Member(Member::Type::File)
{
    this->insert(Key::fileName,fileName);
}

void File::File::saveNameSpace(const Member &nameSpace)
{
    QFile file(getFileName().toLower()+".h");
    if( file.open(QIODeviceBase::ReadWrite | QIODevice::Text ) ){
        QTextStream out(&file);

        out << "#ifndef " + getFileName().toUpper()+"_H\n";
        out << "#define " + getFileName().toUpper()+"_H\n";

        QString code = this->recursiveFunc(nameSpace);

        out << code;



        out << "#endif ";

        file.close();
    }
}

QString File::File::getFileName() const
{
    return this->value(Key::fileName).toString();
}

QString File::File::recursiveFunc(const Member &member)
{
    QString code;

    if( member.getType() == CPP::Member::Type::NameSpace ){
        CPP::NameSpace::NameSpace _nameSpace(member);
        code += "namespace " + _nameSpace.getName() + " {\n";
        auto list = _nameSpace.memberList();
        for( const auto &_member : list ){
            code += this->recursiveFunc(_member);
        }
        code += "}// end namespace " + _nameSpace.getName() +"\n\n";
    }else if( member.getType() == CPP::Member::Type::Class ){
        CPP::Class::Class _class(member);
        code += "class "+_class.getName()+"\n";
        code += "{\n";
        code += "private:\n";

        code += "protected:\n";

        code += "public:\n";
        auto list = _class.publicMemberList();
        for( const auto &_member : list ){
            code += this->recursiveFunc(_member);
        }
        code += "};// end class " + _class.getName() + "\n\n";
    }else if( member.getType() == CPP::Member::Type::Function ){
        CPP::Function::Function _function(member);
        code += _function.getReturnType() + " " +_function.getName() + "();\n";
    }else if( member.getType() == CPP::Member::Type::Attribute ){
        CPP::Attribute::Attribute _attribute(member);
        QString constStr = _attribute.getIsReadOnly() ? "const" : "";
        QString initialValue = _attribute.getInitialValue().isEmpty() ? "" : _attribute.getInitialValue();
        code += constStr + " " + _attribute.getType() + " " + _attribute.getName() +"{"+initialValue+"};\n";
    }


    return code;

}

} // namespace CPP

