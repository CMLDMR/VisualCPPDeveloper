
#include "newprojectdialog.h"

#include "global/projectmanager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include <QFile>


namespace GeneratorDialog {

NewProjectDialog::NewProjectDialog()
{

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mProjectNameLineEdit = new QLineEdit();
    mProjectNameLineEdit->setPlaceholderText("Enter Project Name");
    mMainLayout->addWidget(mProjectNameLineEdit);



    mProjectLocationLayout = new QHBoxLayout();
    mLocationLineEdit = new QLineEdit();
    mLocationLineEdit->setPlaceholderText("Set Project Location Path");
    mProjectLocationLayout->addWidget(mLocationLineEdit);
    mBrowseLocationBtn = new QPushButton("Browse");
    mProjectLocationLayout->addWidget(mBrowseLocationBtn);
    mMainLayout->addLayout(mProjectLocationLayout);


    mMainLayout->addStretch(1);

    mControllerLayout = new QHBoxLayout();
    mSaveProjectBtn = new QPushButton("Save");
    mControllerLayout->addWidget(mSaveProjectBtn);

    mCancelBtn = new QPushButton("Cancel");
    mControllerLayout->addWidget(mCancelBtn);

    mMainLayout->addLayout(mControllerLayout);



    QObject::connect(mBrowseLocationBtn,&QPushButton::clicked,this,&NewProjectDialog::browseLocation);
    QObject::connect(mSaveProjectBtn,&QPushButton::clicked,this,&NewProjectDialog::saveProject);

    QObject::connect(mCancelBtn,&QPushButton::clicked,[=](){
        this->close();
    });




}

void NewProjectDialog::browseLocation()
{
    auto location = QFileDialog::getExistingDirectory(this,"ProjectLocation",QDir::currentPath());
    mLocationLineEdit->setText(location);
}

void NewProjectDialog::saveProject()
{

    QDir dir(mLocationLineEdit->text());


    if( !dir.exists("package") ){
        if( !dir.mkdir("package") ){
            //TODO: error Dialog
            qDebug() << "package can not create";
            return;
        }
    }




    Global::ProjectManager::instance()->newProject(mProjectNameLineEdit->text(),mLocationLineEdit->text());

    Global::ProjectManager::instance()->save();
    this->close();
}

} // namespace GeneratorDialog

