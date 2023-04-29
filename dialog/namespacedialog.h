
#ifndef GENERATORDIALOG_NAMESPACEDIALOG_H
#define GENERATORDIALOG_NAMESPACEDIALOG_H

#include <QDialog>

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

#include "cpp/namespace.h"

namespace GeneratorDialog {

class NameSpaceDialog : public QDialog
{
public:
    NameSpaceDialog();



    CPP::NameSpace::NameSpace getNameSpace() const;
    bool isAccepted() const;

private:

    QVBoxLayout* mMainLayout;
    QLineEdit* mNameSpaceLineEdit;

    QHBoxLayout* mControllerLayout;
    QPushButton* mAcceptedBtn;
    QPushButton* mRejectedBtn;

    bool mIsAccepted{false};

};

} // namespace GeneratorDialog

#endif // GENERATORDIALOG_NAMESPACEDIALOG_H
