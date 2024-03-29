#include "horizonjuicercreator.hpp"
#include "ui_horizonjuicercreator.h"
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

HorizonJuicerCreator::HorizonJuicerCreator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HorizonJuicerCreator)
{
    ui->setupUi(this);
    setWindowTitle("HorizonJuicerCreator");
    r = new ReadAndWriteJson;

    setVersion();
}

HorizonJuicerCreator::~HorizonJuicerCreator()
{
    delete ui;
    delete r;
}

void HorizonJuicerCreator::setVersion() {

    fs::path a = r->filePath.toStdString();
    if (!fs::exists(a)) {
        fs::ofstream file(a);
        file.close();
    }

    QJsonObject obj = r->readJsonToObj();

    if (obj["version"].isNull() || obj["version"].toString() != version) {
        obj.insert("version", version);

        r->saveObjToJson(obj);
    }
}

void HorizonJuicerCreator::on_creatNewMachineButton_clicked()
{
    creatorWindow = new CreatorWindow(ui->centralwidget);

    connect(creatorWindow, SIGNAL(triggerBackToMain()), this, SLOT(showWindow()));

    ui->creatNewMachineButton->hide();
    ui->removeCommitsButton->hide();
    creatorWindow->show();

    creatorWindow->setMaximumHeight(560);

}

void HorizonJuicerCreator::on_removeCommitsButton_clicked()
{
    removeCommitWindow = new RemoveCommitWindow(ui->centralwidget);

    connect(removeCommitWindow, SIGNAL(triggerBackToMain()), this, SLOT(showWindow()));

    ui->creatNewMachineButton->hide();
    ui->removeCommitsButton->hide();
    removeCommitWindow->show();

}

void HorizonJuicerCreator::on_actionSettings_triggered()
{
    setting = new Setting();
    setting->setWindowModality(Qt::ApplicationModal);//阻塞程序其他窗口
    setting->show();
}

void HorizonJuicerCreator::on_actionAbout_triggered()
{
    about = new About();
    about->show();
}

void HorizonJuicerCreator::on_actionHistory_triggered()
{
    history = new History();
    history->show();
}

void HorizonJuicerCreator::showWindow() {
    ui->creatNewMachineButton->show();
    ui->removeCommitsButton->show();

    //this->show();
}
