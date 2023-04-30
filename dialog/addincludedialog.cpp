
#include "addincludedialog.h"

namespace GeneratorDialog {

AddIncludeDialog::AddIncludeDialog()
{
    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mTextEdit = new QTextEdit();
    mTextEdit->setPlaceholderText("add include files");
    mMainLayout->addWidget(mTextEdit);

    mControllerLayout = new QHBoxLayout();
    mMainLayout->addLayout(mControllerLayout);

    mAcceptedBtn = new QPushButton("OK");

    mRejectedBtn = new QPushButton("Cancel");
    mControllerLayout->addWidget(mAcceptedBtn);
    mControllerLayout->addWidget(mRejectedBtn);

    QObject::connect(mAcceptedBtn,&QPushButton::clicked,[=](){

        mIsAccepted = true;
        this->close();
    });

    QObject::connect(mRejectedBtn,&QPushButton::clicked,[=](){

        this->close();
    });
}

bool AddIncludeDialog::isAccepted() const
{
    return mIsAccepted;
}

QString AddIncludeDialog::getIncludeFiles() const
{
    return mTextEdit->toPlainText();
}

void AddIncludeDialog::setIncludeFiles(const QString &code)
{
    mTextEdit->setText(code);
}

} // namespace GeneratorDialog

