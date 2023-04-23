
#ifndef CPP_CLASS_CLASS_H
#define CPP_CLASS_CLASS_H

#include "cpp/member.h"
#include <QJsonArray>



namespace CPP {
namespace Class {

namespace Key{
inline const QString name{"name"};
inline const QString construction{"construction"};
inline const QString destruction{"destruction"};
inline const QString publicArea{"public"};
inline const QString protectedArea{"protected"};
inline const QString privateArea{"private"};

}

class Class : public Member
{
public:
    explicit Class( const QString &className );
    Class( const Member &member );

    Class &appendPublic( const CPP::Member &member );
    Class &appendPrivate( const CPP::Member &member );

    QList<Member> publicMemberList() const;


private:
    QJsonArray mPublic;
    QJsonArray mProtected;
    QJsonArray mPrivate;


};

} // namespace Class
} // namespace CPP

#endif // CPP_CLASS_CLASS_H
