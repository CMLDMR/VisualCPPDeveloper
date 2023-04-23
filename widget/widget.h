
#ifndef WIDGET_WIDGET_H
#define WIDGET_WIDGET_H


#include <QWidget>
#include <memory>


namespace Widget {

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    virtual ~Widget();

    template<typename T>
    T* setMainLayout(){
        auto item = new T();
        this->setLayout(item);
        return item;
    }

signals:

};

} // namespace Widget

#endif // WIDGET_WIDGET_H
