
#ifndef GENERATORDIALOG_NEWPROJECTDIALOG_H
#define GENERATORDIALOG_NEWPROJECTDIALOG_H

#include <QDialog>

#include <QWidget>

class QVBoxLayout;
class QLineEdit;
class QLabel;
class QPushButton;
class QHBoxLayout;
class QFileDialog;


namespace GeneratorDialog {

class NewProjectDialog : public QDialog
{
    Q_OBJECT
public:
    NewProjectDialog();



private:
    QVBoxLayout* mMainLayout;
    QLineEdit* mProjectNameLineEdit;

    QHBoxLayout* mProjectLocationLayout;
    QLineEdit* mLocationLineEdit;
    QPushButton* mBrowseLocationBtn;

    QHBoxLayout* mControllerLayout;
    QPushButton* mSaveProjectBtn;
    QPushButton* mCancelBtn;

private slots:

    void browseLocation();
    void saveProject();
};

} // namespace GeneratorDialog

#endif // GENERATORDIALOG_NEWPROJECTDIALOG_H
