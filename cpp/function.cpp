
#include "function.h"

namespace CPP {
namespace Function {

Function::Function(const QString &functionName)
    :CPP::Member(CPP::Member::Type::Function)
{
    this->setName(functionName);
    this->setFunctionType("Normal");
    this->setReadOnly();
}

Function::Function(const Function &other)
{
    this->setJsonObject(other);
}

Function::Function(const Member &other)
{
    this->setJsonObject(other);
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

QString Function::getParameter() const
{
    return this->value(Key::defaultParameter).toString();
}

void Function::setReturnType(const QString &returnType)
{
    this->insert(Key::returnType,returnType);

}

void Function::setFunctionType(const QString &functionType)
{
    this->insert(Key::functionType,functionType);
}

QString Function::getFunctionType() const
{
    return this->value(Key::functionType).toString();
}

void Function::setReadOnly(const bool value)
{
    this->insert(Key::isReadOnly,value);
}

void Function::setImplementation(const QString &implementationCode)
{
    this->insert(Key::implementationCode,implementationCode);
}

QString Function::getImplementation() const
{
    return this->value(Key::implementationCode).toString();
}

QString Function::getReturnType() const
{
    return this->value(Key::returnType).toString();
}

} // namespace Function
} // namespace CPP

