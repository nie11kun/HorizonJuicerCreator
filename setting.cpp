/**
 * @file setting.cpp
 * @brief Settings dialog widget implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "setting.hpp"
#include "ui_setting.h"

#include <QFileDialog>

Setting::Setting(QWidget *parent) : QWidget(parent), ui(new Ui::Setting) {
  ui->setupUi(this);
  setWindowTitle("设置");
  jsonHandler = new ReadAndWriteJson;

  loadDir();
}

Setting::~Setting() {
  delete ui;
  delete jsonHandler;
}

void Setting::on_abortButton_clicked() { QWidget::close(); }

void Setting::loadDir() {
  ui->lineEditSource->setText(jsonHandler->getSourceDir());
  ui->lineEditDest->setText(jsonHandler->getDestDir());

  // Set cursor position to start for long paths
  ui->lineEditSource->setStyleSheet(
      "QLineEdit { qproperty-cursorPosition: 0; }");
  ui->lineEditDest->setStyleSheet("QLineEdit { qproperty-cursorPosition: 0; }");
}

void Setting::on_saveButton_clicked() {
  QString sourceStr = ui->lineEditSource->text();
  QString destStr = ui->lineEditDest->text();

  // Validate both paths exist
  if (!sourceStr.isEmpty() && !destStr.isEmpty() && QDir(sourceStr).exists() &&
      QDir(destStr).exists()) {
    jsonHandler->setDirs(sourceStr, destStr);
    QWidget::close();
  } else {
    ui->labelError->setText("请设置正确路径！");
  }
}

void Setting::on_sourceButton_clicked() {
  QString selectedDir =
      QFileDialog::getExistingDirectory(this, "Open the folder");
  if (!selectedDir.isEmpty()) {
    ui->lineEditSource->setText(selectedDir);
  }
}

void Setting::on_destButton_clicked() {
  QString selectedDir =
      QFileDialog::getExistingDirectory(this, "Open the folder");
  if (!selectedDir.isEmpty()) {
    ui->lineEditDest->setText(selectedDir);
  }
}
