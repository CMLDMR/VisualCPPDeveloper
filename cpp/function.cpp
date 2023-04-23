
#include "function.h"

namespace CPP {
namespace Function {

Function::Function(const QString &functionName)
    :CPP::Member(CPP::Member::Type::Function)
{
    this->insert(Key::functionType,"Normal");
    this->setFunctionType(MethodType::Normal);
    this->setReadOnly();
}

void Function::setThisConstruction()
{
    this->insert(Key::functionType,"Construction");
    setReturnType("");
}

void Function::setThisDesConstruction()
{
    this->insert(Key::functionType,"Destruction");
    setReturnType("");
}

void Function::setParameter(const QString &parameter)
{
    this->insert(Key::defaultParameter,parameter);
}

void Function::setReturnType(const QString &returnType)
{
    this->insert(Key::returnType,returnType);

}

void Function::setFunctionType(const MethodType &methodType)
{
    switch (methodType) {
    case MethodType::Normal:
        this->insert(Key::methodType,"Normal");
        break;
    case MethodType::Virtual:
        this->insert(Key::methodType,"Virtual");
        break;
    case MethodType::PureVirtual:
        this->insert(Key::methodType,"PureVirtual");
        break;
    default:
        break;
    }
}

void Function::setReadOnly(const bool value)
{
    this->insert(Key::isReadOnly,value);
}

} // namespace Function
} // namespace CPP

