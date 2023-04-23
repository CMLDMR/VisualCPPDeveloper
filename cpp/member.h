
#ifndef CPP_CLASS_MEMBER_H
#define CPP_CLASS_MEMBER_H

#include <QJsonObject>

#include <QDebug>

namespace CPP {

class Member : public QJsonObject
{
public:

    enum class Type;
    Member(const Type &type );
    Member &setName( const QString &name );
    Member &setType( const QString &type );


private:
    Type mType;

public:
    enum class Type{
        Constructor = 0,
        Destructor,
        Function,
        Operator,
        Attribute,
        Class,
        NameSpace,
        File
    };
};

} // namespace CPP

#endif // CPP_CLASS_MEMBER_H
