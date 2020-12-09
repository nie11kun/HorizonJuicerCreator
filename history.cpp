#include "history.hpp"
#include "ui_history.h"

History::History(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
    setWindowTitle("版本历史");
}

History::~History()
{
    delete ui;
}
