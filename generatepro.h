#ifndef GENERATEPRO_H
#define GENERATEPRO_H

#include <QObject>
#include <string>
#include "readandwritejson.hpp"
#include "convertcode.hpp"
#include "filework.hpp"

using namespace std;

class GeneratePro : public QObject
{
    Q_OBJECT
public:
    explicit GeneratePro(QObject *parent = nullptr);
    ~GeneratePro();

public slots:
    void startGenerate();
    void getJsonValue();
    void test();

private:
    ConvertCode *c;
    ReadAndWriteJson *r;
    FileWork *project;

    string debugDate;
    string specificationInfo;

    string softwareVersion;

    string sourceDir;
    string destDir;

    string machineName;
    string machineNameLng;
    string machineIndex;
    string customInfo;
    int lng;

    int machineType;
    int wareType;
    int ifOperation;
    int ifCenter;
    int ifHasU;
    int ifNotHasUExternalPos;
    int measureMethord;
    int probePos;
    int wheelType;
    int shapeType;
    int ifHasA;
    int grindWheelType;
    int dressWheelType;
    int ifRemoveComments;
    int ifHasReOp;
    int ifHasScrewTap;
    int ifHasWorm;
    int hmiMode;

signals:
    void triggerStartingProcess();
    void triggerFinishedProcess();

};

#endif // GENERATEPRO_H
