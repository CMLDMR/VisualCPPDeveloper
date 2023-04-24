
#ifndef CPP_ATTRIBUTE_ATTRIBUTE_H
#define CPP_ATTRIBUTE_ATTRIBUTE_H

#include "cpp/member.h"



namespace CPP {
namespace Attribute {

namespace Key{
inline const QString name{"name"};
inline const QString Type{"Type"};
inline const QString defaultValue{"defaultValue"};
inline const QString isReadOnly{"isReadOnly"};
}

class Attribute : public CPP::Member
{
public:
    Attribute(const QString &name);
    Attribute(const Member &other);

    void setInitialValue( const QString &value );
    void setReadOnly( const bool value = false );
    void setType( const QString type );

    bool getIsReadOnly() const;
    QString getInitialValue() const;
    QString getType() const;

};

} // namespace Attribute
} // namespace CPP

#endif // CPP_ATTRIBUTE_ATTRIBUTE_H
