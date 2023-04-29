
#include "namespaceitem.h"

#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

#include "dialog/addincludedialog.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsView>
#include <QApplication>

namespace Items {

NamespaceItem::NamespaceItem(const QString &namespaceName)
{
    setFlag(ItemIsMovable);
    this->setAcceptHoverEvents(true);
    mNameSpace = new CPP::NameSpace::NameSpace(namespaceName);
    mFile = new CPP::File::File(namespaceName);

}

NamespaceItem::NamespaceItem(const CPP::NameSpace::NameSpace &nameSpace)
{
    mNameSpace = new CPP::NameSpace::NameSpace(nameSpace);
    mFile = new CPP::File::File(mNameSpace->getName());
    setFlag(ItemIsMovable);
    this->setAcceptHoverEvents(true);


}

} // namespace Items



QRectF Items::NamespaceItem::boundingRect() const
{
    return QRectF(0,0,300,100);


}

void Items::NamespaceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();





    if( mState == BUTTONSTATE::ENTER ){
        painter->fillRect(rect,QBrush(QColor(150,200,170)));/* brush, brush style or color */

    }else if( mState == BUTTONSTATE::LEAVE || mState == BUTTONSTATE::IDLE ){
        painter->fillRect(rect,QBrush(QColor(200,200,170)));/* brush, brush style or color */
    }else if( mState == BUTTONSTATE::LEFTPRESSED ){
        if( mAddFunctionMemberRect.contains(mCLickedPoint) ){
            painter->fillRect(mAddFunctionMemberRect,QBrush(QColor(250,100,170)));/* brush, brush style or color */
        }
    }

    painter->drawText(3,painter->font().pointSize()+5,"Add Member");
    painter->drawRect(mAddFunctionMemberRect);

    painter->drawRect(rect);

    painter->drawText(0,0,"namespace: " + mNameSpace->getName());
}


void Items::NamespaceItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    if( event->button() == Qt::MouseButton::LeftButton ){


        QMenu menu;

        auto editAction = menu.addAction("Düzenle");
                          auto addIncludeFileAction = menu.addAction("add Include");

        menu.addSeparator();
        auto saveAction = menu.addAction("Generate Code");
        auto saveToFileAction = menu.addAction("Save");

        auto selected = menu.exec(event->screenPos());


        if( selected == editAction ){

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
            mFile->addMember(*mNameSpace);
            mFile->saveMembers();
        }

        if( selected == saveToFileAction ){
            mFile->saveFiles();
        }

    }

    QGraphicsItem::mouseDoubleClickEvent(event);

}


void Items::NamespaceItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug() << "Release" << event->scenePos() << event->pos();
    if( event->button() == Qt::MouseButton::LeftButton ){
        mState = BUTTONSTATE::LEFTPRESSED;
        mCLickedPoint = event->pos();
    }
    if( event->button() == Qt::MouseButton::RightButton ){
        mState = BUTTONSTATE::RIGHTPRESSED;
    }

    qDebug() << "Press" << event->scenePos() << event->pos();
    mPressed = true;
    this->update();
    QGraphicsItem::mousePressEvent(event);

}

void Items::NamespaceItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if( mAddFunctionMemberRect.contains(mCLickedPoint) ){
        QMenu menu;

        auto editAction = menu.addAction("Add Function");
        menu.addAction("Add Variable");
        menu.addAction("Add Class");
        auto addIncludeFileAction = menu.addAction("Add Include");

        menu.addSeparator();
        auto saveAction = menu.addAction("Generate Code");
        auto saveToFileAction = menu.addAction("Save");

        auto selected = menu.exec(event->screenPos());


        if( selected == editAction ){

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
            mFile->addMember(*mNameSpace);
            mFile->saveMembers();
        }

        if( selected == saveToFileAction ){
            mFile->saveFiles();
        }
    }

    mState = BUTTONSTATE::IDLE;

    mPressed = false;
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);

}


void Items::NamespaceItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "Enter" << event->scenePos() << event->pos();
//    if( mAddFunctionMemberRect.contains(event->pos()) ){
//        qApp->setOverrideCursor(QCursor(Qt::PointingHandCursor));
//    }

    mState = BUTTONSTATE::ENTER;

    QGraphicsItem::hoverEnterEvent(event);

}

void Items::NamespaceItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

    if( mAddFunctionMemberRect.contains(event->pos()) ){
        qApp->setOverrideCursor(QCursor(Qt::PointingHandCursor));
    }else{
        qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));

    }

    qDebug() << "Move" << event->scenePos() << event->pos();


    QGraphicsItem::hoverMoveEvent(event);

}

void Items::NamespaceItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//    qApp->setOverrideCursor(QCursor(Qt::CursorShape::ArrowCursor));
    qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));

    qDebug() << "Leave" << event->scenePos() << event->pos();
    mState = BUTTONSTATE::LEAVE;

    QGraphicsItem::hoverLeaveEvent(event);

}
