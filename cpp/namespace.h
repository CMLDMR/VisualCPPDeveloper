
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

    void appendMember(const CPP::Member &member);

private:
    QJsonArray mArray;
};

} // namespace NameSpace
} // namespace CPP

#endif // CPP_NAMESPACE_NAMESPACE_H
