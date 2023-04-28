
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


void Function::setFunctionType(const QString &functionType)
{
    this->insert(Key::functionType,functionType);
}

QString Function::getFunctionType() const
{
    return this->value(Key::functionType).toString();
}

void Function::setParameter(const QString &code)
{
    this->insert(Key::parameter,code);
}

QString Function::getParameter() const
{
    return this->value(Key::parameter).toString();
}

void Function::setReturnType(const QString &code)
{
    this->insert(Key::returnType,code);
}

QString Function::getReturnType() const
{
    return this->value(Key::returnType).toString();
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

QString Function::generateHeaderCode() const
{
    QString code;
    code += "\n";
    code += this->getReturnType() + " " +this->getDeclaration()+"( " + this->getParameter() + " );\n";
    code += "\n";
    return code;
}

QString Function::generateSourceCode() const
{
    QString code;
    code += "\n";
    code += this->getReturnType() + " " +this->getDeclaration()+"( "+this->getParameter()+" )\n";
    code += "{\n";
    code += "\n";
    code += this->getDefination();
    code += "\n";
    code += "\n";
    code += "}\n";
    code += "\n";
    return code;
}



} // namespace Function
} // namespace CPP

