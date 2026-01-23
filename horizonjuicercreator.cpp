/**
 * @file horizonjuicercreator.cpp
 * @brief Main application window implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "horizonjuicercreator.hpp"
#include "ui_horizonjuicercreator.h"

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

namespace fs = boost::filesystem;

HorizonJuicerCreator::HorizonJuicerCreator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::HorizonJuicerCreator) {
  ui->setupUi(this);
  setWindowTitle("HorizonJuicerCreator");
  jsonHandler = new ReadAndWriteJson;

  setVersion();
}

HorizonJuicerCreator::~HorizonJuicerCreator() {
  delete ui;
  delete jsonHandler;
}

void HorizonJuicerCreator::setVersion() {
  // Create configuration file if it doesn't exist
  fs::path configPath = jsonHandler->filePath.toStdString();
  if (!fs::exists(configPath)) {
    fs::ofstream file(configPath);
    file.close();
  }

  // Update version in configuration if needed
  QJsonObject config = jsonHandler->readJsonToObj();
  if (config["version"].isNull() || config["version"].toString() != version) {
    config.insert("version", version);
    jsonHandler->saveObjToJson(config);
  }
}

void HorizonJuicerCreator::on_creatNewMachineButton_clicked() {
  creatorWindow = new CreatorWindow(ui->centralwidget);
  connect(creatorWindow, SIGNAL(triggerBackToMain()), this, SLOT(showWindow()));

  ui->creatNewMachineButton->hide();
  ui->removeCommitsButton->hide();
  creatorWindow->show();
  creatorWindow->setMaximumHeight(560);
}

void HorizonJuicerCreator::on_removeCommitsButton_clicked() {
  removeCommitWindow = new RemoveCommitWindow(ui->centralwidget);
  connect(removeCommitWindow, SIGNAL(triggerBackToMain()), this,
          SLOT(showWindow()));

  ui->creatNewMachineButton->hide();
  ui->removeCommitsButton->hide();
  removeCommitWindow->show();
}

void HorizonJuicerCreator::on_actionSettings_triggered() {
  settingDialog = new Setting();
  settingDialog->setWindowModality(Qt::ApplicationModal); // Block other windows
  settingDialog->show();
}

void HorizonJuicerCreator::on_actionAbout_triggered() {
  aboutDialog = new About();
  aboutDialog->show();
}

void HorizonJuicerCreator::on_actionHistory_triggered() {
  historyDialog = new History();
  historyDialog->show();
}

void HorizonJuicerCreator::showWindow() {
  ui->creatNewMachineButton->show();
  ui->removeCommitsButton->show();
}
