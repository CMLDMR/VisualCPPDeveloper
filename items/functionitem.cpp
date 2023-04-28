
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
    mFunction->setReturnType("void");
    mFunction->setParameter("int argc, char *argv[]");
    mFunction->setReadOnly();
    mFunction->setImplementation("std::cout << \"Hello World\";");

    mFile = new CPP::File::File(functionName);
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
    painter->drawText(0,20,"type: " + mFunction->getReturnType());
    painter->drawText(0,40,"paramater: " + mFunction->getParameter());
    painter->drawText(0,60,"Regular/Virtual: " + mFunction->getFunctionType());

    painter->setBackground(QBrush(QColor(200,170,170)));

}

void Items::Function::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if( event->button() == Qt::MouseButton::RightButton ){
        QMenu menu;


        auto editAction = menu.addAction("Düzenle");
        auto delAction = menu.addAction("Sil");
        menu.addSeparator();
        auto saveAction = menu.addAction("Save");

        auto selected = menu.exec(event->screenPos());

        if( selected == editAction ){

            auto mDialog = new GeneratorDialog::FunctionDialog();

            mDialog->setCode(mFunction->getImplementation());
            mDialog->setParaMeterCode(mFunction->getParameter());
            mDialog->setReturnTypeCode(mFunction->getReturnType());
            mDialog->setFunctionName(mFunction->getName());
            mDialog->setFunctionType(mFunction->getFunctionType());
            mDialog->exec();


            if( mDialog->isAccepted() ){
                mFunction->setImplementation(mDialog->getCode());
                mFunction->setReturnType(mDialog->getReturnTypeCode());
                mFunction->setParameter(mDialog->getParameterCode());
                mFunction->setName(mDialog->getFunctionName());
                mFunction->setFunctionType(mDialog->getFunctionType());
            }
            delete mDialog;

        }

        if( selected == saveAction ){
            mFile->addFunction(*mFunction);
            mFile->saveFile();
        }

    }

//    QGraphicsItem::mouseDoubleClickEvent(event);
}
