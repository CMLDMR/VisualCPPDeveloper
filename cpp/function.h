
#ifndef CPP_FUNCTION_FUNCTION_H
#define CPP_FUNCTION_FUNCTION_H

#include "member.h"



namespace CPP {
namespace Function {
namespace Key{
inline const QString name{"name"};
inline const QString functionType{"functionType"};
inline const QString returnType{"returnType"};
inline const QString defaultParameter{"defaultParamter"};
inline const QString methodType{"methodType"};
inline const QString isReadOnly{"isReadOnly"};


}

class Function : public CPP::Member
{
public:
    enum class Type;
    enum class MethodType;

    Function( const QString &functionName );
    Function( const Function &other );
    Function( const Member &other );

    void setThisConstruction();
    void setThisDesConstruction();

    void setParameter( const QString &parameter );
    void setReturnType( const QString &returnType );
    void setFunctionType(const MethodType &methodType );
    void setReadOnly( const bool value = false );

    QString getReturnType() const;


    enum class Type{
        Construction = 0,
        Destruction,
        Normal
    };

    enum class MethodType{
        Normal = 0,
        Virtual,
        PureVirtual
    };
};

} // namespace Function
} // namespace CPP

#endif // CPP_FUNCTION_FUNCTION_H
