#include "horizonjuicercreator.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HorizonJuicerCreator w;
    w.show();
    return a.exec();
}
