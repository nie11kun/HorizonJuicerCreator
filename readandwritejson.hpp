#ifndef READANDWRITEJSON_HPP
#define READANDWRITEJSON_HPP

#include <QString>
#include <QJsonObject>
#include <QDir>

class ReadAndWriteJson
{
public:
#ifdef _WIN32
    ReadAndWriteJson(QString f = QDir::homePath() + "/HorizonJuicerCreator.json");
#else
    ReadAndWriteJson(QString f = "/Users/marconie/libs/HorizonJuicerCreator.json");
#endif
    QString file;
    QJsonObject readJsonToObj();
    void saveObjToJson(QJsonObject obj);
    QString getSourceDir();
    QString getDestDir();
    QString getVersionInfo();
    void setDirs(QString a, QString b);

private:

};

#endif // READANDWRITEJSON_HPP
