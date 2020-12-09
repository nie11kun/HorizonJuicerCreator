#include "setting.hpp"
#include "ui_setting.h"
#include <QFileDialog>

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    setWindowTitle("设置");
    r = new ReadAndWriteJson;

    loadDir();
}

Setting::~Setting()
{
    delete ui;
    delete r;
}

void Setting::on_abortButton_clicked()
{
    QWidget::close();
}

void Setting::loadDir() {
    ui->lineEditSource->setText(r->getSourceDir());
    ui->lineEditDest->setText(r->getDestDir());
    ui->lineEditSource->setStyleSheet("QLineEdit { qproperty-cursorPosition: 0; }");
    ui->lineEditDest->setStyleSheet("QLineEdit { qproperty-cursorPosition: 0; }");
}

void Setting::on_saveButton_clicked()
{
    QString sourceStr = ui->lineEditSource->text();
    QString destStr = ui->lineEditDest->text();
    if ((sourceStr != "") && (destStr != "") && (QDir(sourceStr).exists()) && (QDir(destStr).exists())) {

        r->setDirs(sourceStr, destStr);

        QWidget::close();
    } else {
        ui->labelError->setText("请设置正确路径！");
    }
}

void Setting::on_sourceButton_clicked()
{
    QString sourceDir = QFileDialog::getExistingDirectory(this, "Open the folder");
    if (!sourceDir.isEmpty())
        ui->lineEditSource->setText(sourceDir);
}

void Setting::on_destButton_clicked()
{
    QString destDir = QFileDialog::getExistingDirectory(this, "Open the folder");
    if (!destDir.isEmpty())
        ui->lineEditDest->setText(destDir);
}
