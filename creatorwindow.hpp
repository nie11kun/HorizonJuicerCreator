#ifndef CREATORWINDOW_HPP
#define CREATORWINDOW_HPP

#include <QWidget>
#include "setting.hpp"
#include "generatepro.h"
#include <QThread>
#include "readandwritejson.hpp"
#include "convertcode.hpp"

namespace Ui {
class CreatorWindow;
}

class CreatorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreatorWindow(QWidget *parent = nullptr);
    ~CreatorWindow();

private slots:
    int on_saveDataPushButton_clicked();

    void on_comboBoxMachineType_currentIndexChanged(int index);


    void on_comboBoxWareType_currentIndexChanged(int index);

    void on_comboBoxIfOperation_currentIndexChanged(int index);

    void on_comboBoxIfCenter_currentIndexChanged(int index);

    void on_creatPushButton_clicked();

    void startingProcess();
    void finishedProcess();

    void on_comboBoxIfHasU_currentIndexChanged(int index);

    void on_comboBoxMeasureMethord_currentIndexChanged(int index);

    void on_backButton_clicked();

private:
    Ui::CreatorWindow *ui;
    void getMachineInfo();
    void loadComboBoxSet();
    void machineTypeComboBoxSet(int index);
    void wareTypeComboBoxSet(int index);
    void operationComboBoxSet(int index);
    void probePosSet(int index);
    void centerSet(int index);
    void centerExternalSet(int index);
    Setting *setting;
    GeneratePro *generator;
    QThread *t;
    ReadAndWriteJson *r;
    ConvertCode *c;

signals:
    void triggerProcess();
    void triggerBackToMain();

};

#endif // CREATORWINDOW_HPP
