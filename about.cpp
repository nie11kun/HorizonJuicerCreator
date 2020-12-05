#include "about.hpp"
#include "ui_about.h"
#include "readandwritejson.hpp"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setVersionInfo();
}

About::~About()
{
    delete ui;
}

void About::setVersionInfo() {
    ReadAndWriteJson r;
    ui->labelVersion->setText(r.getVersionInfo());
}
