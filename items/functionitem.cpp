
#include "functionitem.h"
#include "cpp/file.h"
#include "cpp/function.h"

#include "dialog/functiondialog.h"
#include "dialog/addincludedialog.h"

#include "global/projectmanager.h"

#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>

namespace Items {

Function::Function(const QString &functionName)
{
    setFlag(ItemIsMovable);
    mFunction = new CPP::Function::Function(functionName);
    mFile = new CPP::File::File(functionName);
    this->initMenu();
}

Function::Function(const CPP::Function::Function &function)
{
    mFunction = new CPP::Function::Function(function);
    mFile = new CPP::File::File(mFunction->getName());
    setFlag(ItemIsMovable);
    this->initMenu();
}

void Function::initMenu()
{

    auto editAction = addMenu("Düzenle");
                      auto addIncludeFileAction = addMenu("add Include");

    auto saveAction = addMenu("Generate Code");
    auto saveToFileAction = addMenu("Save");

    QObject::connect(editAction,&QAction::triggered,this,&Function::editFunction);

    QObject::connect(addIncludeFileAction,&QAction::triggered,[=](){
        auto mDialog = new GeneratorDialog::AddIncludeDialog();
        mDialog->setIncludeFiles(mFile->includeFiles());
        mDialog->exec();
        if( mDialog->isAccepted() ){
//            mFile->setIncludeFiles(mDialog->getIncludeFiles());
            mFunction->setIncludeFiles(mDialog->getIncludeFiles());
        }
        delete mDialog;
    });

    QObject::connect(saveAction,&QAction::triggered,[=](){

        Global::ProjectManager::instance()->append(*mFunction);
        Global::ProjectManager::instance()->generateCode(*mFunction);

//        mFile->addFunction(*mFunction);
//        mFile->saveMembers();
    });

    QObject::connect(saveToFileAction,&QAction::triggered,[=](){
//        mFile->saveFiles();
        Global::ProjectManager::instance()->save();

    });
}



void Function::editFunction()
{
    auto mDialog = new GeneratorDialog::FunctionDialog();

    mDialog->setCode(mFunction->getDefination());
    mDialog->setFunctionName(mFunction->getName());
    mDialog->setDeclaration(mFunction->getDeclaration());
    mDialog->setFunctionType(mFunction->getFunctionType());
    mDialog->setReturnType(mFunction->getReturnType());

    mDialog->exec();


    if( mDialog->isAccepted() ){
        *mFunction = mDialog->getFunction();
    }
    delete mDialog;
}

} // namespace Items



QRectF Items::Function::boundingRect() const
{
    return QRectF(0,0,400,100);

}

void Items::Function::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->fillRect(rect,QBrush(QColor(200,170,170)));/* brush, brush style or color */
    painter->drawRect(rect);

    painter->drawText(0,0,"Function: " + mFunction->getName());
    painter->drawText(0,20,mFunction->getDeclaration());

    AbstractItem::paint(painter,option,widget);
}




void Items::Function::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    if( event->button() == Qt::MouseButton::LeftButton ){


        QMenu menu;

        auto editAction = menu.addAction("edit");
        auto addIncludeFileAction = menu.addAction("add header");

                          menu.addSeparator();
        auto saveAction = menu.addAction("Generate Code");
        auto saveToFileAction = menu.addAction("Save");

        auto selected = menu.exec(event->screenPos());


        if( selected == editAction ){
            this->editFunction();
        }

        if( selected == addIncludeFileAction ){
            auto mDialog = new GeneratorDialog::AddIncludeDialog();
            mDialog->setIncludeFiles(mFile->includeFiles());
            mDialog->exec();
            if( mDialog->isAccepted() ){
                mFile->setIncludeFiles(mDialog->getIncludeFiles());
            }
            delete mDialog;
        }

        if( selected == saveAction ){
            mFile->addFunction(*mFunction);
            mFile->saveMembers();
        }

        if( selected == saveToFileAction ){
            mFile->saveFiles();
        }

    }
}
