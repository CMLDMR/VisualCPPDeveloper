
#ifndef CPP_FILE_H
#define CPP_FILE_H

#include "member.h"



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

};
}


} // namespace CPP

#endif // CPP_FILE_H
