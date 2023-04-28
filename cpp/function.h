
#ifndef CPP_FUNCTION_FUNCTION_H
#define CPP_FUNCTION_FUNCTION_H

#include "member.h"



namespace CPP {
namespace Function {
namespace Key{
inline const QString name{"name"};
inline const QString functionType{"functionType"}; // virtual

inline const QString declaration{"declaration"};
inline const QString defination{"defination"};
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


    void setFunctionType( const QString &functionType = "regular" );
    QString getFunctionType() const;


    void setDeclaration( const QString &code );
    QString getDeclaration() const;

    void setDefination( const QString &code );
    QString getDefination() const;

};

} // namespace Function
} // namespace CPP

#endif // CPP_FUNCTION_FUNCTION_H
