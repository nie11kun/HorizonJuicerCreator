#include "removecommitwindow.hpp"
#include "ui_removecommitwindow.h"

RemoveCommitWindow::RemoveCommitWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoveCommitWindow)
{
    ui->setupUi(this);
}

RemoveCommitWindow::~RemoveCommitWindow()
{
    delete ui;
}
