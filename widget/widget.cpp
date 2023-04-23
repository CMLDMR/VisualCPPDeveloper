
#include "widget.h"
#include <QDebug>

namespace Widget {

Widget::Widget(QWidget *parent)
    : QWidget{parent}
{

}

Widget::~Widget()
{
    qDebug() << "Destruction Widget::Widget";
}

//template<typename T>
//T *Widget::setLayout(std::unique_ptr<T> item)
//{
//    this->setLayout(item->get());
//    return item.get();
//}

} // namespace Widget

