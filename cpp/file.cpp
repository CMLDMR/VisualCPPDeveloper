
#include "file.h"
#include "cpp/namespace.h"
#include "cpp/class.h"
#include "cpp/function.h"
#include "cpp/attribute.h"
#include <QDir>
#include <QJsonDocument>

namespace CPP {

namespace File {
void File::setIncludeFiles(const QString &newIncludeFiles)
{
    mIncludeFiles = newIncludeFiles;
}

QString File::includeFiles() const
{
    return mIncludeFiles;
}

}


bool File::File::saveHeader(const Member &member)
{
    QDir dir;
    if( !dir.exists("code") ){
        dir.mkdir("code");
    }

    // For Header
    QFile file("code/"+getFileName().toLower()+".h");
    if( file.open(QIODeviceBase::ReadWrite | QIODevice::Text ) ){
        QTextStream out(&file);
        out << "#ifndef " + getFileName().toUpper()+"_H\n";
        out << "#define " + getFileName().toUpper()+"_H\n";

        out << "\n";
        out << mIncludeFiles+"\n";
        out << "\n";
        out << "\n";

        QString code = this->recursiveHeaderFunc(member);
        out << code;
        out << "\n";
        out << "#endif ";
        file.close();
        return true;
    }else{
        return false;
    }
}

bool File::File::saveSource(const Member &member)
{
    QDir dir;
    if( !dir.exists("code") ){
        dir.mkdir("code");
    }

    QFile file("code/"+getFileName().toLower()+".cpp");
    if( file.open(QIODeviceBase::ReadWrite | QIODevice::Text ) ){
        QTextStream out(&file);
        out << "#include \"" + getFileName()+".h\"\n";
        QString code = this->recursiveSourceFunc(member);
        out << code;
        file.close();
        return true;
    }else{
        return false;
    }
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

void File::File::addMember(const Member &member)
{
    mMemberList.append(member);
}

bool File::File::saveMembers()
{
    for( const auto &member : mMemberList ){
        // for header
        if( this->saveHeader(member) ){
            this->saveSource(member);
        }
    }
    return true;
}

bool File::File::saveFiles()
{
    QDir dir;
    if( !dir.exists("codeBase") ){
        dir.mkdir("codeBase");
    }
    QFile file("codeBase/"+getFileName().toLower()+".code");
    if( file.open(QIODeviceBase::ReadWrite | QIODevice::Text ) ){
        QTextStream out(&file);

        out << static_cast<int>(mMemberList.size());
        for( const auto &item : mMemberList ){
            out << QJsonDocument(item).toJson();
            out << mIncludeFiles;
        }
        file.close();
        return true;
    }else{
        return false;
    }
}

bool File::File::openFile(const QString &name)
{
    QFile file("codeBase/"+name);
    if( file.open(QIODevice::ReadOnly) ){
        QDataStream in(&file);
        int sizeT;

        in >> sizeT;

        for( int i = 0 ; i < sizeT ; i++ ){
            Member member;
            QString mIncludeFiles;
            in >> member;
            in >> mIncludeFiles;
            if( member.getType() == Member::Type::Function ){
                this->addFunction(member);
            }
        }
        file.close();
        return true;
    }else{
        return false;
    }
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
        code += _class.generateHeaderCode();

    }else if( member.getType() == CPP::Member::Type::Function ){

        CPP::Function::Function _function(member);
        code += _function.generateHeaderCode();

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

    switch (member.getType()) {
    case CPP::Member::Type::Function:
    {
        CPP::Function::Function _function(member);
        code += _function.generateSourceCode();
    }
        break;

    case CPP::Member::Type::Class:
    {
        CPP::Class::Class _class(member);
        code += _class.generateSourceCode();
    }
    break;
    default:
        break;
    }
    return code;
}








































} // namespace CPP

