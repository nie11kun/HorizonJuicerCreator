#include "horizonjuicercreator.hpp"
#include "ui_horizonjuicercreator.h"
#include "convertcode.hpp"

HorizonJuicerCreator::HorizonJuicerCreator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HorizonJuicerCreator)
{
    ui->setupUi(this);
    r = new ReadAndWriteJson;

    setVersion();
}

HorizonJuicerCreator::~HorizonJuicerCreator()
{
    delete ui;
    delete r;
}

void HorizonJuicerCreator::setVersion() {
    QJsonObject obj = r->readJsonToObj();

    qDebug() << obj << Qt::endl;

    if (obj["version"].isNull() || obj["version"].toString() != version) {
        obj.insert("version", version);

        if (!obj["customInfo"].isNull()) {
            QString s = obj["customInfo"].toString();
            obj.insert("customInfo", s);
        }
        if (!obj["machineNameLng"].isNull()) {
            QString s = obj["machineNameLng"].toString();
            obj.insert("machineNameLng", s);
        }
        r->saveObjToJson(obj);
        qDebug() << obj << Qt::endl;
    }
}

void HorizonJuicerCreator::on_creatNewMachineButton_clicked()
{
    creatorWindow = new CreatorWindow();
    creatorWindow->show();
}

void HorizonJuicerCreator::on_removeCommitsButton_clicked()
{
    removeCommitWindow = new RemoveCommitWindow();
    removeCommitWindow->show();
}

void HorizonJuicerCreator::on_actionSettings_triggered()
{
    setting = new Setting();
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
