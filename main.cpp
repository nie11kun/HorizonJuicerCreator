#include "horizonjuicercreator.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HorizonJuicerCreator w;

    QFile file(":qdarkstyle/dark/style.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&file);
    a.setStyleSheet(ts.readAll());

    w.show();
    return a.exec();
}
