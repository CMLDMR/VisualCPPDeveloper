
#ifndef CPP_FILE_H
#define CPP_FILE_H

#include "member.h"

#include <QFile>
#include <QTextStream>
#include <QVector>

namespace CPP {

namespace File{
namespace Key{
inline const QString fileName{"fileName"};
inline const QString className{"className"};
}




class File
{
public:
    File( const QString &fileName );

    QString getFileName() const;


    void addFunction( const CPP::Member &functionMember );


    bool saveFile();

private:
    QString mFileName;
    QFile mFile;
    QVector<CPP::Member> mMemberList;
    QString recursiveHeaderFunc(const Member &member );
    QString recursiveSourceFunc(const Member &member );

    bool saveHeader(const Member &member);
    bool saveSource(const Member &member);


};







namespace legacy{
class File : public CPP::Member
{
public:
    File( const QString &fileName );

    void saveNameSpace(const CPP::Member &nameSpace);

    QString getFileName() const;


    void addFunction( const CPP::Member &functionMember );

    File *header() const;

private:
    QFile mFile;

    QString recursiveFunc(const Member &member );




    File *mHeader;
    File *mSource;

};
}

}


} // namespace CPP

#endif // CPP_FILE_H
