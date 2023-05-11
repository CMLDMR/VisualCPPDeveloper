
#include "functionitem.h"
#include "cpp/file.h"
#include "cpp/function.h"

#include "dialog/functiondialog.h"
#include "dialog/addincludedialog.h"

#include "global/projectmanager.h"

#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QPolygonF>
#include <QImage>
#include <QPainterPath>


namespace Items {

Function::Function(const QString &functionName)
{
    setFlag(ItemIsMovable);
    mFunction = new CPP::Function::Function(functionName);
    mFile = new CPP::File::File(functionName);
//    this->initMenu();
}

Function::Function(const CPP::Function::Function &function)
{
    mFunction = new CPP::Function::Function(function);
    mFile = new CPP::File::File(mFunction->getName());
    setFlag(ItemIsMovable);
//    this->initMenu();
}

void Function::initMenu()
{

    auto editAction = addMenu("Düzenle");
    auto addIncludeFileAction = addMenu("add Include");

    auto saveAction = addMenu("Generate Code");
    auto saveToFileAction = addMenu("Save");

    QObject::connect(editAction,&QAction::triggered,this,&Function::editFunction);

    QObject::connect(addIncludeFileAction,&QAction::triggered,[=](bool checked){
        auto mDialog = new GeneratorDialog::AddIncludeDialog();
        mDialog->setIncludeFiles(mFile->includeFiles());
        mDialog->exec();
        if( mDialog->isAccepted() ){
            mFunction->setIncludeFiles(mDialog->getIncludeFiles());
        }
        delete mDialog;
    });

    QObject::connect(saveAction,&QAction::triggered,[=](bool checked){
        Global::ProjectManager::instance()->append(*mFunction);
        Global::ProjectManager::instance()->generateCode(*mFunction);
    });

    QObject::connect(saveToFileAction,&QAction::triggered,[=](){
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
    return QRectF(0,0,200,100);

}

void Items::Function::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QRectF rect = boundingRect();

    auto fontMetric = painter->fontMetrics();

    QPolygonF polygonF;
    polygonF << QPointF(0, 0);
    polygonF << QPointF(0, fontMetric.boundingRect("function: " + mFunction->getName()).height());
    polygonF << QPointF(0, 100);
    polygonF << QPointF(200, 100);
    polygonF << QPointF(200, fontMetric.boundingRect("function: " + mFunction->getName()).height());
    polygonF << QPointF(fontMetric.boundingRect("function: " + mFunction->getName()).width()+fontMetric.boundingRect("Function: " + mFunction->getName()).height(), fontMetric.boundingRect("Function: " + mFunction->getName()).height());
    polygonF << QPointF(fontMetric.boundingRect("function: " + mFunction->getName()).width(), 0);

    QPainterPath path;
    path.addPolygon(polygonF);
    painter->fillPath(path,QBrush(functionBackGroundColor));

    QImage img;
    if( img.load("icon/function.png") ){
        painter->drawImage( 0 , img.height(),img);
        painter->drawImage( 0 , 0,img);

    }


    auto functionStr = mFunction->getReturnType() + " " + mFunction->getName()+"("+ mFunction->getParameter() +");";

    QRectF attributeRect(img.width(),img.height(),
                         fontMetric.boundingRect(functionStr).width()+5,fontMetric.boundingRect(functionStr).height());

    for( const auto &key : qAsConst(mMenuRectList) ){
        if( key ){
            const auto &[x,y,w,h] = mMenuRectList.key(key);
            QRectF selectedItem(x,y,w,h);
            painter->drawRect(selectedItem);
        }
    }


    mMenuRectList.insert(std::make_tuple(attributeRect.x(),attributeRect.y(),
                                         attributeRect.width(),
                                         attributeRect.height()),0);

    painter->drawText(attributeRect,functionStr);

//    AbstractItem::paint(painter,option,widget);
}




void Items::Function::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractItem::mouseDoubleClickEvent(event);
}


void Items::Function::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if( event->button() == Qt::MouseButton::RightButton ){

        bool mSelectedAttribute{false};
        for( const auto &key : qAsConst(mMenuRectList) ){
            if( key ){
                mSelectedAttribute = true;
                break;
            }
        }

        QMenu menu;

        if( mSelectedAttribute ){
            menu.addAction("Edit Attribute",this,&Function::editFunction);

        }else{
            menu.addAction("Düzenle",this,&Function::editFunction);


            menu.addAction("Add Header",[=](bool checked){
                auto mDialog = new GeneratorDialog::AddIncludeDialog();
                mDialog->setIncludeFiles(mFile->includeFiles());
                mDialog->exec();
                if( mDialog->isAccepted() ){
                    mFunction->setIncludeFiles(mDialog->getIncludeFiles());
                }
                delete mDialog;
            });

            menu.addSeparator();
            menu.addAction("Generate Code",[=](bool checked){
                Global::ProjectManager::instance()->append(*mFunction);
                Global::ProjectManager::instance()->generateCode(*mFunction);
            });


            menu.addAction("Save",[=](){
                Global::ProjectManager::instance()->save();

            });
        }



        menu.exec(event->screenPos());

    }


    AbstractItem::mousePressEvent(event);

}


void Items::Function::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

    QRectF sel;
    for( const auto &key : qAsConst(mMenuRectList) ){
        const auto &[x,y,w,h] = mMenuRectList.key(key);
        QRectF selectedItem(x,y,w,h);
        sel = selectedItem;
        if( selectedItem.contains(event->pos()) ){
            mMenuRectList.insert(std::make_tuple(selectedItem.x(),selectedItem.y(),
                                                 selectedItem.width(),
                                                 selectedItem.height()),1);
        }else{
            mMenuRectList.insert(std::make_tuple(selectedItem.x(),selectedItem.y(),
                                                 selectedItem.width(),
                                                 selectedItem.height()),0);
        }
    }
    this->update(sel);

    qDebug() << event->pos() << sel ;


}
