
#include "classdialog.h"

#include "cpp/function.h"

#include "dialog/functiondialog.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>

namespace GeneratorDialog {

ClassDialog::ClassDialog()
{

    mMainLayout = new QVBoxLayout();

    this->setLayout(mMainLayout);

    mMainLayout->addWidget(new QLabel("Class "));

    mClassNameLineEdit = new QLineEdit();
    mClassNameLineEdit->setPlaceholderText("Type Class Name");
    mMainLayout->addWidget(mClassNameLineEdit);

    mMainLayout->addWidget(new QLabel("Private Members"));
    mPrivateFunctionMembersModel = new QStandardItemModel();

    mPrivateMembersView = new QTableView();
    mPrivateMembersView->setModel(mPrivateFunctionMembersModel);
    mMainLayout->addWidget(mPrivateMembersView);

    mPrivateMembersControllerLayout = new QHBoxLayout();
    mAddPrivateFunctionMemberBtn = new QPushButton("Add Private Function Member");
    mPrivateMembersControllerLayout->addWidget(mAddPrivateFunctionMemberBtn);
    mMainLayout->addLayout(mPrivateMembersControllerLayout);

    mMainLayout->addWidget(new QLabel("Protected Members"));
    //    mProtectedMembers = new QTextEdit();
    //    mMainLayout->addWidget(mProtectedMembers);

    mMainLayout->addWidget(new QLabel("Public Members"));
    //    mPublicMembers = new QTextEdit();
    //    mMainLayout->addWidget(mPublicMembers);

    mControllerLauout = new QHBoxLayout();
    mMainLayout->addLayout(mControllerLauout);

    mAcceptedBtn = new QPushButton("OK");
    mControllerLauout->addWidget(mAcceptedBtn);

    mRejectBtn = new QPushButton("Cancel");
    mControllerLauout->addWidget(mRejectBtn);

    QObject::connect(mAcceptedBtn,&QPushButton::clicked,[=](){

        mIsAccepted = true;
        this->close();
    });


    QObject::connect(mRejectBtn,&QPushButton::clicked,[=](){

        this->close();
    });

    QObject::connect(mAddPrivateFunctionMemberBtn,&QPushButton::clicked,[=](){

        auto mDialog = new FunctionDialog();

        mDialog->exec();

        if( mDialog->isAccepted() ){

            auto functionItem = new QStandardItem(mDialog->getFunctionName());
            functionItem->setData(mDialog->getFunctionType(),Qt::UserRole+1);
            functionItem->setData(mDialog->getDeclaration(),Qt::UserRole+2);
            functionItem->setData(mDialog->getDefination(),Qt::UserRole+3);
            functionItem->setData(mDialog->getReturnType(),Qt::UserRole+4);
            mPrivateFunctionMembersModel->insertRow(0,functionItem);


        }
    });

}

bool ClassDialog::isAccepted() const
{
    return mIsAccepted;
}

QString ClassDialog::getClassName() const
{
    return mClassNameLineEdit->text();
}

QVector<CPP::Function::Function> ClassDialog::getPrivateFunctionMemberList() const
{
    QVector<CPP::Function::Function> list;

    for( int i = 0 ; i < mPrivateFunctionMembersModel->rowCount() ; i++ ){
        CPP::Function::Function function(mPrivateFunctionMembersModel->item(i)->text());
        function.setFunctionType(mPrivateFunctionMembersModel->item(i)->data(Qt::UserRole+1).toString());
        function.setDeclaration(mPrivateFunctionMembersModel->item(i)->data(Qt::UserRole+2).toString());
        function.setDefination(mPrivateFunctionMembersModel->item(i)->data(Qt::UserRole+3).toString());
        function.setReturnType(mPrivateFunctionMembersModel->item(i)->data(Qt::UserRole+4).toString());

        list.push_back(function);
    }

    return list;
}

} // namespace GeneratorDialog

