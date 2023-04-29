
#ifndef CPP_NAMESPACE_NAMESPACE_H
#define CPP_NAMESPACE_NAMESPACE_H

#include "member.h"

#include <QJsonArray>


namespace CPP {
namespace NameSpace {

namespace Key{
inline const QString name{"name"};
inline const QString elements{"elements"};
}

class NameSpace : public CPP::Member
{
public:
    NameSpace(const QString &nameSpaceName );
    NameSpace(const NameSpace &other );

    NameSpace(const Member &other);

    void appendMember(const CPP::Member &member);

    QList<Member> memberList() const;

    QString generateHeaderCode() ;
    QString generateSourceCode() ;

private:
};

} // namespace NameSpace
} // namespace CPP

#endif // CPP_NAMESPACE_NAMESPACE_H
