#ifndef HORIZONJUICERCREATOR_H
#define HORIZONJUICERCREATOR_H

#include <QMainWindow>
#include "creatorwindow.hpp"
#include "removecommitwindow.hpp"
#include "setting.hpp"
#include "about.hpp"
#include "history.hpp"
#include "readandwritejson.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class HorizonJuicerCreator; }
QT_END_NAMESPACE

class HorizonJuicerCreator : public QMainWindow
{
    Q_OBJECT

public:
    HorizonJuicerCreator(QWidget *parent = nullptr);
    ~HorizonJuicerCreator();

private slots:
    void on_creatNewMachineButton_clicked();

    void on_removeCommitsButton_clicked();

    void on_actionSettings_triggered();

    void on_actionAbout_triggered();

    void on_actionHistory_triggered();

    void showWindow();

private:
    Ui::HorizonJuicerCreator *ui;
    CreatorWindow *creatorWindow;
    RemoveCommitWindow *removeCommitWindow;
    Setting *setting;
    About *about;
    History *history;
    void setVersion();
    ReadAndWriteJson *r;
    QString version = "3.24.0";
};
#endif // HORIZONJUICERCREATOR_H
