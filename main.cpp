#include "horizonjuicercreator.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HorizonJuicerCreator w;

    QFile file(":./stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    a.setStyleSheet(styleSheet);

    w.show();
    return a.exec();
}
