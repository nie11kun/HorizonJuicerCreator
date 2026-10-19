/**
 * @file horizonjuicercreator.cpp
 * @brief Main application window implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "horizonjuicercreator.hpp"
#include "ui_horizonjuicercreator.h"

#include <QDate>

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

namespace fs = boost::filesystem;

HorizonJuicerCreator::HorizonJuicerCreator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::HorizonJuicerCreator) {
  ui->setupUi(this);
  setWindowTitle("HorizonJuicerCreator");
  jsonHandler = new ReadAndWriteJson;

  const int currentYear = QDate::currentDate().year();
  const QString yearStr = (currentYear > 2018)
                              ? QString("2018-%1").arg(currentYear)
                              : QString::number(currentYear);
  ui->labelFooter->setText(QString(
      "© %1 Nie Kun · HorizonJuicer 数控系统工程套件 · "
      "<a href=\"https://blog.niekun.net/start-page.html\" style=\"color: #38bdf8; text-decoration: none;\">关于我</a>")
      .arg(yearStr));
  ui->labelFooter->setOpenExternalLinks(true);

  setVersion();
  setupMainButtons();
  setWindowIcon(QIcon(":/icons/gear.svg"));
  ui->actionSettings->setIcon(QIcon(":/icons/gear.svg"));
  ui->actionAbout->setIcon(QIcon(":/icons/info.svg"));
  ui->actionHistory->setIcon(QIcon(":/icons/clock.svg"));
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

  ui->labelAppTitle->hide();
  ui->labelAppSubtitle->hide();
  ui->labelFooter->hide();
  ui->creatNewMachineButton->hide();
  ui->passwordCaculateButton->hide();
  ui->removeCommitsButton->hide();
  creatorWindow->show();
  creatorWindow->setMaximumHeight(560);
}

void HorizonJuicerCreator::on_passwordCaculateButton_clicked() {
  passwordCalculatorWindow = new PasswordCalculatorWindow(ui->centralwidget);
  connect(passwordCalculatorWindow, SIGNAL(triggerBackToMain()), this,
          SLOT(showWindow()));

  ui->creatNewMachineButton->hide();
  ui->passwordCaculateButton->hide();
  ui->removeCommitsButton->hide();
  passwordCalculatorWindow->show();
  passwordCalculatorWindow->setMaximumHeight(560);
}

void HorizonJuicerCreator::on_removeCommitsButton_clicked() {
  removeCommitWindow = new RemoveCommitWindow(ui->centralwidget);
  connect(removeCommitWindow, SIGNAL(triggerBackToMain()), this,
          SLOT(showWindow()));

  ui->creatNewMachineButton->hide();
  ui->passwordCaculateButton->hide();
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
  ui->labelAppTitle->show();
  ui->labelAppSubtitle->show();
  ui->labelFooter->show();
  ui->creatNewMachineButton->show();
  ui->passwordCaculateButton->show();
  ui->removeCommitsButton->show();
}

void HorizonJuicerCreator::setupMainButtons() {
  auto setupButton = [](QPushButton *btn, const QString &iconPath,
                        const QString &title, const QString &subtitle) {
    btn->setText(""); // Clear plain text

    QVBoxLayout *layout = new QVBoxLayout(btn);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(8);
    layout->setAlignment(Qt::AlignCenter);

    // Modern vector SVG icon
    QLabel *iconLabel = new QLabel(btn);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    QPixmap iconPix(iconPath);
    iconLabel->setPixmap(iconPix.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setStyleSheet("background: transparent; border: none;");

    QLabel *titleLabel = new QLabel(title, btn);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    titleLabel->setStyleSheet(
        "font-size: 16px; font-weight: bold; color: #f8fafc; "
        "background: transparent; border: none;");

    QLabel *subLabel = new QLabel(subtitle, btn);
    subLabel->setAlignment(Qt::AlignCenter);
    subLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    subLabel->setWordWrap(true);
    subLabel->setStyleSheet(
        "font-size: 12px; color: #94a3b8; font-weight: normal; "
        "background: transparent; border: none;");

    layout->addWidget(iconLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(subLabel);
  };

  setupButton(ui->creatNewMachineButton, ":/icons/gear.svg", "机床配置", "定制机床加工宏程序");
  setupButton(ui->passwordCaculateButton, ":/icons/key.svg", "口令计算", "新老版解锁口令秒算");
  setupButton(ui->removeCommitsButton, ":/icons/broom.svg", "删除注释", "批量清理程序注释");
}
