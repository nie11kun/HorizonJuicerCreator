#include "readandwritejson.hpp"
#include <QString>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <string>
#include "convertcode.hpp"

using namespace std;

ReadAndWriteJson::ReadAndWriteJson(QString f)
    :file(f)
{

}

QJsonObject ReadAndWriteJson::readJsonToObj() {
    QFile file(this->file);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open error";
        abort();
    } else {
        QTextStream in(&file);
        QString s = in.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(s.toUtf8());
        QJsonObject obj = doc.object();
        return obj;
    }
}

void ReadAndWriteJson::saveObjToJson(QJsonObject obj) {

    QJsonDocument jsonDoc;
    jsonDoc.setObject(obj);


    QFile file(this->file);
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

    if (obj1["version"].isNull())
        obj1.insert("version", "0.0.0");

    if (!obj1["customInfo"].isNull()) {
        ConvertCode c;
        string s = obj1["customInfo"].toString().toStdString();
        s = c.UTF8ToGBK(s);
        //s = c.GBKToUTF8(s);
        obj1.insert("customInfo", QString::fromStdString(s));
    }
    if (!obj1["machineNameLng"].isNull()) {
        ConvertCode c;
        string s = obj1["machineNameLng"].toString().toStdString();
        s = c.UTF8ToGBK(s);
        obj1.insert("machineNameLng", QString::fromStdString(s));
    }

    saveObjToJson(obj1);

}

QString ReadAndWriteJson::getVersionInfo() {
    QJsonObject obj1 = this->readJsonToObj();
    return obj1["version"].toString();
}
