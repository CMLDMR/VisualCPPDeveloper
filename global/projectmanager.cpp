
#include "projectmanager.h"
#include <mutex>

#include <QDir>
#include <QDataStream>
#include <QFile>
#include <QByteArray>

#include "cpp/attribute.h"
#include "cpp/class.h"
#include "cpp/file.h"
#include "cpp/function.h"
#include "cpp/namespace.h"



namespace Global {


std::once_flag mProjectManager_flag;
Global::ProjectManager* Global::ProjectManager::mProjectManager = nullptr;

ProjectManager *ProjectManager::instance()
{
     std::call_once(mProjectManager_flag,[=](){
        mProjectManager = new ProjectManager();
    });
    return mProjectManager;
}

void ProjectManager::append(const CPP::Member &member)
{
    this->mItemList.append(member);
}

const CPP::Member &ProjectManager::operator [](const int index) const
{
    return mItemList[index];
}

const CPP::Member* ProjectManager::getByName(const QString &name) const
{
    CPP::Member member;

    auto item = std::find_if(std::begin(mItemList),std::end(mItemList),[ &name](CPP::Member _member){
        return _member.getName() == name;
    });

    if( item != mItemList.end() ){
        return item;
    }else{
        return nullptr;
    }

}

ProjectManager::ProjectManager(QObject *parent)
    : QObject{parent}
{

}

bool ProjectManager::saveHeader(const CPP::Member &member)
{

    QDir dir(mProjectLocation);
    if( !dir.exists("headers") ){
        dir.mkdir("headers");
    }

    QString fileName = mProjectLocation+"/headers/"+member.getName().toLower()+".h";


    // For Header
    QFile file(fileName);
    if( file.exists() ){
        file.remove();
    }
    if( file.open(QIODeviceBase::ReadWrite | QIODevice::Text ) ){
        QTextStream out(&file);
        out << "#ifndef " + member.getName().toUpper()+"_H\n";
        out << "#define " + member.getName().toUpper()+"_H\n";

        out << "\n";
        if( !member.getIncludeFiles().isEmpty() ){
            out << member.getIncludeFiles()+"\n";
            out << "\n";
            out << "\n";
        }

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

bool ProjectManager::saveSource(const CPP::Member &member)
{
    QDir dir(mProjectLocation);
    if( !dir.exists("src") ){
        dir.mkdir("src");
    }

    QString filename = mProjectLocation+"/src/"+member.getName().toLower()+".cpp";

    QFile file(filename);

    if( file.exists() ){
        file.remove();
    }

    if( file.open(QIODeviceBase::ReadWrite | QIODevice::Text ) ){
        QTextStream out(&file);
        out << "#include \"" + member.getName()+".h\"\n";
        QString code = this->recursiveSourceFunc(member);
        out << code;
        file.close();
        return true;
    }else{
        return false;
    }

    return false;
}

QString ProjectManager::recursiveHeaderFunc(const CPP::Member &member)
{
    QString code;

    if( member.getType() == CPP::Member::Type::NameSpace ){
        CPP::NameSpace::NameSpace _nameSpace(member);
        code += "namespace " + _nameSpace.getName() + " {\n";
        auto list = _nameSpace.memberList();
        for( const auto &_member : list ){
            code += this->recursiveHeaderFunc(_member);
        }
        code +="\n";
        code +="\n";
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

QString ProjectManager::recursiveSourceFunc(const CPP::Member &member)
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

    case CPP::Member::Type::NameSpace:
    {
        CPP::NameSpace::NameSpace _namespace(member);
        code += _namespace.generateSourceCode();
    }
    break;
    default:
        break;
    }
    return code;
}

QString ProjectManager::projectLocation() const
{
    return mProjectLocation;
}

void ProjectManager::setProjectLocation(const QString &newProjectLocation)
{
    mProjectLocation = newProjectLocation;
}

void ProjectManager::newProject(const QString &projectName, const QString &projectPath)
{
    this->setProjectName(projectName);
    this->setProjectLocation(projectPath);
    mItemList.clear();
}

void ProjectManager::generateCode(const CPP::Member &member)
{
    this->saveHeader(member);
    this->saveSource(member);
}

void ProjectManager::save()
{
    //TODO: return error if no Project File Specified

    QDir dir;

    if( !dir.exists("package") ){
        dir.mkdir("package");
    }

    if( !dir.exists("src") ){
        dir.mkdir("src");
    }

    if( !dir.exists("headers") ){
        dir.mkdir("headers");
    }

    mConfigObject.insert("ProjectName",mProjectName);
    mConfigObject.insert("Location",mProjectLocation);

    QJsonArray itemList;
    for( const auto &item : mItemList ){
        itemList.append(item);
    }

    mConfigObject.insert("Items",itemList);

    QFile file(mProjectLocation+"/package/"+mProjectName+".pack");

    if( file.open(QIODevice::ReadWrite) ){
        QDataStream out(&file);
        out << mConfigObject;
        file.close();
    }else{
        //TODO: Error if Project Can not be Saved
        qDebug() << "can not save project";
    }

}

QString ProjectManager::projectName() const
{
    return mProjectName;
}

void ProjectManager::setProjectName(const QString &newProjectName)
{
    mProjectName = newProjectName;
}

} // namespace Global

