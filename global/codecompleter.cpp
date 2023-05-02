
#include "codecompleter.h"
#include <mutex>




namespace Global {


CodeContainer* CodeContainer::mCodeContainer{nullptr};
std::once_flag mContainerOnce_Flag;

CodeContainer *CodeContainer::instance()
{
     std::call_once(mContainerOnce_Flag,[=](){
        mCodeContainer = new CodeContainer();
    });
    return mCodeContainer;
}

CodeContainer::CodeContainer()
{
    mModel = new QStringListModel();
    mCodeList.append("class");
    mCodeList.append("for");
    mCodeList.append("struct");
    mCodeList.append("union");
    mCodeList.append("char");
    mCodeList.append("short");
    mCodeList.append("int");
    mCodeList.append("double");
    mCodeList.append("float");
    mCodeList.append("std::string");

    mCodeList.append("std::int64_t");


    mModel->setStringList(mCodeList);
}

QStringListModel *CodeContainer::codeCompleterModel() const
{
    return mModel;
}

CodeContainer &CodeContainer::append(const QString keyword)
{
    mCodeList.append(keyword);
    return *this;
}

} // namespace Global




