#include "creatorwindow.hpp"
#include "ui_creatorwindow.h"
#include "readandwritejson.hpp"
#include <QMenu>
#include <QJsonDocument>
#include <QFile>
#include <iostream>
#include <string>
#include <convertcode.hpp>
#include <QListView>
#include <QDir>
#include <QMovie>
#include <QDesktopServices>

using namespace std;

CreatorWindow::CreatorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreatorWindow)
{
    ui->setupUi(this);
    getMachineInfo();
    loadComboBoxSet();

    QMovie *movie = new QMovie(":./processing.gif");
    movie->setScaledSize(ui->labelProcessing->size());
    ui->labelProcessing->setMovie(movie);
    movie->start();

    generator = new GeneratePro();
    t = new QThread;
    generator->moveToThread(t);
    t->start();
}

CreatorWindow::~CreatorWindow()
{
    delete ui;
}

void CreatorWindow::getMachineInfo() {
    ConvertCode c;
    ReadAndWriteJson r;
    QJsonObject obj = r.readJsonToObj();

    if (!obj["machineName"].isNull())
        ui->lineEditMachineName->setText(obj["machineName"].toString());
    if (!obj["machineNameLng"].isNull()) {
        string a = obj["machineNameLng"].toString().toStdString();
        a = c.UTF8ToGBK(a);
        ui->lineEditMachineNameLng->setText(QString::fromStdString(a));
    }
    if (!obj["machineIndex"].isNull())
        ui->lineEditMachineIndex->setText(obj["machineIndex"].toString());
    if (!obj["customInfo"].isNull()) {
        string a = obj["customInfo"].toString().toStdString();
        a = c.UTF8ToGBK(a);
        ui->lineEditCustomInfo->setText(QString::fromStdString(a));
    }
    if (!obj["lng"].isNull())
        ui->comboBoxLng->setCurrentIndex(obj["lng"].toInt());

    /*
    string b = obj["customInfo"].toString().toStdString();
    cout << b << endl;
    b = c.UTF8ToGBK(b);
    b = c.UTF8ToGBK(b);
    cout << b << endl;
    */

}

void CreatorWindow::on_saveDataPushButton_clicked()
{
    ConvertCode c;

    QString machineName = ui->lineEditMachineName->text();
    QString machineNameLng = ui->lineEditMachineNameLng->text();
    QString machineIndex = ui->lineEditMachineIndex->text();
    QString customInfo = ui->lineEditCustomInfo->text();
    int lng = ui->comboBoxLng->currentIndex();

    if ((machineName !="") && (machineNameLng !="") && (machineIndex !="") && (customInfo !="")) {
        ReadAndWriteJson r;
        QJsonObject obj = r.readJsonToObj();

        obj.insert("machineName", machineName);
        obj.insert("machineNameLng", machineNameLng);
        obj.insert("machineIndex", machineIndex);
        obj.insert("customInfo", customInfo);
        obj.insert("lng", lng);

        obj.insert("machineType", ui->comboBoxMachineType->currentIndex());
        obj.insert("ifHasScrewTap", ui->comboBoxIfHasScrewTap->currentIndex());
        obj.insert("wareType", ui->comboBoxWareType->currentIndex());
        obj.insert("ifHasWorm", ui->comboBoxIfHasWorm->currentIndex());
        obj.insert("wheelType", ui->comboBoxWheelType->currentIndex());
        obj.insert("shapeType", ui->comboBoxShapeType->currentIndex());
        obj.insert("ifHasReOp", ui->comboBoxIfHasReOp->currentIndex());
        obj.insert("ifOperation", ui->comboBoxIfOperation->currentIndex());
        obj.insert("measureMethord", ui->comboBoxMeasureMethord->currentIndex());
        obj.insert("ifCenter", ui->comboBoxIfCenter->currentIndex());
        obj.insert("ifHasU", ui->comboBoxIfHasU->currentIndex());
        obj.insert("ifHasA", ui->comboBoxIfHasA->currentIndex());
        obj.insert("grindWheelType", ui->comboBoxGrindWheelType->currentIndex());
        obj.insert("dressWheelType", ui->comboBoxDressWheelType->currentIndex());
        obj.insert("roughFeedInput", ui->comboBoxRoughFeedInput->currentIndex());
        obj.insert("ifRemoveComments", ui->comboBoxIfRemoveComments->currentIndex());

        r.saveObjToJson(obj);

    } else {
        ui->labelError->setText("机床信息设置有误");
    }

}

void CreatorWindow::loadComboBoxSet() {
    ReadAndWriteJson r;
    QJsonObject obj = r.readJsonToObj();

    if (!obj["machineType"].isNull())
        ui->comboBoxMachineType->setCurrentIndex(obj["machineType"].toInt());
    if (!obj["ifHasScrewTap"].isNull())
        ui->comboBoxIfHasScrewTap->setCurrentIndex(obj["ifHasScrewTap"].toInt());
    if (!obj["wareType"].isNull())
        ui->comboBoxWareType->setCurrentIndex(obj["wareType"].toInt());
    if (!obj["ifHasWorm"].isNull())
        ui->comboBoxIfHasWorm->setCurrentIndex(obj["ifHasWorm"].toInt());
    if (!obj["wheelType"].isNull())
        ui->comboBoxWheelType->setCurrentIndex(obj["wheelType"].toInt());
    if (!obj["shapeType"].isNull())
        ui->comboBoxShapeType->setCurrentIndex(obj["shapeType"].toInt());
    if (!obj["ifHasReOp"].isNull())
        ui->comboBoxIfHasReOp->setCurrentIndex(obj["ifHasReOp"].toInt());
    if (!obj["ifOperation"].isNull())
        ui->comboBoxIfOperation->setCurrentIndex(obj["ifOperation"].toInt());
    if (!obj["measureMethord"].isNull())
        ui->comboBoxMeasureMethord->setCurrentIndex(obj["measureMethord"].toInt());
    if (!obj["ifCenter"].isNull())
        ui->comboBoxIfCenter->setCurrentIndex(obj["ifCenter"].toInt());
    if (!obj["ifHasU"].isNull())
        ui->comboBoxIfHasU->setCurrentIndex(obj["ifHasU"].toInt());
    if (!obj["ifHasA"].isNull())
        ui->comboBoxIfHasA->setCurrentIndex(obj["ifHasA"].toInt());
    if (!obj["grindWheelType"].isNull())
        ui->comboBoxGrindWheelType->setCurrentIndex(obj["grindWheelType"].toInt());
    if (!obj["dressWheelType"].isNull())
        ui->comboBoxDressWheelType->setCurrentIndex(obj["dressWheelType"].toInt());
    if (!obj["roughFeedInput"].isNull())
        ui->comboBoxRoughFeedInput->setCurrentIndex(obj["roughFeedInput"].toInt());
    if (!obj["ifRemoveComments"].isNull())
        ui->comboBoxIfRemoveComments->setCurrentIndex(obj["ifRemoveComments"].toInt());

    machineTypeComboBoxSet(obj["machineType"].toInt());

}

void CreatorWindow::machineTypeComboBoxSet(int index) {
    if (index == 0 || index == NULL) {
        ui->comboBoxIfHasScrewTap->setHidden(false);
        ui->labelIfHasScrewTap->setHidden(false);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(0, false);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(1, false);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(2, false);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(3, true);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(4, false);

        if (ui->comboBoxWareType->currentIndex() == 3)
            ui->comboBoxWareType->setCurrentIndex(0);

        ui->comboBoxIfHasReOp->setHidden(false);
        ui->labelIfHasReOp->setHidden(false);

    } else {
        ui->comboBoxIfHasScrewTap->setHidden(true);
        ui->labelIfHasScrewTap->setHidden(true);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(0, true);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(1, true);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(2, false);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(3, false);
        qobject_cast<QListView *>(ui->comboBoxWareType->view())->setRowHidden(4, true);

        if (ui->comboBoxWareType->currentIndex() == 0 || ui->comboBoxWareType->currentIndex() == 1 || ui->comboBoxWareType->currentIndex() == 4)
            ui->comboBoxWareType->setCurrentIndex(2);

        ui->comboBoxIfHasReOp->setHidden(true);
        ui->labelIfHasReOp->setHidden(true);

    }

    wareTypeComboBoxSet(ui->comboBoxWareType->currentIndex());
    operationComboBoxSet(ui->comboBoxIfOperation->currentIndex());
    centerSet(ui->comboBoxIfCenter->currentIndex());

}

void CreatorWindow::wareTypeComboBoxSet(int index) {
    if (ui->comboBoxMachineType->currentIndex() == 0 && (index == 0 || index == 2 || index == NULL)) {
        ui->comboBoxIfHasWorm->setHidden(false);
        ui->labelIfHasWorm->setHidden(false);
    } else {
        ui->comboBoxIfHasWorm->setHidden(true);
        ui->labelIfHasWorm->setHidden(true);
    }

    if (index == 0 || index == 2 || index == NULL) {
        ui->comboBoxWheelType->setHidden(false);
        ui->labelWheelType->setHidden(false);
        ui->comboBoxShapeType->setHidden(false);
        ui->labelShapeType->setHidden(false);
    } else {
        ui->comboBoxWheelType->setHidden(true);
        ui->labelWheelType->setHidden(true);
        ui->comboBoxShapeType->setHidden(true);
        ui->labelShapeType->setHidden(true);
    }
}

void CreatorWindow::operationComboBoxSet(int index) {
    if (index == 0 || index == NULL) {
        ui->comboBoxMeasureMethord->setHidden(false);
        ui->labelMeasureMethord->setHidden(false);
        if (ui->comboBoxMachineType->currentIndex() == 0) {
            qobject_cast<QListView *>(ui->comboBoxMeasureMethord->view())->setRowHidden(0, false);
            qobject_cast<QListView *>(ui->comboBoxMeasureMethord->view())->setRowHidden(1, true);
            qobject_cast<QListView *>(ui->comboBoxMeasureMethord->view())->setRowHidden(2, false);

            if (ui->comboBoxMeasureMethord->currentIndex() == 1)
                ui->comboBoxMeasureMethord->setCurrentIndex(0);
        } else {
            qobject_cast<QListView *>(ui->comboBoxMeasureMethord->view())->setRowHidden(0, false);
            qobject_cast<QListView *>(ui->comboBoxMeasureMethord->view())->setRowHidden(1, false);
            qobject_cast<QListView *>(ui->comboBoxMeasureMethord->view())->setRowHidden(2, true);

            if (ui->comboBoxMeasureMethord->currentIndex() == 2)
                ui->comboBoxMeasureMethord->setCurrentIndex(0);
        }
    } else {
        ui->comboBoxMeasureMethord->setHidden(true);
        ui->labelMeasureMethord->setHidden(true);
    }
}

void CreatorWindow::centerSet(int index) {
    if (ui->comboBoxMachineType->currentIndex() == 0 || ui->comboBoxMachineType->currentIndex() == NULL) {
        ui->comboBoxIfCenter->setHidden(true);
        ui->labelIfCenter->setHidden(true);
        ui->comboBoxIfHasU->setHidden(true);
        ui->labelIfHasU->setHidden(true);
    } else {
        ui->comboBoxIfCenter->setHidden(false);
        ui->labelIfCenter->setHidden(false);
        if (index == 0 || index == NULL) {
            ui->comboBoxIfHasU->setHidden(false);
            ui->labelIfHasU->setHidden(false);
        } else {
            ui->comboBoxIfHasU->setHidden(true);
            ui->labelIfHasU->setHidden(true);
        }
    }
}

void CreatorWindow::on_comboBoxMachineType_currentIndexChanged(int index)
{
    machineTypeComboBoxSet(index);
}

void CreatorWindow::on_comboBoxWareType_currentIndexChanged(int index)
{
    wareTypeComboBoxSet(index);
}

void CreatorWindow::on_comboBoxIfOperation_currentIndexChanged(int index)
{
    operationComboBoxSet(index);
}

void CreatorWindow::on_comboBoxIfCenter_currentIndexChanged(int index)
{
    centerSet(index);
}

void CreatorWindow::on_creatPushButton_clicked()
{
    on_saveDataPushButton_clicked();

    ReadAndWriteJson r;
    QJsonObject obj = r.readJsonToObj();

    if (!obj["programDir"].isNull()) {
        QJsonObject a = obj["programDir"].toObject();
        if (!a["sourceDir"].isNull() && !a["destDir"].isNull() && QDir(a["sourceDir"].toString()).exists() && QDir(a["destDir"].toString()).exists()) {
            // QWidget::close();

            ui->labelInfo->setStyleSheet("QLabel { color : red; }");
            ui->labelInfo->setText("正在生成程序...");
            //qDebug() << "Current thread:" << thread();

            generator->startGenerate();
            //generator->test();

            ui->labelInfo->setText("程序已生成");

            QDesktopServices::openUrl(QUrl("file:///" + r.getDestDir()));

        } else {
            setting = new Setting;
            setting->show();
        }
    } else {
        setting = new Setting;
        setting->show();
    }
}
