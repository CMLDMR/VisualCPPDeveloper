
#ifndef GENERATOR_FILE_H
#define GENERATOR_FILE_H

#include <QFile>
#include <QStringList>
#include <tuple>
#include <QVector>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>


namespace Generator {

class File : private QFile
{
public:
    File();
    bool saveHeader(const QString &fileName , const QString &header);
    bool saveCpp(const QString &fileName , const QString &cpp);

    void removeFile( const QString &fileName );
};

//namespace Class{

//    namespace Key{
//    static inline const QString className{"className"};

//    }

//    class Class : public File
//    {
//    public:
//        Class();

//        void setClassName(const QString &newClassName);

//        bool saveClass();

//    private:

//        Class &appendCode( const QString &code );
//        Class &appendLine( const QString &code );

//        Class &endLine();

//        QString mCode;

//        QJsonObject mClassObj;

//        QStringList mIndent;

//        QString buildHeaderCode();
//        QString buildCppCode();

//    };
//}


} // namespace Generator

#endif // GENERATOR_FILE_H
