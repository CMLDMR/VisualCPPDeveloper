
#include "projectmanager.h"
#include <mutex>





namespace Global {


std::once_flag mProjectManager_flag;
Global::ProjectManager* Global::ProjectManager::mProjectManager = nullptr;

ProjectManager *ProjectManager::instance()
{
     std::call_once(mProjectManager_flag,[=](){
        mProjectManager = new ProjectManager();
    });
    return mProjectManager;
}

void ProjectManager::append(const CPP::Member &member)
{
    this->mItemList.append(member);
}

const CPP::Member &ProjectManager::operator [](const int index) const
{
    return mItemList[index];
}

const CPP::Member* ProjectManager::getByName(const QString &name) const
{
    CPP::Member member;

    auto item = std::find_if(std::begin(mItemList),std::end(mItemList),[ &name](CPP::Member _member){
        return _member.getName() == name;
    });

    if( item != mItemList.end() ){
        return item;
    }else{
        return nullptr;
    }

}

ProjectManager::ProjectManager(QObject *parent)
    : QObject{parent}
{

}

} // namespace Global

