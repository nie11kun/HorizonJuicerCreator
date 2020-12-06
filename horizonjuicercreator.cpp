#include "horizonjuicercreator.hpp"
#include "ui_horizonjuicercreator.h"
#include "convertcode.hpp"

HorizonJuicerCreator::HorizonJuicerCreator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HorizonJuicerCreator)
{
    ui->setupUi(this);
    setVersion();
}

HorizonJuicerCreator::~HorizonJuicerCreator()
{
    delete ui;
}

void HorizonJuicerCreator::setVersion() {
    ReadAndWriteJson r;
    QJsonObject obj = r.readJsonToObj();

    if (obj["version"].isNull() || obj["version"].toString() != version) {
        obj.insert("version", version);

        if (!obj["customInfo"].isNull()) {
            ConvertCode c;
            string s = obj["customInfo"].toString().toStdString();
            s = c.UTF8ToGBK(s);
            //s = c.GBKToUTF8(s);
            obj.insert("customInfo", QString::fromStdString(s));
        }
        if (!obj["machineNameLng"].isNull()) {
            ConvertCode c;
            string s = obj["machineNameLng"].toString().toStdString();
            s = c.UTF8ToGBK(s);
            obj.insert("machineNameLng", QString::fromStdString(s));
        }

        r.saveObjToJson(obj);
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
