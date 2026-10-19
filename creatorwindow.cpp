/**
 * @file creatorwindow.cpp
 * @brief Machine program creator window implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "creatorwindow.hpp"
#include "ui_creatorwindow.h"

#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QListView>
#include <QMenu>
#include <QMovie>

#include <iostream>
#include <string>

using namespace std;

CreatorWindow::CreatorWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreatorWindow) {
  ui->setupUi(this);
  setWindowTitle("创建配置");
  setWindowIcon(QIcon(":/icons/gear.svg"));
  ui->backButton->setIcon(QIcon(":/icons/arrow-left.svg"));
  ui->backButton->setIconSize(QSize(15, 15));
  ui->saveDataPushButton->setIcon(QIcon(":/icons/save.svg"));
  ui->saveDataPushButton->setIconSize(QSize(16, 16));
  ui->creatPushButton->setIcon(QIcon(":/icons/bolt.svg"));
  ui->creatPushButton->setIconSize(QSize(16, 16));
  jsonHandler = new ReadAndWriteJson;
  converter = new ConvertCode;

  getMachineInfo();
  loadComboBoxSet();

  // Setup processing animation and initial status
  QMovie *processingAnimation = new QMovie(":./processing.gif");
  processingAnimation->setScaledSize(QSize(110, 110));
  ui->labelProcessing->setMovie(processingAnimation);
  processingAnimation->start();
  ui->labelProcessing->hide();
  ui->labelIdleIcon->setPixmap(QPixmap(":/icons/gear.svg").scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  ui->labelIdleIcon->show();

  // Setup generator worker thread
  generator = new GeneratePro();
  workerThread = new QThread;
  generator->moveToThread(workerThread);
  workerThread->start();

  // Connect signals for processing
  connect(this, SIGNAL(triggerProcess()), generator, SLOT(startGenerate()));
  connect(generator, SIGNAL(triggerStartingProcess()), this,
          SLOT(startingProcess()));
  connect(generator, SIGNAL(triggerFinishedProcess()), this,
          SLOT(finishedProcess()));
}

CreatorWindow::~CreatorWindow() {
  delete ui;
  delete jsonHandler;
  delete converter;
}

//=============================================================================
// Configuration Loading
//=============================================================================

void CreatorWindow::getMachineInfo() {
  QJsonObject config = jsonHandler->readJsonToObj();

  if (!config["machineName"].isNull())
    ui->lineEditMachineName->setText(config["machineName"].toString());
  if (!config["machineNameLng"].isNull()) {
    QString machineNameLng = config["machineNameLng"].toString();
    ui->lineEditMachineNameLng->setText(machineNameLng);
  }
  if (!config["machineIndex"].isNull())
    ui->lineEditMachineIndex->setText(config["machineIndex"].toString());
  if (!config["customInfo"].isNull()) {
    QString customInfo = config["customInfo"].toString();
    ui->lineEditCustomInfo->setText(customInfo);
  }
  if (!config["lng"].isNull())
    ui->comboBoxLng->setCurrentIndex(config["lng"].toInt());
}

void CreatorWindow::loadComboBoxSet() {
  QJsonObject config = jsonHandler->readJsonToObj();

  if (!config["machineType"].isNull())
    ui->comboBoxMachineType->setCurrentIndex(config["machineType"].toInt());
  if (!config["ifHasScrewTap"].isNull())
    ui->comboBoxIfHasScrewTap->setCurrentIndex(config["ifHasScrewTap"].toInt());
  if (!config["wareType"].isNull())
    ui->comboBoxWareType->setCurrentIndex(config["wareType"].toInt());
  if (!config["ifHasWorm"].isNull())
    ui->comboBoxIfHasWorm->setCurrentIndex(config["ifHasWorm"].toInt());
  if (!config["wheelType"].isNull())
    ui->comboBoxWheelType->setCurrentIndex(config["wheelType"].toInt());
  if (!config["shapeType"].isNull())
    ui->comboBoxShapeType->setCurrentIndex(config["shapeType"].toInt());
  if (!config["ifHasReOp"].isNull())
    ui->comboBoxIfHasReOp->setCurrentIndex(config["ifHasReOp"].toInt());
  if (!config["ifOperation"].isNull())
    ui->comboBoxIfOperation->setCurrentIndex(config["ifOperation"].toInt());
  if (!config["measureMethord"].isNull())
    ui->comboBoxMeasureMethord->setCurrentIndex(
        config["measureMethord"].toInt());
  if (!config["probePos"].isNull())
    ui->comboBoxProbePos->setCurrentIndex(config["probePos"].toInt());
  if (!config["ifCenter"].isNull())
    ui->comboBoxIfCenter->setCurrentIndex(config["ifCenter"].toInt());
  if (!config["ifHasU"].isNull())
    ui->comboBoxIfHasU->setCurrentIndex(config["ifHasU"].toInt());
  if (!config["ifNotHasUExternalPos"].isNull())
    ui->comboBoxIfNotHasUExternalPos->setCurrentIndex(
        config["ifNotHasUExternalPos"].toInt());
  if (!config["ifHasA"].isNull())
    ui->comboBoxIfHasA->setCurrentIndex(config["ifHasA"].toInt());
  if (!config["grindWheelType"].isNull())
    ui->comboBoxGrindWheelType->setCurrentIndex(
        config["grindWheelType"].toInt());
  if (!config["exGrindWheelType"].isNull())
    ui->comboBoxExGrindWheelType->setCurrentIndex(
        config["exGrindWheelType"].toInt());
  if (!config["dressWheelType"].isNull())
    ui->comboBoxDressWheelType->setCurrentIndex(
        config["dressWheelType"].toInt());
  if (!config["ifRemoveComments"].isNull())
    ui->comboBoxIfRemoveComments->setCurrentIndex(
        config["ifRemoveComments"].toInt());
  if (!config["hmiMode"].isNull())
    ui->comboBoxHMIMode->setCurrentIndex(config["hmiMode"].toInt());
  if (!config["systemMode"].isNull())
    ui->comboBoxSystemMode->setCurrentIndex(config["systemMode"].toInt());
  if (!config["ifHasLoadingArm"].isNull())
    ui->comboBoxLoadingArm->setCurrentIndex(config["ifHasLoadingArm"].toInt());
  if (!config["ifHasEncryption"].isNull())
    ui->comboBoxEncryption->setCurrentIndex(config["ifHasEncryption"].toInt());
  if (!config["ifHasNoneTradeMark"].isNull())
    ui->comboBoxNoneTradeMark->setCurrentIndex(config["ifHasNoneTradeMark"].toInt());

  machineTypeComboBoxSet(config["machineType"].toInt());
}

//=============================================================================
// ComboBox Configuration Logic
//=============================================================================

void CreatorWindow::machineTypeComboBoxSet(int index) {
  QListView *wareTypeView =
      qobject_cast<QListView *>(ui->comboBoxWareType->view());

  if (index == 0 || index == NULL) {
    // External grinding machine type
    ui->comboBoxIfHasScrewTap->setHidden(false);
    ui->labelIfHasScrewTap->setHidden(false);
    wareTypeView->setRowHidden(0, false);
    wareTypeView->setRowHidden(1, false);
    wareTypeView->setRowHidden(2, false);
    wareTypeView->setRowHidden(3, true);
    wareTypeView->setRowHidden(4, false);
    wareTypeView->setRowHidden(5, false);
    wareTypeView->setRowHidden(6, true);

    if (ui->comboBoxWareType->currentIndex() == 3 ||
        ui->comboBoxWareType->currentIndex() == 6)
      ui->comboBoxWareType->setCurrentIndex(0);

    ui->comboBoxIfHasReOp->setHidden(false);
    ui->labelIfHasReOp->setHidden(false);
    ui->labelGrindWheelType->setText("外磨砂轮驱动");
  } else {
    // Internal grinding machine type
    ui->comboBoxIfHasScrewTap->setHidden(true);
    ui->labelIfHasScrewTap->setHidden(true);
    wareTypeView->setRowHidden(0, true);
    wareTypeView->setRowHidden(1, true);
    wareTypeView->setRowHidden(2, false);
    wareTypeView->setRowHidden(3, false);
    wareTypeView->setRowHidden(4, true);
    wareTypeView->setRowHidden(5, false);
    wareTypeView->setRowHidden(6, false);

    if (ui->comboBoxWareType->currentIndex() == 0 ||
        ui->comboBoxWareType->currentIndex() == 1 ||
        ui->comboBoxWareType->currentIndex() == 4)
      ui->comboBoxWareType->setCurrentIndex(2);

    ui->comboBoxIfHasReOp->setHidden(true);
    ui->labelIfHasReOp->setHidden(true);
    ui->labelGrindWheelType->setText("内磨砂轮驱动");
  }

  wareTypeComboBoxSet(ui->comboBoxWareType->currentIndex());
  operationComboBoxSet(ui->comboBoxIfOperation->currentIndex());
  centerSet(ui->comboBoxIfCenter->currentIndex());
  centerExternalSet(ui->comboBoxIfHasU->currentIndex());
  probePosSet(ui->comboBoxMeasureMethord->currentIndex());
}

void CreatorWindow::wareTypeComboBoxSet(int index) {
  bool isExternalMachine = (ui->comboBoxMachineType->currentIndex() == 0);
  bool showWormOption = isExternalMachine && (index == 0 || index == 2 ||
                                              index == 5 || index == 6 ||
                                              index == NULL);

  ui->comboBoxIfHasWorm->setHidden(!showWormOption);
  ui->labelIfHasWorm->setHidden(!showWormOption);

  bool showWheelOptions =
      (index == 0 || index == 2 || index == 5 || index == 6 || index == NULL);
  ui->comboBoxWheelType->setHidden(!showWheelOptions);
  ui->labelWheelType->setHidden(!showWheelOptions);
  ui->comboBoxShapeType->setHidden(!showWheelOptions);
  ui->labelShapeType->setHidden(!showWheelOptions);
}

void CreatorWindow::operationComboBoxSet(int index) {
  QListView *measureView =
      qobject_cast<QListView *>(ui->comboBoxMeasureMethord->view());

  if (index == 0 || index == NULL) {
    ui->comboBoxMeasureMethord->setHidden(false);
    ui->labelMeasureMethord->setHidden(false);

    if (ui->comboBoxMachineType->currentIndex() == 0) {
      measureView->setRowHidden(0, false);
      measureView->setRowHidden(1, true);
      measureView->setRowHidden(2, false);

      if (ui->comboBoxMeasureMethord->currentIndex() == 1)
        ui->comboBoxMeasureMethord->setCurrentIndex(0);
    } else {
      measureView->setRowHidden(0, false);
      measureView->setRowHidden(1, false);
      measureView->setRowHidden(2, true);

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
  bool isExternalMachine = (ui->comboBoxMachineType->currentIndex() == 0 ||
                            ui->comboBoxMachineType->currentIndex() == NULL);

  if (isExternalMachine) {
    ui->comboBoxIfCenter->setHidden(true);
    ui->labelIfCenter->setHidden(true);
    ui->comboBoxIfHasU->setHidden(true);
    ui->labelIfHasU->setHidden(true);
    ui->comboBoxIfNotHasUExternalPos->setHidden(true);
    ui->labelIfNotHasUExternalPos->setHidden(true);
    ui->comboBoxExGrindWheelType->setHidden(true);
    ui->labelExGrindWheelType->setHidden(true);
  } else {
    ui->comboBoxIfCenter->setHidden(false);
    ui->labelIfCenter->setHidden(false);

    if (index == 0 || index == NULL) {
      ui->comboBoxIfHasU->setHidden(false);
      ui->labelIfHasU->setHidden(false);
      ui->comboBoxExGrindWheelType->setHidden(false);
      ui->labelExGrindWheelType->setHidden(false);

      bool hasU = (ui->comboBoxIfHasU->currentIndex() == 0 ||
                   ui->comboBoxIfHasU->currentIndex() == NULL);
      ui->comboBoxIfNotHasUExternalPos->setHidden(hasU);
      ui->labelIfNotHasUExternalPos->setHidden(hasU);
    } else {
      ui->comboBoxIfHasU->setHidden(true);
      ui->labelIfHasU->setHidden(true);
      ui->comboBoxExGrindWheelType->setHidden(true);
      ui->labelExGrindWheelType->setHidden(true);
      ui->comboBoxIfNotHasUExternalPos->setHidden(true);
      ui->labelIfNotHasUExternalPos->setHidden(true);
    }
  }
  centerExternalSet(ui->comboBoxIfHasU->currentIndex());
}

void CreatorWindow::centerExternalSet(int index) {
  bool isExternalMachine = (ui->comboBoxMachineType->currentIndex() == 0 ||
                            ui->comboBoxMachineType->currentIndex() == NULL);

  if (isExternalMachine) {
    ui->comboBoxIfNotHasUExternalPos->setHidden(true);
    ui->labelIfNotHasUExternalPos->setHidden(true);
  } else {
    bool centerMode = (ui->comboBoxIfCenter->currentIndex() == 0 ||
                       ui->comboBoxIfCenter->currentIndex() == NULL);

    if (centerMode) {
      bool hasU = (index == 0 || index == NULL);
      ui->comboBoxIfNotHasUExternalPos->setHidden(hasU);
      ui->labelIfNotHasUExternalPos->setHidden(hasU);
    } else {
      ui->comboBoxIfNotHasUExternalPos->setHidden(true);
      ui->labelIfNotHasUExternalPos->setHidden(true);
    }
  }
}

void CreatorWindow::probePosSet(int index) {
  bool isExternalMachine = (ui->comboBoxMachineType->currentIndex() == 0 ||
                            ui->comboBoxMachineType->currentIndex() == NULL);

  if (isExternalMachine) {
    ui->comboBoxProbePos->setHidden(true);
    ui->labelProbePos->setHidden(true);
  } else {
    bool isOperationMode = (ui->comboBoxIfOperation->currentIndex() == 0 ||
                            ui->comboBoxIfOperation->currentIndex() == NULL);

    ui->comboBoxProbePos->setHidden(!isOperationMode);
    ui->labelProbePos->setHidden(!isOperationMode);
  }
}

//=============================================================================
// ComboBox Change Event Handlers
//=============================================================================

void CreatorWindow::on_comboBoxMachineType_currentIndexChanged(int index) {
  machineTypeComboBoxSet(index);
}

void CreatorWindow::on_comboBoxWareType_currentIndexChanged(int index) {
  wareTypeComboBoxSet(index);
}

void CreatorWindow::on_comboBoxIfOperation_currentIndexChanged(int index) {
  operationComboBoxSet(index);
}

void CreatorWindow::on_comboBoxMeasureMethord_currentIndexChanged(int index) {
  probePosSet(index);
}

void CreatorWindow::on_comboBoxIfCenter_currentIndexChanged(int index) {
  centerSet(index);
}

void CreatorWindow::on_comboBoxIfHasU_currentIndexChanged(int index) {
  centerExternalSet(index);
}

//=============================================================================
// Button Click Handlers
//=============================================================================

int CreatorWindow::on_saveDataPushButton_clicked() {
  QString machineName = ui->lineEditMachineName->text();
  QString machineNameLng = ui->lineEditMachineNameLng->text();
  QString machineIndex = ui->lineEditMachineIndex->text();
  QString customInfo = ui->lineEditCustomInfo->text();
  int languageIndex = ui->comboBoxLng->currentIndex();

  // Validate required fields
  if (machineName.isEmpty() || machineNameLng.isEmpty() ||
      machineIndex.isEmpty() || customInfo.isEmpty()) {
    ui->labelInfo->setText("机床信息设置有误");
    return false;
  }

  QJsonObject config = jsonHandler->readJsonToObj();

  // Save machine info
  config.insert("machineName", machineName);
  config.insert("machineNameLng", machineNameLng);
  config.insert("machineIndex", machineIndex);
  config.insert("customInfo", customInfo);
  config.insert("lng", languageIndex);

  // Save all combo box settings
  config.insert("machineType", ui->comboBoxMachineType->currentIndex());
  config.insert("ifHasScrewTap", ui->comboBoxIfHasScrewTap->currentIndex());
  config.insert("wareType", ui->comboBoxWareType->currentIndex());
  config.insert("ifHasWorm", ui->comboBoxIfHasWorm->currentIndex());
  config.insert("wheelType", ui->comboBoxWheelType->currentIndex());
  config.insert("shapeType", ui->comboBoxShapeType->currentIndex());
  config.insert("ifHasReOp", ui->comboBoxIfHasReOp->currentIndex());
  config.insert("ifOperation", ui->comboBoxIfOperation->currentIndex());
  config.insert("measureMethord", ui->comboBoxMeasureMethord->currentIndex());
  config.insert("probePos", ui->comboBoxProbePos->currentIndex());
  config.insert("ifCenter", ui->comboBoxIfCenter->currentIndex());
  config.insert("ifHasU", ui->comboBoxIfHasU->currentIndex());
  config.insert("ifNotHasUExternalPos",
                ui->comboBoxIfNotHasUExternalPos->currentIndex());
  config.insert("ifHasA", ui->comboBoxIfHasA->currentIndex());
  config.insert("grindWheelType", ui->comboBoxGrindWheelType->currentIndex());
  config.insert("exGrindWheelType",
                ui->comboBoxExGrindWheelType->currentIndex());
  config.insert("dressWheelType", ui->comboBoxDressWheelType->currentIndex());
  config.insert("ifRemoveComments",
                ui->comboBoxIfRemoveComments->currentIndex());
  config.insert("hmiMode", ui->comboBoxHMIMode->currentIndex());
  config.insert("systemMode", ui->comboBoxSystemMode->currentIndex());
  config.insert("ifHasLoadingArm", ui->comboBoxLoadingArm->currentIndex());
  config.insert("ifHasEncryption", ui->comboBoxEncryption->currentIndex());
  config.insert("ifHasNoneTradeMark", ui->comboBoxNoneTradeMark->currentIndex());

  jsonHandler->saveObjToJson(config);

  ui->labelStateBadge->setText("● 配置已保存");
  ui->labelStateBadge->setStyleSheet(
      "color: #10b981; background-color: #064e3b; border: 1px solid #059669; "
      "border-radius: 4px; padding: 3px 8px; font-size: 11px; font-weight: bold;");
  ui->labelStatusTitle->setText("机床配置已保存");
  ui->labelStatusTitle->setStyleSheet("color: #10b981; font-size: 13px; font-weight: bold;");
  ui->labelInfo->setText("当前界面配置参数已成功保存至本地文件");
  ui->labelInfo->setStyleSheet("color: #94a3b8; font-size: 11px; line-height: 140%;");
  return true;
}

void CreatorWindow::on_creatPushButton_clicked() {
  int saveResult = on_saveDataPushButton_clicked();
  if (saveResult == false)
    return;

  QJsonObject config = jsonHandler->readJsonToObj();

  // Check if program directories are configured
  if (!config["programDir"].isNull()) {
    QJsonObject programDir = config["programDir"].toObject();
    bool hasValidDirs = !programDir["sourceDir"].isNull() &&
                        !programDir["destDir"].isNull() &&
                        QDir(programDir["sourceDir"].toString()).exists() &&
                        QDir(programDir["destDir"].toString()).exists();

    if (hasValidDirs) {
      emit triggerProcess();
    } else {
      settingDialog = new Setting;
      settingDialog->show();
    }
  } else {
    settingDialog = new Setting;
    settingDialog->show();
  }
}

//=============================================================================
// Process Status Handlers
//=============================================================================

void CreatorWindow::startingProcess() {
  ui->creatPushButton->setText("正在生成...");
  ui->creatPushButton->setIcon(QIcon());
  ui->creatPushButton->setDisabled(true);
  ui->saveDataPushButton->setDisabled(true);
  ui->backButton->setDisabled(true);
  ui->labelIdleIcon->hide();
  ui->labelProcessing->show();
  ui->labelStatusTitle->setText("正在构建程序");
  ui->labelStatusTitle->setStyleSheet("color: #38bdf8; font-size: 13px; font-weight: bold;");
  ui->labelInfo->show();
  ui->labelInfo->setText("正在校验机床参数并组装代码...\n请稍候");
  ui->labelInfo->setStyleSheet("color: #94a3b8; font-size: 11px; line-height: 140%;");
  ui->labelStateBadge->setText("● 正在生成...");
  ui->labelStateBadge->setStyleSheet(
      "color: #38bdf8; background-color: #0c4a6e; border: 1px solid #0284c7; "
      "border-radius: 4px; padding: 3px 8px; font-size: 11px; font-weight: bold;");
}

void CreatorWindow::finishedProcess() {
  ui->creatPushButton->setText("程序生成");
  ui->creatPushButton->setIcon(QIcon(":/icons/bolt.svg"));
  ui->creatPushButton->setDisabled(false);
  ui->saveDataPushButton->setDisabled(false);
  ui->backButton->setDisabled(false);
  ui->labelProcessing->hide();
  ui->labelIdleIcon->setPixmap(QPixmap(":/icons/check.svg").scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  ui->labelIdleIcon->setStyleSheet(
      "QLabel#labelIdleIcon { background-color: #064e3b; border: 2px solid #059669; "
      "border-radius: 32px; color: #10b981; font-weight: bold; }");
  ui->labelIdleIcon->show();
  ui->labelStatusTitle->setText("加工程序生成成功");
  ui->labelStatusTitle->setStyleSheet("color: #10b981; font-size: 14px; font-weight: bold;");
  ui->labelInfo->show();
  ui->labelInfo->setStyleSheet("color: #94a3b8; font-size: 11px; line-height: 140%;");
  ui->labelInfo->setText("文件已生成完毕\n输出目标目录已自动打开");
  ui->labelStateBadge->setText("● 生成完毕");
  ui->labelStateBadge->setStyleSheet(
      "color: #10b981; background-color: #064e3b; border: 1px solid #059669; "
      "border-radius: 4px; padding: 3px 8px; font-size: 11px; font-weight: bold;");

  // Open destination directory
  QDesktopServices::openUrl(
      QUrl("file:///" + jsonHandler->getDestDir(), QUrl::TolerantMode));
}

void CreatorWindow::on_backButton_clicked() {
  emit triggerBackToMain();
  this->close();
}
