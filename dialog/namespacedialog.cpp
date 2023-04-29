
#include "namespacedialog.h"

namespace GeneratorDialog {

NameSpaceDialog::NameSpaceDialog()
{

    this->setWindowTitle("Add namespace");

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mMainLayout->addWidget(new QLabel("Add namespace"));

    mNameSpaceLineEdit = new QLineEdit();
    mNameSpaceLineEdit->setPlaceholderText("type namespace name");
    mMainLayout->addWidget(mNameSpaceLineEdit);

    mControllerLayout = new QHBoxLayout();
    mAcceptedBtn = new QPushButton("OK");
    mRejectedBtn = new QPushButton("Cancel");

    mControllerLayout->addWidget(mAcceptedBtn);
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

CPP::NameSpace::NameSpace NameSpaceDialog::getNameSpace() const
{
    CPP::NameSpace::NameSpace space(mNameSpaceLineEdit->text());

    return space;
}

bool NameSpaceDialog::isAccepted() const
{
    return mIsAccepted;
}

} // namespace GeneratorDialog

