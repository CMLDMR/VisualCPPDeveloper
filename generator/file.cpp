
#include "file.h"
#include <QTextStream>
#include <QString>
#include <QDebug>

namespace Generator {

File::File()
{

}

bool File::saveHeader(const QString &fileName, const QString &header)
{

    this->setFileName(fileName.toLower()+".h");
    if( this->open(QIODevice::ReadWrite|QIODevice::Text) ){
        QTextStream out(this);
        out << header;
        this->close();
        return true;
    }else{
        return false;
    }

}

bool File::saveCpp(const QString &fileName, const QString &cpp)
{
    this->setFileName(fileName.toLower()+".cpp");
    if( this->open(QIODevice::ReadWrite|QIODevice::Text) ){
        QTextStream out(this);
        out << cpp;
        this->close();
        return true;
    }else{
        return false;
    }

}

void File::removeFile(const QString &fileName)
{

}

//Class::Class::Class()
//{

//}

//void Class::Class::setClassName(const QString &newClassName)
//{
//    mClassObj[Key::className] = newClassName;
//}






//Class::Class &Class::Class::appendCode(const QString &code)
//{

//    return *this;
//}

//Class::Class &Class::Class::appendLine(const QString &code)
//{
//    QString str;
//    for( const auto &item : mIndent ){
//        str += item;
//    }
//    mCode.append(str+code+"\n");
//    return *this;
//}

//Class::Class &Class::Class::endLine()
//{
//    return *this;
//}

//bool Class::Class::saveClass()
//{
//    if( mClassObj[Key::className].toString().isEmpty() ){
//        qDebug() << __LINE__ <<"Class Name Required";
//        return false;
//    }

//    if( this->saveHeader(mClassObj[Key::className].toString(),this->buildHeaderCode()) ){
//        if( saveCpp(mClassObj[Key::className].toString(),this->buildCppCode()) ){
//            return true;
//        }else{
//            return false;
//        }
//    }else{
//        return false;
//    }
//}

//QString Class::Class::buildHeaderCode()
//{
//    mCode.clear();

//    this->appendLine("#ifndef "+ mClassObj[Key::className].toString().toUpper()+"_H");
//    this->appendLine("#define "+ mClassObj[Key::className].toString().toUpper()+"_H");
//    this->appendLine("");

//    this->appendLine("class "+ mClassObj[Key::className].toString());
//    this->appendLine("{");


//    this->appendLine("};");





//    return mCode;
//}

//QString Class::Class::buildCppCode()
//{



//    return "code";


//}

} // namespace Generator

