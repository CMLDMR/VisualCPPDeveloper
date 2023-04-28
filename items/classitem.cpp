
#include "classitem.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>

#include "dialog/class.h"

#include "cpp/class.h"
#include "cpp/file.h"
#include "cpp/namespace.h"
#include "cpp/function.h"
#include "cpp/attribute.h"

namespace Items {

Class::Class()
{
    setFlag(ItemIsMovable);

}

} // namespace Items



QRectF Items::Class::boundingRect() const
{
    return QRectF(0,0,100,100);

}

void Items::Class::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->setBackground(mBackGround);
    painter->drawRect(rect);
    painter->drawText(0,0,"Class");

}



void Items::Class::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QMenu menu;


    auto editAction = menu.addAction("Düzenle");

    menu.addAction("Sil");

    auto selected = menu.exec(event->screenPos());

    if( selected == editAction ){


        CPP::NameSpace::NameSpace nameSpace("HHHello");

        CPP::NameSpace::NameSpace world("World");

        nameSpace.appendMember(world);


        CPP::Class::Class mClass("HelloWorld");
        CPP::Function::Function consFunc("HelloWorld");
        consFunc.setThisConstruction();
        mClass.appendPublic(consFunc);

        CPP::Function::Function desFunc("~HelloWorld");
        desFunc.setThisDesConstruction();
        desFunc.setFunctionType("virtual");
        mClass.appendPublic(desFunc);


        CPP::Function::Function print("printHello");
        print.setReturnType("void");
        print.setParameter("");
        print.setReadOnly(true);
        mClass.appendPublic(print);
        mClass.appendPublic(print);


        CPP::Attribute::Attribute atribute("AdSoyad");
        atribute.setType("std::string");
        atribute.setInitialValue("\"Test Yazı\"");
        atribute.setReadOnly(true);
        mClass.appendPublic(atribute);

        atribute.setName("mMiktar");
        atribute.setType("double");
        atribute.setInitialValue("25");
        atribute.setReadOnly(false);
        mClass.appendPrivate(atribute);


        nameSpace.appendMember(mClass);



        CPP::File::legacy::File file("HelloWord");
        file.saveNameSpace(nameSpace);


//        CPP::File::File mainFunc("main");
//        file.saveNameSpace(nameSpace);
//        CPP::Function::Function print("printHello");
//        print.setReturnType("void");
//        print.setParameter("");
//        print.setReadOnly(true);
//        mClass.appendPublic(print);

        qDebug() << nameSpace;






    }

    QGraphicsItem::mouseDoubleClickEvent(event);
}


