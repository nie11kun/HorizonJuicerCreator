#include "history.hpp"
#include "ui_history.h"

History::History(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
}

History::~History()
{
    delete ui;
}
