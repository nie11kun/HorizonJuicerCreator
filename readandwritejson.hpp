#ifndef READANDWRITEJSON_HPP
#define READANDWRITEJSON_HPP

#include <QString>
#include <QJsonObject>
#include <QDir>

class ReadAndWriteJson
{
public:
    ReadAndWriteJson();
#ifdef _WIN32
    QString file = QDir::homePath() + "/HorizonJuicerCreator.json";
#else
    QString file = "/Users/marconie/libs/HorizonJuicerCreator.json";
#endif
    QJsonObject readJsonToObj();
    void saveObjToJson(QJsonObject obj);
    QString getSourceDir();
    QString getDestDir();
    QString getVersionInfo();
    void setDirs(QString a, QString b);

private:

};

#endif // READANDWRITEJSON_HPP
