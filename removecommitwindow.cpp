/**
 * @file removecommitwindow.cpp
 * @brief Comment removal window widget implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "removecommitwindow.hpp"
#include "ui_removecommitwindow.h"

#include <QDesktopServices>
#include <QFileDialog>
#include <QMovie>

RemoveCommitWindow::RemoveCommitWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::RemoveCommitWindow) {
  ui->setupUi(this);
  setWindowTitle("删除程序注释");
  setWindowIcon(QIcon(":/icons/broom.svg"));
  ui->pushButtonCancel->setIcon(QIcon(":/icons/arrow-left.svg"));
  ui->pushButtonCancel->setIconSize(QSize(14, 14));
  ui->pushButtonDir->setIcon(QIcon(":/icons/folder.svg"));
  ui->pushButtonDir->setIconSize(QSize(15, 15));
  ui->pushButtonStart->setIcon(QIcon(":/icons/play.svg"));
  ui->pushButtonStart->setIconSize(QSize(15, 15));

  converter = new ConvertCode;
  jsonHandler = new ReadAndWriteJson;
  loadDir();

  // Setup processing animation
  QMovie *processingAnimation = new QMovie(":./processing.gif");
  processingAnimation->setScaledSize(ui->labelProcess->size());
  ui->labelProcess->setMovie(processingAnimation);
  processingAnimation->start();
  ui->labelProcess->hide();

  // Setup worker thread for comment removal
  removeWorker = new RemoveCommit;
  workerThread = new QThread;
  removeWorker->moveToThread(workerThread);
  workerThread->start();

  // Connect signals
  connect(this, SIGNAL(triggerProcess()), removeWorker, SLOT(startProcess()));
  connect(removeWorker, SIGNAL(triggerStartingProcess()), this,
          SLOT(startingProcess()));
  connect(removeWorker, SIGNAL(triggerFinishedProcess()), this,
          SLOT(finishedProcess()));
}

RemoveCommitWindow::~RemoveCommitWindow() {
  delete ui;
  delete jsonHandler;
  delete removeWorker;
  delete converter;
}

void RemoveCommitWindow::loadDir() {
  QJsonObject config = jsonHandler->readJsonToObj();

  if (!config["removeDir"].isNull()) {
    ui->lineEditDir->setText(config["removeDir"].toString());
    ui->lineEditDir->setStyleSheet(
        "QLineEdit { qproperty-cursorPosition: 0; }");
  }
}

void RemoveCommitWindow::on_pushButtonDir_clicked() {
  QString selectedDir =
      QFileDialog::getExistingDirectory(this, "Open the folder");
  if (!selectedDir.isEmpty()) {
    ui->lineEditDir->setText(selectedDir);
  }
}

void RemoveCommitWindow::on_pushButtonStart_clicked() {
  QString targetDir = ui->lineEditDir->text();

  if (!targetDir.isEmpty() && QDir(targetDir).exists()) {
    // Save directory to configuration
    QJsonObject config = jsonHandler->readJsonToObj();
    config.insert("removeDir", targetDir);
    jsonHandler->saveObjToJson(config);

    emit triggerProcess();
  } else {
    ui->labelInfo->setStyleSheet("QLabel { color : #ef4444; font-weight: bold; font-size: 13px; background-color: transparent; }");
    ui->labelInfo->setText("请选择有效的程序文件夹路径！");
  }
}

void RemoveCommitWindow::on_pushButtonCancel_clicked() {
  emit triggerBackToMain();
  this->close();
}

void RemoveCommitWindow::startingProcess() {
  ui->pushButtonStart->setText("正在清理中...");
  ui->pushButtonStart->setIcon(QIcon());
  ui->pushButtonStart->setDisabled(true);
  ui->pushButtonCancel->setDisabled(true);
  ui->labelInfo->hide();
  ui->labelProcess->show();
}

void RemoveCommitWindow::finishedProcess() {
  ui->pushButtonStart->setText("开始清理注释");
  ui->pushButtonStart->setIcon(QIcon(":/icons/play.svg"));
  ui->pushButtonStart->setDisabled(false);
  ui->pushButtonCancel->setDisabled(false);
  ui->labelProcess->hide();
  ui->labelInfo->show();
  ui->labelInfo->setStyleSheet("QLabel { color : #10b981; font-weight: bold; font-size: 14px; background-color: transparent; }");
  ui->labelInfo->setText("注释清理已顺利完成！");
}
