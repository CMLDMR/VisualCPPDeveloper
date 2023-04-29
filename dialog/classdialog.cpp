
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


    mHLayout = new QHBoxLayout();
    mMainLayout->addLayout(mHLayout);

    mPrivateWidget = new QWidget();
    mHLayout->addWidget(mPrivateWidget);

    mPrivateVLayout = new QVBoxLayout();
    mPrivateWidget->setLayout(mPrivateVLayout);

    mPrivateVLayout->addWidget(new QLabel("Private Members"));
    mPrivateFunctionMembersModel = new QStandardItemModel();

    mPrivateMembersView = new QTableView();
    mPrivateMembersView->setModel(mPrivateFunctionMembersModel);
    mPrivateVLayout->addWidget(mPrivateMembersView);

    mPrivateMembersControllerLayout = new QHBoxLayout();
    mAddPrivateFunctionMemberBtn = new QPushButton("Add Function");
    mPrivateMembersControllerLayout->addWidget(mAddPrivateFunctionMemberBtn);
    mAddPrivateAttributeMemberBtn = new QPushButton("Add Member");
    mPrivateMembersControllerLayout->addWidget(mAddPrivateAttributeMemberBtn );
    mPrivateVLayout->addLayout(mPrivateMembersControllerLayout);




    //TODO: implement Protected Members
    mMainLayout->addWidget(new QLabel("Protected Members"));
    //    mProtectedMembers = new QTextEdit();
    //    mMainLayout->addWidget(mProtectedMembers);



    mPublicWidget = new QWidget();
    mPublicVLayout = new QVBoxLayout();
    mPublicWidget->setLayout(mPublicVLayout);
    mHLayout->addWidget(mPublicWidget);

    mPublicVLayout->addWidget(new QLabel("Public Members"));
    mPublicFunctionMembersModel = new QStandardItemModel();

    mPublicMembersView = new QTableView();
    mPublicMembersView->setModel(mPublicFunctionMembersModel);
    mPublicVLayout->addWidget(mPublicMembersView);

    mPublicMembersControllerLayout = new QHBoxLayout();
    mAddPublicFunctionMemberBtn = new QPushButton("Add Function");
    mPublicMembersControllerLayout->addWidget(mAddPublicFunctionMemberBtn);
    mAddPublicAttributeMemberBtn = new QPushButton("Add Member");
    mPublicMembersControllerLayout->addWidget(mAddPublicAttributeMemberBtn);
    mPublicVLayout->addLayout(mPublicMembersControllerLayout);






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
            functionItem->setData(Function,Type);
            functionItem->setData(PRIVATE,Area);
            functionItem->setData(mDialog->getFunction(),Function);
            mPrivateFunctionMembersModel->insertRow(0,functionItem);

        }
    });

    QObject::connect(mAddPublicFunctionMemberBtn,&QPushButton::clicked,[=](){

        auto mDialog = new FunctionDialog();

        mDialog->exec();

        if( mDialog->isAccepted() ){

            auto functionItem = new QStandardItem(mDialog->getFunctionName());
            functionItem->setData(Function,Type);
            functionItem->setData(PUBLIC,Area);
            functionItem->setData(mDialog->getFunction(),Function);
            mPublicFunctionMembersModel->insertRow(0,functionItem);

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

        auto dataIndex = mPrivateFunctionMembersModel->item(i);
        if( dataIndex->data(Type).toInt() == Function && dataIndex->data(Area).toInt() == PRIVATE ){
            CPP::Function::Function function_(mPrivateFunctionMembersModel->item(i)->data(Function).toJsonObject());
            list.push_back(function_);
        }

    }

    return list;
}

QVector<CPP::Function::Function> ClassDialog::getPublicFunctionMemberList() const
{
    QVector<CPP::Function::Function> list;

    for( int i = 0 ; i < mPublicFunctionMembersModel->rowCount() ; i++ ){

        auto dataIndex = mPublicFunctionMembersModel->item(i);
        if( dataIndex->data(Type).toInt() == Function && dataIndex->data(Area).toInt() == PUBLIC ){
            CPP::Function::Function function_(mPublicFunctionMembersModel->item(i)->data(Function).toJsonObject());
            list.push_back(function_);
        }

    }

    return list;
}

} // namespace GeneratorDialog

