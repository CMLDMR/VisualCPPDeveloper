
#include "function.h"

namespace CPP {
namespace Function {

Function::Function(const QString &functionName)
    :CPP::Member(CPP::Member::Type::Function)
{
    this->setName(functionName);
    this->setFunctionType("Normal");
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
}

void Function::setThisDesConstruction()
{
    this->insert(Key::functionType,"Destruction");
}



void Function::setFunctionType(const QString &functionType)
{
    this->insert(Key::functionType,functionType);
}

QString Function::getFunctionType() const
{
    return this->value(Key::functionType).toString();
}


void Function::setDeclaration(const QString &code)
{
    this->insert(Key::declaration,code);
}

QString Function::getDeclaration() const
{
    return this->value(Key::declaration).toString();
}

void Function::setDefination(const QString &code)
{
    this->insert(Key::defination,code);
}

QString Function::getDefination() const
{
    return this->value(Key::defination).toString();
}



} // namespace Function
} // namespace CPP

