#ifndef GENERATEPRO_H
#define GENERATEPRO_H

#include <QObject>
#include <string>
#include "readandwritejson.hpp"

using namespace std;

class GeneratePro : public QObject
{
    Q_OBJECT
public:
    explicit GeneratePro(QObject *parent = nullptr);

public slots:
    void startGenerate();
    void test();

private:
    void getJsonValue();
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
    int measureMethord;
    int wheelType;
    int shapeType;
    int ifHasA;
    int grindWheelType;
    int dressWheelType;
    int ifRemoveComments;
    int roughFeedInput;
    int ifHasReOp;
    int ifHasScrewTap;
    int ifHasWorm;

signals:

};

#endif // GENERATEPRO_H
