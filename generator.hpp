#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <string>
#include "readandwritejson.hpp"
#include "runtime.hpp"

using namespace std;

class Generator
{
public:
    Generator();
    void startGenerate();

private:
    Runtime *runtime;
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

};

#endif // GENERATOR_HPP
