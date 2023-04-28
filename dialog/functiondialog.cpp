
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

    mIsAccepted = false;

    mMainLayout = new QVBoxLayout();

    this->setLayout(mMainLayout);

    mMainLayout->addWidget(new QLabel("Function Detail"));


    mFunctionNameLineEdit = new QLineEdit();
    mMainLayout->addWidget(mFunctionNameLineEdit);

    mFunctionType = new QComboBox();
    mFunctionType->addItem("regular");
    mFunctionType->addItem("virtual");
    mMainLayout->addWidget(mFunctionType);

    mReturnTypeLineEdit = new QLineEdit();
    mReturnTypeLineEdit->setPlaceholderText("Return Type");

    mParametersLineEdit = new QLineEdit();
    mParametersLineEdit->setPlaceholderText("Function Parameters");
    mMainLayout->addWidget(mReturnTypeLineEdit);
    mMainLayout->addWidget(mParametersLineEdit);


    mTextEdit = new QTextEdit();
    mMainLayout->addWidget(new QLabel("Implementation"));
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

void FunctionDialog::setParaMeterCode(const QString &code)
{
    mParametersLineEdit->setText(code);
}

QString FunctionDialog::getParameterCode() const
{
    return mParametersLineEdit->text();
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

void FunctionDialog::setReturnTypeCode(const QString &code)
{
    mReturnTypeLineEdit->setText(code);
}

QString FunctionDialog::getReturnTypeCode() const
{
    return mReturnTypeLineEdit->text();
}

} // namespace GeneratorDialog

