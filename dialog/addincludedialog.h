
#ifndef GENERATORDIALOG_ADDINCLUDEDIALOG_H
#define GENERATORDIALOG_ADDINCLUDEDIALOG_H

#include <QDialog>

#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>


namespace GeneratorDialog {

class AddIncludeDialog : public QDialog
{
public:
    AddIncludeDialog();

    bool isAccepted() const;

    QString getIncludeFiles() const;
    void setIncludeFiles( const QString &code );

private:
    QVBoxLayout* mMainLayout;
    QTextEdit* mTextEdit;
    QHBoxLayout* mControllerLayout;
    QPushButton* mAcceptedBtn;
    QPushButton* mRejectedBtn;

    bool mIsAccepted{false};
};

} // namespace GeneratorDialog

#endif // GENERATORDIALOG_ADDINCLUDE_H
