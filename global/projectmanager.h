
#ifndef GLOBAL_PROJECTMANAGER_H
#define GLOBAL_PROJECTMANAGER_H


#include <QObject>
#include "cpp/member.h"
#include <optional>

#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>



namespace Global {

class ProjectManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ProjectManager)

public:
    virtual ~ProjectManager(){}
    static ProjectManager* instance();

    void append( const CPP::Member &member );

    const CPP::Member &operator[](const int index) const;
    const CPP::Member *getByName(const QString &name) const;



    QString projectName() const;
    void setProjectName(const QString &newProjectName);

    QString projectLocation() const;
    void setProjectLocation(const QString &newProjectLocation);

    void newProject( const QString &projectName,
                    const QString &projectPath );

    void generateCode( const CPP::Member &member );


    void save();

signals:

private:
    explicit ProjectManager(QObject *parent = nullptr);

    static ProjectManager* mProjectManager;

    QVector<CPP::Member> mItemList;

    QString mProjectName;
    QString mProjectLocation;

    QJsonObject mConfigObject;


    bool saveHeader(const CPP::Member &member);
    bool saveSource( const CPP::Member &member );

    QString recursiveHeaderFunc(const CPP::Member &member);
    QString recursiveSourceFunc(const CPP::Member &member);
};

} // namespace Global

#endif // GLOBAL_PROJECTMANAGER_H
