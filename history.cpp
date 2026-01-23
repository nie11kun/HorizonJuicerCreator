/**
 * @file history.cpp
 * @brief Version history dialog widget implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "history.hpp"
#include "ui_history.h"

History::History(QWidget *parent) : QWidget(parent), ui(new Ui::History) {
  ui->setupUi(this);
  setWindowTitle("版本历史");
}

History::~History() { delete ui; }
