#include "runtime.hpp"
#include "ui_runtime.h"

Runtime::Runtime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Runtime)
{
    ui->setupUi(this);
}

Runtime::~Runtime()
{
    delete ui;
}
