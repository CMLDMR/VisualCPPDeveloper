
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
    void addMember( const CPP::Member &member );

    bool saveMembers();
    bool saveFiles();
    bool openFile( const QString &name );

    void setIncludeFiles(const QString &newIncludeFiles);

    QString includeFiles() const;

private:
    QString mFileName;
    QFile mFile;
    QVector<CPP::Member> mMemberList;
    QString mIncludeFiles;

    QString recursiveHeaderFunc(const Member &member );
    QString recursiveSourceFunc(const Member &member );


    bool saveHeader(const Member &member);
    bool saveSource(const Member &member);
};
}


} // namespace CPP

#endif // CPP_FILE_H
