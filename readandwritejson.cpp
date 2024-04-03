#include "readandwritejson.hpp"
#include <QString>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <string>

using namespace std;

ReadAndWriteJson::ReadAndWriteJson()
{
    c = new ConvertCode;
    filePath = QDir::homePath() + seg + fileName;
}

ReadAndWriteJson::~ReadAndWriteJson()
{
    delete c;
}

QJsonObject ReadAndWriteJson::readJsonToObj() {
    QFile file(this->filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open error";
        abort();
    } else {
        QTextStream in(&file);
        in.setCodec("utf8");// if not set code to utf8, chinese will error when is odd number.
        QString s = in.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(s.toUtf8());
        QJsonObject obj = doc.object();
        qDebug() << "***************read json************\n"
                 << obj <<
                    "\n**********************************\n";
        return obj;
    }
}

void ReadAndWriteJson::saveObjToJson(QJsonObject obj) {

    qDebug() << "***************write json***********\n"
             << obj <<
                "\n**********************************\n";
    QJsonDocument jsonDoc;
    jsonDoc.setObject(obj);
    QFile file(this->filePath);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "File open error";
        abort();
    } else {
        file.resize(0);
        file.write(jsonDoc.toJson());
        file.close();
    }
}

QString ReadAndWriteJson::getSourceDir() {
    QJsonObject obj1 = this->readJsonToObj();
    QJsonValue prog = obj1["programDir"];
    QJsonObject obj2 = prog.toObject();
    QString s = obj2["sourceDir"].toString();
    return s;
}

QString ReadAndWriteJson::getDestDir() {
    QJsonObject obj1 = this->readJsonToObj();
    QJsonValue prog = obj1["programDir"];
    QJsonObject obj2 = prog.toObject();
    QString s = obj2["destDir"].toString();
    return s;
}

void ReadAndWriteJson::setDirs(QString a, QString b) {
    QJsonObject obj1 = this->readJsonToObj();

    QJsonObject obj2;
    obj2.insert("sourceDir", a);
    obj2.insert("destDir", b);

    obj1.insert("programDir", obj2);

    if (!obj1["customInfo"].isNull()) {
        QString s = obj1["customInfo"].toString();
        obj1.insert("customInfo", s);
    }
    if (!obj1["machineNameLng"].isNull()) {
        QString s = obj1["machineNameLng"].toString();
        obj1.insert("machineNameLng", s);
    }

    saveObjToJson(obj1);
}

QString ReadAndWriteJson::getVersionInfo() {
    QJsonObject obj1 = this->readJsonToObj();
    return obj1["version"].toString();
}

QString ReadAndWriteJson::getRemoveDir() {
    QJsonObject obj = this->readJsonToObj();
    return obj["removeDir"].toString();
}
