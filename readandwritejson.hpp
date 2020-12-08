#ifndef READANDWRITEJSON_HPP
#define READANDWRITEJSON_HPP

#include <QString>
#include <QJsonObject>
#include <QDir>
#include "convertcode.hpp"

class ReadAndWriteJson
{
public:
    ReadAndWriteJson();
    ~ReadAndWriteJson();
    QString filePath;
    QJsonObject readJsonToObj();
    void saveObjToJson(QJsonObject obj);
    QString getSourceDir();
    QString getDestDir();
    QString getVersionInfo();
    void setDirs(QString a, QString b);

private:
    ConvertCode *c;
    QString fileName = "HorizonJuicerCreator.json";
    #ifdef _WIN32
    QString seg = "\\";
    #else
    QString seg = "/";
    #endif

};

#endif // READANDWRITEJSON_HPP
