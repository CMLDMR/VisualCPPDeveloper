
#include "file.h"
#include "cpp/namespace.h"
#include "cpp/class.h"
#include "cpp/function.h"
#include "cpp/attribute.h"

namespace CPP {

bool File::File::saveHeader(const Member &member)
{
    // For Header
    QFile file(getFileName().toLower()+".h");
    if( file.open(QIODeviceBase::ReadWrite | QIODevice::Text ) ){
        QTextStream out(&file);
        out << "#ifndef " + getFileName().toUpper()+"_H\n";
        out << "#define " + getFileName().toUpper()+"_H\n";
        QString code = this->recursiveHeaderFunc(member);
        out << code;
        out << "#endif ";
        file.close();
        return true;
    }else{
        return false;
    }
}

bool File::File::saveSource(const Member &member)
{
    bool saveSuccess = false;
    // TODO: For Source
    QFile file(getFileName().toLower()+".cpp");
    if( file.open(QIODeviceBase::ReadWrite | QIODevice::Text ) ){
        QTextStream out(&file);
        out << "#include \"" + getFileName()+".h\"\n";
        QString code = this->recursiveSourceFunc(member);
        out << code;
        file.close();
    }
    return saveSuccess;
}

File::File::File(const QString &fileName)
{
    mFileName =fileName;
}

QString File::File::getFileName() const
{
    return mFileName;
}

void File::File::addFunction(const Member &functionMember)
{
    mMemberList.append(functionMember);
}

bool File::File::saveFile()
{
    for( const auto &member : mMemberList ){
        // for header
        if( this->saveHeader(member) ){
            this->saveSource(member);
        }
    }
    return true;
}

QString File::File::recursiveHeaderFunc(const Member &member)
{
    QString code;

    if( member.getType() == CPP::Member::Type::NameSpace ){
        CPP::NameSpace::NameSpace _nameSpace(member);
        code += "namespace " + _nameSpace.getName() + " {\n";
        auto list = _nameSpace.memberList();
        for( const auto &_member : list ){
            code += this->recursiveHeaderFunc(_member);
        }
        code += "}// end namespace " + _nameSpace.getName() +"\n\n";


    }else if( member.getType() == CPP::Member::Type::Class ){
        CPP::Class::Class _class(member);
        code += "class "+_class.getName()+"\n";
        code += "{\n";
        code += "private:\n";
        auto list = _class.privateMemberList();
        for( const auto &_member : list ){
            code += this->recursiveHeaderFunc(_member);
        }
        code += "\n";
        code += "protected:\n";
        list = _class.protectedMemberList();
        for( const auto &_member : list ){
            code += this->recursiveHeaderFunc(_member);
        }
        code += "\n";
        code += "public:\n";
        list = _class.publicMemberList();
        for( const auto &_member : list ){
            code += this->recursiveHeaderFunc(_member);
        }
        code += "\n";
        code += "};// end class " + _class.getName() + "\n\n";


    }else if( member.getType() == CPP::Member::Type::Function ){
        CPP::Function::Function _function(member);
        code += "\n";
        code += _function.getReturnType() + " " +_function.getName() + "(" + _function.getParameter() + ");\n";
        code += "\n";

    }else if( member.getType() == CPP::Member::Type::Attribute ){
        CPP::Attribute::Attribute _attribute(member);
        QString constStr = _attribute.getIsReadOnly() ? "const" : "";
        QString initialValue = _attribute.getInitialValue().isEmpty() ? "" : _attribute.getInitialValue();
        code += constStr + " " + _attribute.getType() + " " + _attribute.getName() +"{"+initialValue+"};\n";
    }

    return code;
}

QString File::File::recursiveSourceFunc(const Member &member)
{

    QString code;

    if( member.getType() == CPP::Member::Type::NameSpace ){

    }else if( member.getType() == CPP::Member::Type::Class ){

    }else if( member.getType() == CPP::Member::Type::Function ){
        CPP::Function::Function _function(member);
        code += "\n";
        code += _function.getReturnType() + " " +_function.getName() + "(" + _function.getParameter() + ")\n";
        code += "{\n";
        code += "\n";
        code += _function.getImplementation();
        code += "\n";
        code += "\n";
        code += "}\n";
        code += "\n";

    }else if( member.getType() == CPP::Member::Type::Attribute ){

    }

    return code;
}





































namespace File{
namespace legacy {

File::File(const QString &fileName)
    :CPP::Member(Member::Type::File)
{
    this->insert(Key::fileName,fileName);
}

void File::saveNameSpace(const Member &nameSpace)
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

QString File::getFileName() const
{
    return this->value(Key::fileName).toString();
}

void File::addFunction(const Member &functionMember)
{

    this->insert("function",functionMember);

    qDebug() << *this;



}

QString File::recursiveFunc(const Member &member)
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
        auto list = _class.privateMemberList();
        for( const auto &_member : list ){
            code += this->recursiveFunc(_member);
        }
        code += "\n";
        code += "protected:\n";
        list = _class.protectedMemberList();
        for( const auto &_member : list ){
            code += this->recursiveFunc(_member);
        }
        code += "\n";
        code += "public:\n";
        list = _class.publicMemberList();
        for( const auto &_member : list ){
            code += this->recursiveFunc(_member);
        }
        code += "\n";
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

}

}



} // namespace CPP

