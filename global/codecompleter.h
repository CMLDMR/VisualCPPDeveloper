
#ifndef GLOBAL_CODECOMPLETER_H
#define GLOBAL_CODECOMPLETER_H

#include <QAbstractListModel>

#include <QStringListModel>

namespace Global {


class CodeContainer : public QObject
{
    Q_OBJECT
public:

    static CodeContainer* instance();

    QStringListModel *codeCompleterModel() const;

    CodeContainer &append( const QString keyword );


private:
    explicit CodeContainer();

    static CodeContainer* mCodeContainer;

    QStringListModel* mModel;
    QStringList mCodeList;
};




} // namespace Global

#endif // GLOBAL_CODECOMPLETER_H
