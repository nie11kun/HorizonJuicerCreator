#ifndef CREATORWINDOW_HPP
#define CREATORWINDOW_HPP

#include <QWidget>
#include "setting.hpp"
#include "generatepro.h"
#include <QThread>

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
    void on_saveDataPushButton_clicked();

    void on_comboBoxMachineType_currentIndexChanged(int index);


    void on_comboBoxWareType_currentIndexChanged(int index);

    void on_comboBoxIfOperation_currentIndexChanged(int index);

    void on_comboBoxIfCenter_currentIndexChanged(int index);

    void on_creatPushButton_clicked();

private:
    Ui::CreatorWindow *ui;
    void getMachineInfo();
    void loadComboBoxSet();
    void machineTypeComboBoxSet(int index);
    void wareTypeComboBoxSet(int index);
    void operationComboBoxSet(int index);
    void centerSet(int index);
    Setting *setting;
    GeneratePro *generator;
    QThread *t;

signals:
    void startOtherThread();

};

#endif // CREATORWINDOW_HPP
