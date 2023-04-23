
#ifndef CPP_CLASS_MEMBER_H
#define CPP_CLASS_MEMBER_H

#include <QJsonObject>

#include <QDebug>

namespace CPP {

class Member : public QJsonObject
{
public:

    enum class Type;
    explicit Member();
    Member(const Type &type);
    Member(const Member &other);
    Member &setName( const QString &name );
    Member &setType( const QString &type );
    Type getType() const;

    QString getName() const;

    void setJsonObject( const Member &obj );
    void setJsonObject( const QJsonObject &obj );

    Member &operator=( const Member &other);


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
