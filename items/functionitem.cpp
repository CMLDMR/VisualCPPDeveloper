
#include "functionitem.h"
#include "cpp/file.h"
#include "cpp/function.h"

#include "dialog/functiondialog.h"

#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>

namespace Items {

Function::Function(const QString &functionName)
{
    setFlag(ItemIsMovable);

    mFunction = new CPP::Function::Function(functionName);
    mFunction->setFunctionType("regular");
    mFunction->setDeclaration("void main(int argc, char *argv[])");
    mFunction->setDefination("std::cout << \"Hello World\";");

    mFile = new CPP::File::File(functionName);
}

Function::Function(const CPP::Function::Function &function)
{
    mFunction = new CPP::Function::Function(function);
    mFile = new CPP::File::File(mFunction->getName());
    setFlag(ItemIsMovable);
}

} // namespace Items



QRectF Items::Function::boundingRect() const
{
    return QRectF(-20,-20,300,100);

}

void Items::Function::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->fillRect(rect,QBrush(QColor(200,170,170)));/* brush, brush style or color */
//    painter->drawRect(rect);
    painter->drawText(0,0,"Function: " + mFunction->getName());
    painter->drawText(0,20,mFunction->getDeclaration());

    painter->setBackground(QBrush(QColor(200,170,170)));

}

void Items::Function::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if( event->button() == Qt::MouseButton::RightButton ){
        QMenu menu;


        auto editAction = menu.addAction("Düzenle");
        menu.addSeparator();
        auto saveAction = menu.addAction("Save");
        auto saveToFileAction = menu.addAction("Save To File");

        auto selected = menu.exec(event->screenPos());

        if( selected == editAction ){

            auto mDialog = new GeneratorDialog::FunctionDialog();

            mDialog->setCode(mFunction->getDefination());
            mDialog->setFunctionName(mFunction->getName());
            mDialog->setDeclaration(mFunction->getDeclaration());
            mDialog->setFunctionType(mFunction->getFunctionType());
            mDialog->setIncludeFile(mFunction->getIncludeFiles());
            mDialog->exec();


            if( mDialog->isAccepted() ){
                mFunction->setDeclaration(mDialog->getCode());
                mFunction->setDeclaration(mDialog->getDeclaration());
                mFunction->setName(mDialog->getFunctionName());
                mFunction->setFunctionType(mDialog->getFunctionType());
                mFunction->setIncludeFiles(mDialog->getIncludeFile());
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

//    QGraphicsItem::mouseDoubleClickEvent(event);
}
