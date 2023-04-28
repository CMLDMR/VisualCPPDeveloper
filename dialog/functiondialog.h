
#ifndef GENERATORDIALOG_FUNCTIONDIALOG_H
#define GENERATORDIALOG_FUNCTIONDIALOG_H

#include <QDialog>

#include <QObject>
#include <QTextEdit>

class QVBoxLayout;
class QPushButton;
class QHBoxLayout;
class QLineEdit;
class QComboBox;


namespace GeneratorDialog {

class FunctionDialog : public QDialog
{
    Q_OBJECT
public:
    FunctionDialog();
    virtual ~FunctionDialog(){}


    bool isAccepted() const;

    QString getCode() const;
    void setCode( const QString &code );

    void setDeclaration( const QString &code );
    QString getDeclaration() const;

    void setDefination( const QString &code );
    QString getDefination() const;

    void setFunctionName( const QString &functionName );
    QString getFunctionName() const;

    void setFunctionType( const QString &type = "regular" );
    QString getFunctionType() const;

    void setReturnType( const QString &type = "void" );
    QString getReturnType() const;


private:

    QVBoxLayout* mMainLayout;
    QLineEdit* mFunctionNameLineEdit;
    QTextEdit* mTextEdit;

    QHBoxLayout* mDeclareLayout;
    QComboBox* mReturnTypeComboBox;
    QLineEdit* mDeclarationLineEdit;

    QHBoxLayout* mControllerLayout;
    QPushButton* mAcceptedBtn;
    QPushButton* mRejectedBtn;

    QComboBox* mFunctionType;

    bool mIsAccepted;


};

} // namespace GeneratorDialog

#endif // GENERATORDIALOG_FUNCTION_H
