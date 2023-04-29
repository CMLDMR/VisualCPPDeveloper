
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

    enum Role{
        Type = Qt::UserRole+1,
        Area,
        Function,

        lastRole = Qt::UserRole + 99
    };



    enum RoleArea{
        PUBLIC = lastRole+1,
        PROTECTED,
        PRIVATE
    };


    bool isAccepted() const;

    QString getClassName() const;
    QVector<CPP::Function::Function> getPrivateFunctionMemberList() const;
    QVector<CPP::Function::Function> getPublicFunctionMemberList() const;

private:
    QVBoxLayout* mMainLayout;

    QLineEdit* mClassNameLineEdit;


    QHBoxLayout* mHLayout;

    QWidget* mPrivateWidget;
    QVBoxLayout* mPrivateVLayout;
    QStandardItemModel* mPrivateFunctionMembersModel;
    QTableView* mPrivateMembersView;
    QHBoxLayout* mPrivateMembersControllerLayout;
    QPushButton* mAddPrivateFunctionMemberBtn;
    QPushButton* mAddPrivateAttributeMemberBtn;


    QWidget* mPublicWidget;
    QVBoxLayout* mPublicVLayout;
    QStandardItemModel* mPublicFunctionMembersModel;
    QTableView* mPublicMembersView;
    QHBoxLayout* mPublicMembersControllerLayout;
    QPushButton* mAddPublicFunctionMemberBtn;
    QPushButton* mAddPublicAttributeMemberBtn;




    QTextEdit* mProtectedMembers;
    QTextEdit* mPublicMembers;


    QHBoxLayout* mControllerLauout;
    QPushButton* mAcceptedBtn;
    QPushButton* mRejectBtn;

    bool mIsAccepted{false};
};

} // namespace GeneratorDialog

#endif // GENERATORDIALOG_CLASSDIALOG_H
