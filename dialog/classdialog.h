
#ifndef GENERATORDIALOG_CLASSDIALOG_H
#define GENERATORDIALOG_CLASSDIALOG_H

#include <QDialog>
#include <QVector>

#include "cpp/function.h"

class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QTextEdit;
class QStandardItem;
class QStandardItemModel;
class QTableView;



namespace GeneratorDialog {

class ClassDialog : public QDialog
{
    Q_OBJECT
public:
    ClassDialog();

    enum RoleType{
        function
    };


    bool isAccepted() const;

    QString getClassName() const;
    QVector<CPP::Function::Function> getPrivateFunctionMemberList() const;

private:
    QVBoxLayout* mMainLayout;

    QLineEdit* mClassNameLineEdit;


    QStandardItemModel* mPrivateFunctionMembersModel;
    QTableView* mPrivateMembersView;
    QHBoxLayout* mPrivateMembersControllerLayout;
    QPushButton* mAddPrivateFunctionMemberBtn;



    QTextEdit* mProtectedMembers;
    QTextEdit* mPublicMembers;


    QHBoxLayout* mControllerLauout;
    QPushButton* mAcceptedBtn;
    QPushButton* mRejectBtn;

    bool mIsAccepted{false};
};

} // namespace GeneratorDialog

#endif // GENERATORDIALOG_CLASSDIALOG_H
