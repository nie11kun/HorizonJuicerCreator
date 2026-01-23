/**
 * @file about.cpp
 * @brief About dialog widget implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "about.hpp"
#include "readandwritejson.hpp"
#include "ui_about.h"


About::About(QWidget *parent) : QWidget(parent), ui(new Ui::About) {
  ui->setupUi(this);
  setWindowTitle("关于");
  setVersionInfo();

  // Enable external links in text browser
  ui->textBrowser->setOpenLinks(true);
  ui->textBrowser->setOpenExternalLinks(true);
}

About::~About() { delete ui; }

void About::setVersionInfo() {
  ReadAndWriteJson jsonReader;
  ui->labelVersion->setText(jsonReader.getVersionInfo());
}
