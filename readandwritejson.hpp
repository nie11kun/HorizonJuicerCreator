#ifndef READANDWRITEJSON_HPP
#define READANDWRITEJSON_HPP

#include <QString>
#include <QJsonObject>

class ReadAndWriteJson
{
public:
    ReadAndWriteJson(QString f = "./info.json");
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
