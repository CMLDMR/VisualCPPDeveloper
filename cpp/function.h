
#ifndef CPP_FUNCTION_FUNCTION_H
#define CPP_FUNCTION_FUNCTION_H

#include "member.h"



namespace CPP {
namespace Function {
namespace Key{
inline const QString name{"name"};
inline const QString functionType{"functionType"}; // virtual
inline const QString returnType{"returnType"};
inline const QString defaultParameter{"defaultParamter"};
inline const QString methodType{"methodType"}; // void int std::string
inline const QString isReadOnly{"isReadOnly"};
inline const QString implementationCode{"implementation"};
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
    QString getParameter() const;
    void setReturnType( const QString &returnType );
    void setFunctionType( const QString &functionType = "regular" );
    QString getFunctionType() const;
    void setReadOnly( const bool value = false );

    void setImplementation( const QString &implementationCode );
    QString getImplementation() const;

    QString getReturnType() const;


    enum class Type{
        Construction = 0,
        Destruction,
        Normal
    };
};

} // namespace Function
} // namespace CPP

#endif // CPP_FUNCTION_FUNCTION_H
