#include "creatorwindow.hpp"
#include "ui_creatorwindow.h"
#include <QMenu>
#include <QJsonDocument>
#include <QFile>
#include <iostream>
#include <string>
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
    setWindowTitle("创建配置");
    r = new ReadAndWriteJson;
    c = new ConvertCode;

    getMachineInfo();
    loadComboBoxSet();

    QMovie *movie = new QMovie(":./processing.gif");
    movie->setScaledSize(ui->labelProcessing->size());
    ui->labelProcessing->setMovie(movie);
    movie->start();
    ui->labelProcessing->hide();

    generator = new GeneratePro();
    t = new QThread;
    generator->moveToThread(t);
    t->start();

    connect(this, SIGNAL(triggerProcess()), generator, SLOT(startGenerate()));
    connect(generator, SIGNAL(triggerStartingProcess()), this, SLOT(startingProcess()));
    connect(generator, SIGNAL(triggerFinishedProcess()), this, SLOT(finishedProcess()));
}

CreatorWindow::~CreatorWindow()
{
    delete ui;
    delete r;
    delete c;
}

void CreatorWindow::getMachineInfo() {
    QJsonObject obj = r->readJsonToObj();

    if (!obj["machineName"].isNull())
        ui->lineEditMachineName->setText(obj["machineName"].toString());
    if (!obj["machineNameLng"].isNull()) {
        QString a = obj["machineNameLng"].toString();
        ui->lineEditMachineNameLng->setText(a);
    }
    if (!obj["machineIndex"].isNull())
        ui->lineEditMachineIndex->setText(obj["machineIndex"].toString());
    if (!obj["customInfo"].isNull()) {
        QString a = obj["customInfo"].toString();
        ui->lineEditCustomInfo->setText(a);
    }
    if (!obj["lng"].isNull())
        ui->comboBoxLng->setCurrentIndex(obj["lng"].toInt());
}

void CreatorWindow::loadComboBoxSet() {
    QJsonObject obj = r->readJsonToObj();

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
    if (!obj["probePos"].isNull())
        ui->comboBoxProbePos->setCurrentIndex(obj["probePos"].toInt());
    if (!obj["ifCenter"].isNull())
        ui->comboBoxIfCenter->setCurrentIndex(obj["ifCenter"].toInt());
    if (!obj["ifHasU"].isNull())
        ui->comboBoxIfHasU->setCurrentIndex(obj["ifHasU"].toInt());
    if (!obj["ifNotHasUExternalPos"].isNull())
        ui->comboBoxIfNotHasUExternalPos->setCurrentIndex(obj["ifNotHasUExternalPos"].toInt());
    if (!obj["ifHasA"].isNull())
        ui->comboBoxIfHasA->setCurrentIndex(obj["ifHasA"].toInt());
    if (!obj["grindWheelType"].isNull())
        ui->comboBoxGrindWheelType->setCurrentIndex(obj["grindWheelType"].toInt());
    if (!obj["dressWheelType"].isNull())
        ui->comboBoxDressWheelType->setCurrentIndex(obj["dressWheelType"].toInt());
    if (!obj["ifRemoveComments"].isNull())
        ui->comboBoxIfRemoveComments->setCurrentIndex(obj["ifRemoveComments"].toInt());
    if (!obj["hmiMode"].isNull())
        ui->comboBoxHMIMode->setCurrentIndex(obj["hmiMode"].toInt());

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
    centerExternalSet(ui->comboBoxIfHasU->currentIndex());
    probePosSet(ui->comboBoxMeasureMethord->currentIndex());

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
    probePosSet(ui->comboBoxMeasureMethord->currentIndex());
}

void CreatorWindow::centerSet(int index) {
    if (ui->comboBoxMachineType->currentIndex() == 0 || ui->comboBoxMachineType->currentIndex() == NULL) {
        ui->comboBoxIfCenter->setHidden(true);
        ui->labelIfCenter->setHidden(true);
        ui->comboBoxIfHasU->setHidden(true);
        ui->labelIfHasU->setHidden(true);
        ui->comboBoxIfNotHasUExternalPos->setHidden(true);
        ui->labelIfNotHasUExternalPos->setHidden(true);
    } else {
        ui->comboBoxIfCenter->setHidden(false);
        ui->labelIfCenter->setHidden(false);
        if (index == 0 || index == NULL) {
            ui->comboBoxIfHasU->setHidden(false);
            ui->labelIfHasU->setHidden(false);
            if (ui->comboBoxIfHasU->currentIndex() == 0 || ui->comboBoxIfHasU->currentIndex() == NULL) {
                ui->comboBoxIfNotHasUExternalPos->setHidden(true);
                ui->labelIfNotHasUExternalPos->setHidden(true);
            } else {
                ui->comboBoxIfNotHasUExternalPos->setHidden(false);
                ui->labelIfNotHasUExternalPos->setHidden(false);
            }
            qobject_cast<QListView *>(ui->comboBoxMeasureMethord->view())->setRowHidden(0, true);
            ui->comboBoxMeasureMethord->setCurrentIndex(1);
        } else {
            ui->comboBoxIfHasU->setHidden(true);
            ui->labelIfHasU->setHidden(true);
            ui->comboBoxIfNotHasUExternalPos->setHidden(true);
            ui->labelIfNotHasUExternalPos->setHidden(true);

            qobject_cast<QListView *>(ui->comboBoxMeasureMethord->view())->setRowHidden(0, false);
        }
    }
    centerExternalSet(ui->comboBoxIfHasU->currentIndex());
}

void CreatorWindow::centerExternalSet(int index) {
    if (ui->comboBoxMachineType->currentIndex() == 0 || ui->comboBoxMachineType->currentIndex() == NULL) {
        ui->comboBoxIfNotHasUExternalPos->setHidden(true);
        ui->labelIfNotHasUExternalPos->setHidden(true);
    } else {
        if (ui->comboBoxIfCenter->currentIndex() == 0 || ui->comboBoxIfCenter->currentIndex() == NULL) {
            if (index == 0 || index == NULL) {
                ui->comboBoxIfNotHasUExternalPos->setHidden(true);
                ui->labelIfNotHasUExternalPos->setHidden(true);
            } else {
                ui->comboBoxIfNotHasUExternalPos->setHidden(false);
                ui->labelIfNotHasUExternalPos->setHidden(false);
            }
        } else {
            ui->comboBoxIfNotHasUExternalPos->setHidden(true);
            ui->labelIfNotHasUExternalPos->setHidden(true);
        }
    }
}

void CreatorWindow::probePosSet(int index) {
    if (ui->comboBoxMachineType->currentIndex() == 0 || ui->comboBoxMachineType->currentIndex() == NULL) {
        ui->comboBoxProbePos->setHidden(true);
        ui->labelProbePos->setHidden(true);
    } else {
        if (ui->comboBoxIfOperation->currentIndex() == 0 || ui->comboBoxIfOperation->currentIndex() == NULL) {
            if (index == 0 || index == NULL) {
                ui->comboBoxProbePos->setHidden(true);
                ui->labelProbePos->setHidden(true);
            } else {
                ui->comboBoxProbePos->setHidden(false);
                ui->labelProbePos->setHidden(false);
            }
        } else {
            ui->comboBoxProbePos->setHidden(true);
            ui->labelProbePos->setHidden(true);
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

void CreatorWindow::on_comboBoxMeasureMethord_currentIndexChanged(int index)
{
    probePosSet(index);
}

void CreatorWindow::on_comboBoxIfCenter_currentIndexChanged(int index)
{
    centerSet(index);
}

void CreatorWindow::on_comboBoxIfHasU_currentIndexChanged(int index)
{
    centerExternalSet(index);
}

void CreatorWindow::on_saveDataPushButton_clicked()
{
    QString machineName = ui->lineEditMachineName->text();
    QString machineNameLng = ui->lineEditMachineNameLng->text();
    QString machineIndex = ui->lineEditMachineIndex->text();
    QString customInfo = ui->lineEditCustomInfo->text();
    int lng = ui->comboBoxLng->currentIndex();

    if ((machineName !="") && (machineNameLng !="") && (machineIndex !="") && (customInfo !="")) {
        QJsonObject obj = r->readJsonToObj();

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
        obj.insert("probePos", ui->comboBoxProbePos->currentIndex());
        obj.insert("ifCenter", ui->comboBoxIfCenter->currentIndex());
        obj.insert("ifHasU", ui->comboBoxIfHasU->currentIndex());
        obj.insert("ifNotHasUExternalPos", ui->comboBoxIfNotHasUExternalPos->currentIndex());
        obj.insert("ifHasA", ui->comboBoxIfHasA->currentIndex());
        obj.insert("grindWheelType", ui->comboBoxGrindWheelType->currentIndex());
        obj.insert("dressWheelType", ui->comboBoxDressWheelType->currentIndex());
        obj.insert("ifRemoveComments", ui->comboBoxIfRemoveComments->currentIndex());
        obj.insert("hmiMode", ui->comboBoxHMIMode->currentIndex());

        r->saveObjToJson(obj);

        ui->labelInfo->setText("保存成功");

    } else {
        ui->labelInfo->setText("机床信息设置有误");
    }
}

void CreatorWindow::on_creatPushButton_clicked()
{
    on_saveDataPushButton_clicked();

    QJsonObject obj = r->readJsonToObj();

    if (!obj["programDir"].isNull()) {
        QJsonObject a = obj["programDir"].toObject();
        if (!a["sourceDir"].isNull() && !a["destDir"].isNull() && QDir(a["sourceDir"].toString()).exists() && QDir(a["destDir"].toString()).exists()) {
            // QWidget::close();
            //qDebug() << "Current thread:" << thread();
            //generator->startGenerate();

            emit triggerProcess();
        } else {
            setting = new Setting;
            setting->show();
        }
    } else {
        setting = new Setting;
        setting->show();
    }
}

void CreatorWindow::startingProcess() {
    ui->creatPushButton->setText("正在生成");
    ui->creatPushButton->setDisabled(true);
    ui->saveDataPushButton->setDisabled(true);
    ui->labelInfo->hide();
    ui->labelProcessing->show();
}

void CreatorWindow::finishedProcess() {

    ui->creatPushButton->setText("程序生成");
    ui->creatPushButton->setDisabled(false);
    ui->saveDataPushButton->setDisabled(false);
    ui->labelProcessing->hide();
    ui->labelInfo->show();
    ui->labelInfo->setStyleSheet("QLabel { color : red; }");
    ui->labelInfo->setText("程序已生成");

    QDesktopServices::openUrl(QUrl("file:///" + r->getDestDir(), QUrl::TolerantMode));
}

