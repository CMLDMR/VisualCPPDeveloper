
#include "functiondialog.h"

#include "global/highlighter.h"
#include "global/textedit.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QCompleter>
#include <QStringListModel>
#include <QAbstractItemView>


namespace GeneratorDialog {

FunctionDialog::FunctionDialog()
{

    this->setWindowTitle("Add Function");

    mIsAccepted = false;

    mMainLayout = new QVBoxLayout();

    this->setLayout(mMainLayout);

    mFunctionNameLineEdit = new QLineEdit();
    mFunctionNameLineEdit->setPlaceholderText("Function Name");
    mMainLayout->addWidget(mFunctionNameLineEdit);

    mFunctionType = new QComboBox();
    mFunctionType->addItem("regular");
    mFunctionType->addItem("virtual");
    mFunctionType->addItem("construction");
    mFunctionType->addItem("destruction");
    mMainLayout->addWidget(mFunctionType);

    mDeclareLayout = new QHBoxLayout();
    mReturnTypeComboBox = new QComboBox();
    mReturnTypeComboBox->addItem("void");
    mReturnTypeComboBox->addItem("int");
    mReturnTypeComboBox->addItem("double");
    mDeclareLayout->addWidget(mReturnTypeComboBox);

    mDeclarationLineEdit = new QLineEdit();
    mDeclarationLineEdit->setPlaceholderText("Declaration");
    mDeclareLayout->addWidget(mDeclarationLineEdit);

    mParameterLineEdit = new QLineEdit();
    mParameterLineEdit->setPlaceholderText("Parameter");
    mDeclareLayout->addWidget(mParameterLineEdit);


    mMainLayout->addLayout(mDeclareLayout);

    QObject::connect(mFunctionNameLineEdit,&QLineEdit::textEdited,[=]( const QString &txt){
        mDeclarationLineEdit->setText(txt);
        mDeclarationLineEdit->setEnabled(false);
    });


    mDefinationTextEdit = new Global::TextEdit();
    mMainLayout->addWidget(new QLabel("Defination"));
    mHighLighter = new Global::Highlighter();
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    mDefinationTextEdit->setFont(font);
    mHighLighter->setDocument(mDefinationTextEdit->document());
    mMainLayout->addWidget(mDefinationTextEdit);


    //TODO: Complete Completer and update Completer Database

    QStringList mList;
    mList.append("class");
    mList.append("int");
    mList.append("kestane");
    mList.append("Global");
    mList.append("Global1");

    auto model = new QStringListModel(completer);


    model->setStringList(mList);


    completer = new QCompleter(mList,mDefinationTextEdit);
//    completer->setModel(model);
//    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    mDefinationTextEdit->setCompleter(completer);

//    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
//    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    completer->setWrapAround(false);
//    completer->setCompletionMode(QCompleter::PopupCompletion);
//    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    QObject::connect(completer, QOverload<const QString &>::of(&QCompleter::activated),
//                     [=](const QString &completion){
//                         if (completer->widget() != this)
//                             return;
//                         QTextCursor tc = mDefinationTextEdit->textCursor();
//                         int extra = completion.length() - completer->completionPrefix().length();
//                         tc.movePosition(QTextCursor::Left);
//                         tc.movePosition(QTextCursor::EndOfWord);
//                         tc.insertText(completion.right(extra));
//                         mDefinationTextEdit->setTextCursor(tc);
//                     });

//    QObject::connect(mDefinationTextEdit, &QTextEdit::textChanged,
//                     [=](){
//                         auto xPos = mDefinationTextEdit->cursorRect().x();
//                         auto yPos = mDefinationTextEdit->cursorRect().y();
//                         auto point = this->mapToGlobal(QPointF(xPos,yPos));
//                         completer->popup()->setGeometry(point.x(),point.y(),250,350);
//                         completer->popup()->show();
//                         qDebug() << "changed";
//                     });


//    mDefinationTextEdit->setCompleter(completer);



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
    return mDefinationTextEdit->toPlainText();
}

void FunctionDialog::setCode(const QString &code)
{
    mDefinationTextEdit->setPlainText(code);
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
    mDefinationTextEdit->setText(code);
}

QString FunctionDialog::getDefination() const
{
    return mDefinationTextEdit->toPlainText();
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

void FunctionDialog::setReturnType(const QString &type)
{
    mReturnTypeComboBox->setCurrentText(type);
}

QString FunctionDialog::getReturnType() const
{
    return mReturnTypeComboBox->currentText();
}

CPP::Function::Function FunctionDialog::getFunction() const
{

    CPP::Function::Function function(mFunctionNameLineEdit->text());
    function.setDefination(mDefinationTextEdit->toPlainText());
    function.setReturnType(mReturnTypeComboBox->currentText());
    function.setDeclaration(mDeclarationLineEdit->text());
    function.setParameter(mParameterLineEdit->text());
    return function;
}



} // namespace GeneratorDialog

