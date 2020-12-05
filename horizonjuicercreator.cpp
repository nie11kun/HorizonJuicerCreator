#include "horizonjuicercreator.hpp"
#include "ui_horizonjuicercreator.h"

HorizonJuicerCreator::HorizonJuicerCreator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HorizonJuicerCreator)
{
    ui->setupUi(this);
}

HorizonJuicerCreator::~HorizonJuicerCreator()
{
    delete ui;
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
