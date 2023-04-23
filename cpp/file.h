
#ifndef CPP_FILE_H
#define CPP_FILE_H

#include "member.h"

#include <QFile>
#include <QTextStream>

namespace CPP {

namespace File{
namespace Key{
inline const QString fileName{"fileName"};
inline const QString className{"className"};
}



class File : public CPP::Member
{
public:
    File( const QString &fileName );

    void saveNameSpace(const CPP::Member &nameSpace);

    QString getFileName() const;

private:
    QFile mFile;

    QString recursiveFunc(const Member &member );

};
}


} // namespace CPP

#endif // CPP_FILE_H
