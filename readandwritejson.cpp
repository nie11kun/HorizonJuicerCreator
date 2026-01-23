/**
 * @file readandwritejson.cpp
 * @brief JSON configuration read/write utilities implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "readandwritejson.hpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QTextStream>

#include <string>

ReadAndWriteJson::ReadAndWriteJson() {
  converter = new ConvertCode;
  filePath = QDir::homePath() + pathSeparator + fileName;
}

ReadAndWriteJson::~ReadAndWriteJson() { delete converter; }

QJsonObject ReadAndWriteJson::readJsonToObj() {
  QFile file(this->filePath);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "File open error";
    abort();
  }

  QTextStream inputStream(&file);
  QString content = inputStream.readAll();
  file.close();

  QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
  QJsonObject obj = doc.object();

  qDebug() << "***************read json************\n"
           << obj << "\n**********************************\n";

  return obj;
}

void ReadAndWriteJson::saveObjToJson(QJsonObject obj) {
  qDebug() << "***************write json***********\n"
           << obj << "\n**********************************\n";

  QJsonDocument jsonDoc;
  jsonDoc.setObject(obj);

  QFile file(this->filePath);
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "File open error";
    abort();
  }

  file.resize(0); // Clear file contents
  file.write(jsonDoc.toJson());
  file.close();
}

QString ReadAndWriteJson::getSourceDir() {
  QJsonObject config = this->readJsonToObj();
  QJsonValue programDir = config["programDir"];
  QJsonObject dirObj = programDir.toObject();
  return dirObj["sourceDir"].toString();
}

QString ReadAndWriteJson::getDestDir() {
  QJsonObject config = this->readJsonToObj();
  QJsonValue programDir = config["programDir"];
  QJsonObject dirObj = programDir.toObject();
  return dirObj["destDir"].toString();
}

void ReadAndWriteJson::setDirs(QString sourceDir, QString destDir) {
  QJsonObject config = this->readJsonToObj();

  QJsonObject dirObj;
  dirObj.insert("sourceDir", sourceDir);
  dirObj.insert("destDir", destDir);
  config.insert("programDir", dirObj);

  // Preserve existing string values
  if (!config["customInfo"].isNull()) {
    QString customInfo = config["customInfo"].toString();
    config.insert("customInfo", customInfo);
  }
  if (!config["machineNameLng"].isNull()) {
    QString machineNameLng = config["machineNameLng"].toString();
    config.insert("machineNameLng", machineNameLng);
  }

  saveObjToJson(config);
}

QString ReadAndWriteJson::getVersionInfo() {
  QJsonObject config = this->readJsonToObj();
  return config["version"].toString();
}

QString ReadAndWriteJson::getRemoveDir() {
  QJsonObject config = this->readJsonToObj();
  return config["removeDir"].toString();
}
