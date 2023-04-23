
#ifndef LAYOUT_VBOXLAYOUT_H
#define LAYOUT_VBOXLAYOUT_H

#include <QVBoxLayout>
#include <QHBoxLayout>


namespace Layout {

class VBoxLayout : public QVBoxLayout
{
public:
    VBoxLayout();

    template<typename T>
    T* addWidgetItem();

private:

};


class HBoxLayout : public QHBoxLayout
{
public:
    HBoxLayout();

    template<typename T>
    T* addWidgetItem();
};












template<typename T>
T *HBoxLayout::addWidgetItem()
{
    T* item = new T();
    this->addWidget(item);
    return item;
}


template<typename T>
T *VBoxLayout::addWidgetItem()
{
    T* item = new T();
    this->addWidget(item);
    return item;
}

} // namespace Layout

#endif // LAYOUT_VBOXLAYOUT_H
