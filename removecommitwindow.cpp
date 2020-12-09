#include "removecommitwindow.hpp"
#include "ui_removecommitwindow.h"
#include "QFileDialog"
#include <QMovie>
#include <QDesktopServices>

RemoveCommitWindow::RemoveCommitWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoveCommitWindow)
{
    ui->setupUi(this);
    setWindowTitle("删除程序注释");

    c = new ConvertCode;
    r = new ReadAndWriteJson;
    loadDir();

    QMovie *movie = new QMovie(":./processing.gif");
    movie->setScaledSize(ui->labelProcess->size());
    ui->labelProcess->setMovie(movie);
    movie->start();
    ui->labelProcess->hide();

    remove = new RemoveCommit;
    t = new QThread;
    remove->moveToThread(t);
    t->start();

    connect(this, SIGNAL(triggerProcess()), remove, SLOT(startProcess()));
    connect(remove, SIGNAL(triggerStartingProcess()), this, SLOT(startingProcess()));
    connect(remove, SIGNAL(triggerFinishedProcess()), this, SLOT(finishedProcess()));
}

RemoveCommitWindow::~RemoveCommitWindow()
{
    delete ui;
    delete r;
    delete remove;
    delete t;
    delete c;
}

void RemoveCommitWindow::loadDir() {
    QJsonObject obj = r->readJsonToObj();

    if (!obj["removeDir"].isNull()) {
        ui->lineEditDir->setText(obj["removeDir"].toString());
        ui->lineEditDir->setStyleSheet("QLineEdit { qproperty-cursorPosition: 0; }");
    }
}

void RemoveCommitWindow::on_pushButtonDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Open the folder");
    if (!dir.isEmpty())
        ui->lineEditDir->setText(dir);
}

void RemoveCommitWindow::on_pushButtonStart_clicked()
{
    QString dir = ui->lineEditDir->text();
    if ((dir != "") && (QDir(dir).exists())) {
        QJsonObject obj = r->readJsonToObj();
        obj.insert("removeDir", dir);
        r->saveObjToJson(obj);

        emit triggerProcess();

    } else {
        ui->labelInfo->setText("请设置正确路径！");
    }
}

void RemoveCommitWindow::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

void RemoveCommitWindow::startingProcess() {
    ui->pushButtonStart->setText("正在处理");
    ui->pushButtonStart->setDisabled(true);
    ui->pushButtonCancel->setDisabled(true);
    ui->labelInfo->hide();
    ui->labelProcess->show();
}

void RemoveCommitWindow::finishedProcess() {
    ui->pushButtonStart->setText("开始");
    ui->pushButtonStart->setDisabled(false);
    ui->pushButtonCancel->setDisabled(false);
    ui->labelProcess->hide();
    ui->labelInfo->show();
    ui->labelInfo->setStyleSheet("QLabel { color : red; }");
    ui->labelInfo->setText("注释删除完成");

    // QDesktopServices::openUrl(QUrl("file:///" + r->getRemoveDir()));
}
