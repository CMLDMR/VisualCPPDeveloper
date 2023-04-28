
#include "functiondialog.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>

namespace GeneratorDialog {

FunctionDialog::FunctionDialog()
{

    this->setWindowTitle("Add Function");

    mIsAccepted = false;

    mMainLayout = new QVBoxLayout();

    this->setLayout(mMainLayout);

    mMainLayout->addWidget(new QLabel("Function Detail"));


    mFunctionNameLineEdit = new QLineEdit();
    mMainLayout->addWidget(mFunctionNameLineEdit);

    mFunctionType = new QComboBox();
    mFunctionType->addItem("regular");
    mFunctionType->addItem("virtual");
    mFunctionType->addItem("construction");
    mFunctionType->addItem("destruction");
    mMainLayout->addWidget(mFunctionType);

    mDeclarationLineEdit = new QLineEdit();
    mDeclarationLineEdit->setPlaceholderText("Declaration");
    mMainLayout->addWidget(mDeclarationLineEdit);


    mTextEdit = new QTextEdit();
    mMainLayout->addWidget(new QLabel("Defination"));
    mMainLayout->addWidget(mTextEdit);


    mControllerLayout = new QHBoxLayout();
    mAcceptedBtn = new QPushButton("OK");
    mControllerLayout->addWidget(mAcceptedBtn);

    mRejectedBtn = new QPushButton("Cancel");
    mControllerLayout->addWidget(mRejectedBtn);

    mMainLayout->addLayout(mControllerLayout);

    QObject::connect(mAcceptedBtn,&QPushButton::clicked,[=](){
        mIsAccepted = true;
        this->close();
    });

    QObject::connect(mRejectedBtn,&QPushButton::clicked,[=](){
        mIsAccepted = false;
        this->close();
    });
}

bool FunctionDialog::isAccepted() const
{
    return mIsAccepted;
}

QString FunctionDialog::getCode() const
{
    return mTextEdit->toPlainText();
}

void FunctionDialog::setCode(const QString &code)
{
    mTextEdit->setPlainText(code);
}

void FunctionDialog::setDeclaration(const QString &code)
{
    mDeclarationLineEdit->setText(code);
}

QString FunctionDialog::getDeclaration() const
{
    return mDeclarationLineEdit->text();
}

void FunctionDialog::setDefination(const QString &code)
{
    mTextEdit->setText(code);
}

QString FunctionDialog::getDefination() const
{
    return mTextEdit->toPlainText();
}

void FunctionDialog::setFunctionName(const QString &functionName)
{
    mFunctionNameLineEdit->setText(functionName);
}

QString FunctionDialog::getFunctionName() const
{
    return mFunctionNameLineEdit->text();
}

void FunctionDialog::setFunctionType(const QString &type)
{
    mFunctionType->setCurrentText(type);
}

QString FunctionDialog::getFunctionType() const
{
    return mFunctionType->currentText();
}


} // namespace GeneratorDialog

