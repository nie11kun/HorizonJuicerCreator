#include "generatepro.h"
#include <iostream>
#include "convertcode.hpp"
#include "filework.hpp"
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

#ifdef _WIN32
    string seg = "\\";
#else
    string seg = "/";
#endif

const char* isComments =
"(;[^\n\*]+)";

const char* commentsInFiles[] = {
    "com$",
    "spf$",
    "mpf$",
    "COM$",
    "SPF$",
    "MPF$"
};
//*****************************************
const char* ifIsKaiGuanCeLiang =
"(;ifIsKaiGuanCeLiangBegin.*?;ifIsKaiGuanCeLiangEnd)|"
"(\<!--ifIsKaiGuanCeLiangBegin--\>.*?\<!--ifIsKaiGuanCeLiangEnd--\>)|"
"([^\n]+ifIsKaiGuanCeLiang\\b)|"
"([^\n]+\<!--ifIsKaiGuanCeLiangLine--\>)"
;
const char* ifIsCeTouCeLiang =
"(;ifIsCeTouCeLiangBegin.*?;ifIsCeTouCeLiangEnd)|"
"(\<!--ifIsCeTouCeLiangBegin--\>.*?\<!--ifIsCeTouCeLiangEnd--\>)|"
"([^\n]+ifIsCeTouCeLiang\\b)|"
"([^\n]+\<!--ifIsCeTouCeLiangLine--\>)"
;
const char* ifIsKaiGuanAndCeTouCeLiang =
"(;ifIsKaiGuanAndCeTouCeLiangBegin.*?;ifIsKaiGuanAndCeTouCeLiangEnd)|"
"(\<!--ifIsKaiGuanAndCeTouCeLiangBegin--\>.*?\<!--ifIsKaiGuanAndCeTouCeLiangEnd--\>)|"
"([^\n]+ifIsKaiGuanAndCeTouCeLiang\\b)|"
"([^\n]+\<!--ifIsKaiGuanAndCeTouCeLiangLine--\>)"
;
const char* ifIsNotCenter =
"(;ifIsNotCenterBegin.*?;ifIsNotCenterEnd)|"
"(\<!--ifIsNotCenterBegin--\>.*?\<!--ifIsNotCenterEnd--\>)|"
"([^\n]+ifIsNotCenter\\b)|"
"([^\n]+\<!--ifIsNotCenterLine--\>)"
;
const char* ifIsCenter =
"(;ifIsCenterBegin.*?;ifIsCenterEnd)|"
"(\<!--ifIsCenterBegin--\>.*?\<!--ifIsCenterEnd--\>)|"
"([^\n]+ifIsCenter\\b)|"
"([^\n]+\<!--ifIsCenterLine--\>)"
;
const char* ifIsAuto =
"(;ifIsAutoBegin.*?;ifIsAutoEnd)|"
"(\<!--ifIsAutoBegin--\>.*?\<!--ifIsAutoEnd--\>)|"
"([^\n]+ifIsAuto\\b)|"
"([^\n]+\<!--ifIsAutoLine--\>)"
;
const char* ifIsExternal =
"(;ifIsExternalBegin.*?;ifIsExternalEnd)|"
"(\<!--ifIsExternalBegin--\>.*?\<!--ifIsExternalEnd--\>)|"
"([^\n]+ifIsExternal\\b)|"
"([^\n]+\<!--ifIsExternalLine--\>)"
;
const char* ifIsExternalVW =
"(;ifIsExternalVWBegin.*?;ifIsExternalVWEnd)|"
"(\<!--ifIsExternalVWBegin--\>.*?\<!--ifIsExternalVWEnd--\>)|"
"([^\n]+ifIsExternalVW\\b)|"
"([^\n]+\<!--ifIsExternalVWLine--\>)"
;
const char* ifIsScrewTap =
"(;ifIsScrewTapBegin.*?;ifIsScrewTapEnd)|"
"(\<!--ifIsScrewTapBegin--\>.*?\<!--ifIsScrewTapEnd--\>)|"
"([^\n]+ifIsScrewTap\\b)|"
"([^\n]+\<!--ifIsScrewTapLine--\>)"
;
const char* ifIsNotScrewTap =
"(;ifIsNotScrewTapBegin.*?;ifIsNotScrewTapEnd)|"
"(\<!--ifIsNotScrewTapBegin--\>.*?\<!--ifIsNotScrewTapEnd--\>)|"
"([^\n]+ifIsNotScrewTap\\b)|"
"([^\n]+\<!--ifIsNotScrewTapLine--\>)"
;
const char* ifIsInternal =
"(;ifIsInternalBegin.*?;ifIsInternalEnd)|"
"(\<!--ifIsInternalBegin--\>.*?\<!--ifIsInternalEnd--\>)|"
"([^\n]+ifIsInternal\\b)|"
"([^\n]+\<!--ifIsInternalLine--\>)"
;
const char* ifIsInternalOnly =
"(;ifIsInternalOnlyBegin.*?;ifIsInternalOnlyEnd)|"
"(\<!--ifIsInternalOnlyBegin--\>.*?\<!--ifIsInternalOnlyEnd--\>)|"
"([^\n]+ifIsInternalOnly\\b)|"
"([^\n]+\<!--ifIsInternalOnlyLine--\>)"
;
const char* ifIsDressWare1 =
"(;ifIsDressWare1Begin.*?;ifIsDressWare1End)|"
"(\<!--ifIsDressWare1Begin--\>.*?\<!--ifIsDressWare1End--\>)|"
"([^\n]+ifIsDressWare1\\b)|"
"([^\n]+\<!--ifIsDressWare1Line--\>)"
;
const char* ifIsDressWare2 =
"(;ifIsDressWare2Begin.*?;ifIsDressWare2End)|"
"(\<!--ifIsDressWare2Begin--\>.*?\<!--ifIsDressWare2End--\>)|"
"([^\n]+ifIsDressWare2\\b)|"
"([^\n]+\<!--ifIsDressWare2Line--\>)"
;
const char* ifIsDressWare3 =
"(;ifIsDressWare3Begin.*?;ifIsDressWare3End)|"
"(\<!--ifIsDressWare3Begin--\>.*?\<!--ifIsDressWare3End--\>)|"
"([^\n]+ifIsDressWare3\\b)|"
"([^\n]+\<!--ifIsDressWare3Line--\>)"
;
const char* ifIsDressWare4 =
"(;ifIsDressWare4Begin.*?;ifIsDressWare4End)|"
"(\<!--ifIsDressWare4Begin--\>.*?\<!--ifIsDressWare4End--\>)|"
"([^\n]+ifIsDressWare4\\b)|"
"([^\n]+\<!--ifIsDressWare4Line--\>)"
;
const char* ifIsDressWare5 =
"(;ifIsDressWare5Begin.*?;ifIsDressWare5End)|"
"(\<!--ifIsDressWare5Begin--\>.*?\<!--ifIsDressWare5End--\>)|"
"([^\n]+ifIsDressWare5\\b)|"
"([^\n]+\<!--ifIsDressWare5Line--\>)"
;
const char* ifIsSingleAndRound =
"(;ifIsSingleAndRoundBegin.*?;ifIsSingleAndRoundEnd)|"
"(\<!--ifIsSingleAndRoundBegin--\>.*?\<!--ifIsSingleAndRoundEnd--\>)|"
"([^\n]+ifIsSingleAndRound\\b)|"
"([^\n]+\<!--ifIsSingleAndRoundLine--\>)"
;
const char* ifIsSide =
"(;ifIsSideBegin.*?;ifIsSideEnd)|"
"(\<!--ifIsSideBegin--\>.*?\<!--ifIsSideEnd--\>)|"
"([^\n]+ifIsSide\\b)|"
"([^\n]+\<!--ifIsSideLine--\>)"
;
const char* ifIsAllShape =
"(;ifIsAllShapeBegin.*?;ifIsAllShapeEnd)|"
"(\<!--ifIsAllShapeBegin--\>.*?\<!--ifIsAllShapeEnd--\>)|"
"([^\n]+ifIsAllShape\\b)|"
"([^\n]+\<!--ifIsAllShapeLine--\>)"
;
const char* ifIsArc =
"(;ifIsArcBegin.*?;ifIsArcEnd)|"
"(\<!--ifIsArcBegin--\>.*?\<!--ifIsArcEnd--\>)|"
"([^\n]+ifIsArc\\b)|"
"([^\n]+\<!--ifIsArcLine--\>)"
;
const char* ifIsOnlyArc =
"(;ifIsOnlyArcBegin.*?;ifIsOnlyArcEnd)|"
"(\<!--ifIsOnlyArcBegin--\>.*?\<!--ifIsOnlyArcEnd--\>)|"
"([^\n]+ifIsOnlyArc\\b)|"
"([^\n]+\<!--ifIsOnlyArcLine--\>)"
;
const char* ifIsFrontDress =
"(;ifIsFrontDressBegin.*?;ifIsFrontDressEnd)|"
"(\<!--ifIsFrontDressBegin--\>.*?\<!--ifIsFrontDressEnd--\>)|"
"([^\n]+ifIsFrontDress\\b)|"
"([^\n]+\<!--ifIsFrontDressLine--\>)"
;
const char* ifIsBackDress =
"(;ifIsBackDressBegin.*?;ifIsBackDressEnd)|"
"(\<!--ifIsBackDressBegin--\>.*?\<!--ifIsBackDressEnd--\>)|"
"([^\n]+ifIsBackDress\\b)|"
"([^\n]+\<!--ifIsBackDressLine--\>)"
;
const char* ifIsVW =
"(;ifIsVWBegin.*?;ifIsVWEnd)|"
"(\<!--ifIsVWBegin--\>.*?\<!--ifIsVWEnd--\>)|"
"([^\n]+ifIsVW\\b)|"
"([^\n]+\<!--ifIsVWLine--\>)"
;
const char* ifIsVWSR =
"(;ifIsVWSRBegin.*?;ifIsVWSREnd)|"
"(\<!--ifIsVWSRBegin--\>.*?\<!--ifIsVWSREnd--\>)|"
"([^\n]+ifIsVWSR\\b)|"
"([^\n]+\<!--ifIsVWSRLine--\>)"
;
const char* ifIsVWSide =
"(;ifIsVWSideBegin.*?;ifIsVWSideEnd)|"
"(\<!--ifIsVWSideBegin--\>.*?\<!--ifIsVWSideEnd--\>)|"
"([^\n]+ifIsVWSide\\b)|"
"([^\n]+\<!--ifIsVWSideLine--\>)"
;
const char* ifIsV =
"(;ifIsVBegin.*?;ifIsVEnd)|"
"(\<!--ifIsVBegin--\>.*?\<!--ifIsVEnd--\>)|"
"([^\n]+ifIsV\\b)|"
"([^\n]+\<!--ifIsVLine--\>)"
;
const char* ifIsXZSR =
"(;ifIsXZSRBegin.*?;ifIsXZSREnd)|"
"(\<!--ifIsXZSRBegin--\>.*?\<!--ifIsXZSREnd--\>)|"
"([^\n]+ifIsXZSR\\b)|"
"([^\n]+\<!--ifIsXZSRLine--\>)"
;
const char* ifIsXZSide =
"(;ifIsXZSideBegin.*?;ifIsXZSideEnd)|"
"(\<!--ifIsXZSideBegin--\>.*?\<!--ifIsXZSideEnd--\>)|"
"([^\n]+ifIsXZSide\\b)|"
"([^\n]+\<!--ifIsXZSideLine--\>)"
;
const char* ifIsXWai =
"(;ifIsXWaiBegin.*?;ifIsXWaiEnd)|"
"(\<!--ifIsXWaiBegin--\>.*?\<!--ifIsXWaiEnd--\>)|"
"([^\n]+ifIsXWai\\b)|"
"([^\n]+\<!--ifIsXWaiLine--\>)"
;
const char* ifIsXNeiFront =
"(;ifIsXNeiFrontBegin.*?;ifIsXNeiFrontEnd)|"
"(\<!--ifIsXNeiFrontBegin--\>.*?\<!--ifIsXNeiFrontEnd--\>)|"
"([^\n]+ifIsXNeiFront\\b)|"
"([^\n]+\<!--ifIsXNeiFrontLine--\>)"
;
const char* ifIsXNeiBack =
"(;ifIsXNeiBackBegin.*?;ifIsXNeiBackEnd)|"
"(\<!--ifIsXNeiBackBegin--\>.*?\<!--ifIsXNeiBackEnd--\>)|"
"([^\n]+ifIsXNeiBack\\b)|"
"([^\n]+\<!--ifIsXNeiBackLine--\>)"
;
const char* ifIsVH =
"(;ifIsVHBegin.*?;ifIsVHEnd)|"
"(\<!--ifIsVHBegin--\>.*?\<!--ifIsVHEnd--\>)|"
"([^\n]+ifIsVH\\b)|"
"([^\n]+\<!--ifIsVHLine--\>)"
;
const char* ifIsHasWorm =
"(;ifIsHasWormBegin.*?;ifIsHasWormEnd)|"
"(\<!--ifIsHasWormBegin--\>.*?\<!--ifIsHasWormEnd--\>)|"
"([^\n]+ifIsHasWorm\\b)|"
"([^\n]+\<!--ifIsHasWormLine--\>)"
;
const char* ifIsNotHasWorm =
"(;ifIsNotHasWormBegin.*?;ifIsNotHasWormEnd)|"
"(\<!--ifIsNotHasWormBegin--\>.*?\<!--ifIsNotHasWormEnd--\>)|"
"([^\n]+ifIsNotHasWorm\\b)|"
"([^\n]+\<!--ifIsNotHasWormLine--\>)"
;
const char* ifIsHasU =
"(;ifIsHasUBegin.*?;ifIsHasUEnd)|"
"(\<!--ifIsHasUBegin--\>.*?\<!--ifIsHasUEnd--\>)|"
"([^\n]+ifIsHasU\\b)|"
"([^\n]+\<!--ifIsHasULine--\>)"
;
const char* ifIsNotHasU =
"(;ifIsNotHasUBegin.*?;ifIsNotHasUEnd)|"
"(\<!--ifIsNotHasUBegin--\>.*?\<!--ifIsNotHasUEnd--\>)|"
"([^\n]+ifIsNotHasU\\b)|"
"([^\n]+\<!--ifIsNotHasULine--\>)"
;
const char* ifIsRoughToAmount =
"(;ifIsRoughToAmountBegin.*?;ifIsRoughToAmountEnd)|"
"(\<!--ifIsRoughToAmountBegin--\>.*?\<!--ifIsRoughToAmountEnd--\>)|"
"([^\n]+ifIsRoughToAmount\\b)|"
"([^\n]+\<!--ifIsRoughToAmountLine--\>)"
;
const char* ifIsNotRoughToAmount =
"(;ifIsNotRoughToAmountBegin.*?;ifIsNotRoughToAmountEnd)|"
"(\<!--ifIsNotRoughToAmountBegin--\>.*?\<!--ifIsNotRoughToAmountEnd--\>)|"
"([^\n]+ifIsNotRoughToAmount\\b)|"
"([^\n]+\<!--ifIsNotRoughToAmountLine--\>)"
;
const char* ifIsHasReOperate =
"(;ifIsHasReOperateBegin.*?;ifIsHasReOperateEnd)|"
"(\<!--ifIsHasReOperateBegin--\>.*?\<!--ifIsHasReOperateEnd--\>)|"
"([^\n]+ifIsHasReOperate\\b)|"
"([^\n]+\<!--ifIsHasReOperateLine--\>)"
;
const char* ifIsNotHasReOperate =
"(;ifIsNotHasReOperateBegin.*?;ifIsNotHasReOperateEnd)|"
"(\<!--ifIsNotHasReOperateBegin--\>.*?\<!--ifIsNotHasReOperateEnd--\>)|"
"([^\n]+ifIsNotHasReOperate\\b)|"
"([^\n]+\<!--ifIsNotHasReOperateLine--\>)"
;
const char* ifIsCHS =
"(;ifIsCHSBegin.*?;ifIsCHSEnd)|"
"(\<!--ifIsCHSBegin--\>.*?\<!--ifIsCHSEnd--\>)|"
"([^\n]+ifIsCHS\\b)|"
"([^\n]+\<!--ifIsCHSLine--\>)"
;
const char* ifIsENG =
"(;ifIsENGBegin.*?;ifIsENGEnd)|"
"(\<!--ifIsENGBegin--\>.*?\<!--ifIsENGEnd--\>)|"
"([^\n]+ifIsENG\\b)|"
"([^\n]+\<!--ifIsENGLine--\>)"
;
const char* ifIsHasOtherCommonShape =
"(;ifIsHasOtherCommonShapeBegin.*?;ifIsHasOtherCommonShapeEnd)|"
"(\<!--ifIsHasOtherCommonShapeBegin--\>.*?\<!--ifIsHasOtherCommonShapeEnd--\>)|"
"([^\n]+ifIsHasOtherCommonShape\\b)|"
"([^\n]+\<!--ifIsHasOtherCommonShapeLine--\>)"
;
//----------------------------------------
const char* rmUnusedPart =
"(;)"
;
const char* rmUnusedPartInHTML =
"(<!--removed-->)"
;
//****************************************
const char* chsInPanel =
"(chs\.png)"
;
const char* toEngInPanel =
"(eng\.png)"
;
//*****************************************
const char* ifIsHasA =
"(INI\\[16]\\=\\d)"
;
const char* itIsHasA =
"(INI[16]=1)"
;
const char* ifIsSiFuInGrindWheel =
"(INI\\[36]\\=\\d)"
;
const char* itIsSiFuInGrindWheel =
"(INI[36]=1)"
;
const char* ifIsSiFuInDressWheel =
"(INI\\[37]\\=\\d)"
;
const char* itIsSiFuInDressWheel =
"(INI[37]=1)"
;
const char* ifIsAutoOp =
"(INI\\[69]\\=\\d)"
;
const char* itIsAutoOp =
"(INI[69]=1)"
;
const char* ifIsReOp =
"(INI\\[78]\\=\\d)"
;
const char* itIsReOp =
"(INI[78]=1)"
;
//***************************************
const char* fromMachineNameInMain =
"(machineName)"
;
const char* fromMachineNameCHS =
"(machineCHS)"
;
const char* fromMachineIndex =
"(machineIndex)"
;
const char* fromCustomInfo =
"(customInfo)"
;
const char* fromDebugDate =
"(debugDate)"
;
const char* fromSoftwareVersion =
"(softwareVersion)"
;
const char* fromSpecificationInfo =
"(specificationInfo)"
;
//***************************************
string souceLibraryDir[] = {
    seg + "Source_Library"
};

string commonSourceDir[] = {
    seg + "Source_Library" + seg + "CMA",
    seg + "Source_Library" + seg + "CMA" + seg + "DRESS_PART",
    seg + "Source_Library" + seg + "CMA" + seg + "DRESS_PART" + seg + "shape"
};
string commonShapeDir[] = {
    seg + "Source_Library" + seg + "CMA" + seg + "DRESS_PART" + seg + "CommonShape"
};
string externalShapeDir[] = {
    seg + "Source_Library" + seg + "CMA" + seg + "DRESS_PART" + seg + "ExterneShape"
};
string wormShapeDir[] = {
    seg + "Source_Library" + seg + "CMA" + seg + "DRESS_PART" + seg + "Worm"
};
string operationSourceDir[] = {
    seg + "Source_Library" + seg + "CMA" + seg + "auto_operation"
};

string centerSourceDir[] = {
    seg + "Source_Library" + seg + "CMA" + seg + "GRIND_CENTER"
};

string defSourceDir[] = {
    seg + "Source_Library" + seg + "DEF"
};

string mpfsourceDir[] = {
    seg + "Source_Library" + seg + "MPF"
};

string hmiCfgSourceDir[] = {
    seg + "Source_Library" + seg + "HMI" + seg + "cfg"
};

string hmiIco640SourceDir[] = {
    seg + "Source_Library" + seg + "HMI" + seg + "ico" + seg + "ico640"
};

string hmiIco800SourceDir[] = {
    seg + "Source_Library" + seg + "HMI" + seg + "ico" + seg + "ico800"
};
string hmiIco800DefaultSourceDir[] = {
    seg + "Source_Library" + seg + "HMI" + seg + "ico" + seg + "ico800" + seg + "default"
};
string hmiLngSourceDir[] = {
    seg + "Source_Library" + seg + "HMI" + seg + "lng"
};
string hmiHlpSourceDir[] = {
    seg + "Source_Library" + seg + "HMI" + seg + "hlp"
};
string hmiProjSourceDir[] = {
    seg + "Source_Library" + seg + "HMI" + seg + "proj"
};
string hmiRepositorySourceDir[] = {
    seg + "Source_Library" + seg + "HMI" + seg + "Repository"
};
string screwTapSourceDir[] = {
    seg + "Source_Library" + seg + "CMA" + seg + "SCREW_TAP"
};
//*******************************************
const char* swIncludeFiles[] = {
    "INFO_INIT\.MPF$"
};
const char* snIncludeFiles[] = {
    "INFO_INIT\.MPF$"
};
const char* hmiHlpIgnoreFiles[] = {
    "\.png$",
    "\.PNG$"
};
const char* commonProjFiles[] = {
    "custom\.com$",
    "dress\.com$",
    "dressware\.com$",
    "grind\.com$",
    "info\.com$",
    "process\.com$"
};
const char* cbProjFiles[] = {
    "shape\.com$",
    "shapecommon\.com$"
};
const char* autoProjFiles[] = {
    "auto\.com$"
};
const char* centerProjFiles[] = {
    "centerduanmian\.com$",
    "centermain\.com$",
    "centerwaiyuan\.com$"
};

const char* ncPlcParaFiles[] = {
    "NC_PLC-variates\.xml$"
};

const char* machinePic800[] = {
    "panel_0_0",
    "panel_0_1"
};
const char* machinePic640[] = {
    "splash"
};

const char* mpfMachineMainProgram[] = {
    "INFO_INIT\.MPF$"
};
const char* cmaMachineINIProgram[] = {
    "B_MACHINE_INI\.SPF$"
};
//*******************************************
const char* MultiSymbel =
"(×)|"
"(\\*)"
;
const char* MultiRepleace =
"(x)"
;
const char* Half =
"(/)"
;
const char* XiaHua =
"(_)"
;
const char* HenGang =
"(-)"
;
//*******************************************

string cmaDirRef = seg + "CMA";
string mpfDirRef = seg + "MPF";
string defDirRef = seg + "DEF";
string hmiDirRef = seg + "HMI";
string hmiCfgDirRef = seg + "HMI" + seg + "cfg";
string hmiIcoDirRef = seg + "HMI" + seg + "ico";
string hmiIco640DirRef = seg + "HMI" + seg + "ico" + seg + "ico640";
string hmiIco800DirRef = seg + "HMI" + seg + "ico" + seg + "ico800";
string hmiIco800DefaultDirRef = seg + "HMI" + seg + "ico" + seg + "ico800" + seg + "default";
string hmiLngDirRef = seg + "HMI" + seg + "lng";
string hmiProjDirRef = seg + "HMI" + seg + "proj";
string hmiHlpDirRef = seg + "HMI" + seg + "hlp";

const char* snxzSourceDirRef[] = { "SN$", "X_Z$" };
const char* swvwSourceDirRef[] = { "SW$", "V_W$" };
const char* swxzSourceDirRef[] = { "SW$", "X_Z$" };
//**********************************

const int swIFCount = sizeof(swIncludeFiles) / sizeof(swIncludeFiles[0]);
const int snIFCount = sizeof(snIncludeFiles) / sizeof(snIncludeFiles[0]);
const int commonPFCount = sizeof(commonProjFiles) / sizeof(commonProjFiles[0]);
const int cbPFCount = sizeof(cbProjFiles) / sizeof(cbProjFiles[0]);
const int autoPFCount = sizeof(autoProjFiles) / sizeof(autoProjFiles[0]);
const int centerPFCount = sizeof(centerProjFiles) / sizeof(centerProjFiles[0]);
const int snxzSDCount = sizeof(snxzSourceDirRef) / sizeof(snxzSourceDirRef[0]);
const int swvwSDCount = sizeof(swvwSourceDirRef) / sizeof(swvwSourceDirRef[0]);
const int swxzSDCount = sizeof(swxzSourceDirRef) / sizeof(swxzSourceDirRef[0]);
const int machinePic800Count = sizeof(machinePic800) / sizeof(machinePic800[0]);
const int machinePic640Count = sizeof(machinePic640) / sizeof(machinePic640[0]);
const int commentsInFilesCount = sizeof(commentsInFiles) / sizeof(commentsInFiles[0]);
const int ncPlcParaCount = sizeof(ncPlcParaFiles) / sizeof(ncPlcParaFiles[0]);
const int hmiHlpIgnoreFilesCount = sizeof(hmiHlpIgnoreFiles) / sizeof(hmiHlpIgnoreFiles[0]);

//**********************************************

GeneratePro::GeneratePro(QObject *parent) : QObject(parent)
{
    //qDebug() << "Current thread:" << thread();
}

void GeneratePro::test() {
    qDebug() << "Current thread:" << thread();
}

void GeneratePro::getJsonValue(){
    ConvertCode c;
    ReadAndWriteJson r;
    QJsonObject obj = r.readJsonToObj();
    QJsonObject obj2 = obj["programDir"].toObject();

    softwareVersion = obj["version"].toString().toStdString();

    sourceDir = obj2["sourceDir"].toString().toStdString();
    //sourceDir = c.UTF8ToGBK(sourceDir);
    destDir = obj2["destDir"].toString().toStdString();
    //destDir = c.UTF8ToGBK(destDir);

    machineName = obj["machineName"].toString().toStdString();
    machineNameLng = obj["machineNameLng"].toString().toStdString();
    machineNameLng = c.UTF8ToGBK(machineNameLng);
    machineIndex = obj["machineIndex"].toString().toStdString();
    customInfo = obj["customInfo"].toString().toStdString();
    customInfo = c.UTF8ToGBK(customInfo);
    lng = obj["lng"].toInt();

    machineType = obj["machineType"].toInt();
    wareType = obj["wareType"].toInt();
    ifOperation = obj["ifOperation"].toInt();
    ifCenter = obj["ifCenter"].toInt();
    ifHasU = obj["ifHasU"].toInt();
    measureMethord = obj["measureMethord"].toInt();
    wheelType = obj["wheelType"].toInt();
    shapeType = obj["shapeType"].toInt();
    ifHasA = obj["ifHasA"].toInt();
    grindWheelType = obj["grindWheelType"].toInt();
    dressWheelType = obj["dressWheelType"].toInt();
    ifRemoveComments = obj["ifRemoveComments"].toInt();
    roughFeedInput = obj["roughFeedInput"].toInt();
    ifHasReOp = obj["ifHasReOp"].toInt();
    ifHasScrewTap = obj["ifHasScrewTap"].toInt();
    ifHasWorm = obj["ifHasWorm"].toInt();

    cout << softwareVersion << endl;
    cout << "-------------------" << endl;
    cout << sourceDir << endl;
    cout << destDir << endl;
    cout << "-------------------" << endl;
    cout << machineName << endl;
    cout << machineNameLng << endl;
    cout << machineIndex << endl;
    cout << customInfo << endl;
    cout << lng << endl;
    cout << "-------------------" << endl;
    cout << machineType << endl;
    cout << wareType << endl;
    cout << ifOperation << endl;
    cout << ifCenter << endl;
    cout << ifHasU << endl;
    cout << measureMethord << endl;
    cout << wheelType << endl;
    cout << shapeType << endl;
    cout << ifHasA << endl;
    cout << grindWheelType << endl;
    cout << dressWheelType << endl;
    cout << ifRemoveComments << endl;
    cout << roughFeedInput << endl;
    cout << ifHasReOp << endl;
    cout << ifHasScrewTap << endl;
    cout << ifHasWorm << endl;
    cout << "-------------------" << endl;
}

void GeneratePro::startGenerate() {
    emit triggerStartingProcess();

    getJsonValue();

    FileWork project;

    specificationInfo.erase();

    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t t_now = chrono::system_clock::to_time_t(now);
    debugDate = ctime(&t_now);
    debugDate.pop_back();

    char* toDebugDate = (char*)debugDate.c_str();
    char* toSoftwareVersion = (char*)softwareVersion.c_str();

    //**************************************
    locale loc;
    for (string::size_type i = 0; i < machineName.length(); ++i)
    {
        machineName[i] = std::toupper(machineName[i], loc);
    }

    project.findAndReplaceInString(machineName, MultiSymbel, MultiRepleace);

    project.findAndReplaceInString(machineName, MultiRepleace, XiaHua);
    project.findAndReplaceInString(machineName, Half, HenGang);
    string machineNameForFileName = machineName;

    project.findAndReplaceInString(machineName, XiaHua, MultiRepleace);
    project.findAndReplaceInString(machineName, HenGang, Half);
    string machineNameForInfo = machineName;

    const char* toMachineNameInMain = (char*)machineNameForInfo.c_str();
    string nameFixed = machineNameForFileName + "$";
    const char* c_machineName[] = { (char*)nameFixed.c_str() };

    //*************************************************
    char* toMachineNameLng = (char*)machineNameLng.c_str();
    char* toMachineIndex = (char*)machineIndex.c_str();
    //************************************************

    char* toCustomInfo = (char*)customInfo.c_str();
    string machineNameForDirName = machineNameForFileName + "(#" + machineIndex + "-" + customInfo + ")";

    //************************************************

    if (lng == 0)
        hmiIco800DefaultSourceDir[0] += seg + "chs";
    else
        hmiIco800DefaultSourceDir[0] += seg + "eng";

    string destDirParent = destDir;
    destDir = destDir + seg + machineNameForDirName;

    //*******************************************

    const int commonSDSize = sizeof(commonSourceDir) / sizeof(commonSourceDir[0]);

    const char* c_commonSourceDir[] = {
        commonSourceDir[0].insert(0, sourceDir).c_str(),
        commonSourceDir[1].insert(0, sourceDir).c_str(),
        commonSourceDir[2].insert(0, sourceDir).c_str()
    };

    //const int commonSDSize = sizeof(c_commonSourceDir) / sizeof(c_commonSourceDir[0]);

    const char* c_souceLibraryDir[] = {
        souceLibraryDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_commonShapeDir[] = {
        commonShapeDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_externalShapeDir[] = {
        externalShapeDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_wormShapeDir[] = {
        wormShapeDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_operationSourceDir[] = {
        operationSourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_centerSourceDir[] = {
        centerSourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_defSourceDir[] = {
        defSourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_mpfsourceDir[] = {
        mpfsourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_hmiCfgSourceDir[] = {
        hmiCfgSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiIco640SourceDir[] = {
        hmiIco640SourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiIco800SourceDir[] = {
        hmiIco800SourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiIco800DefaultSourceDir[] = {
        hmiIco800DefaultSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiLngSourceDir[] = {
        hmiLngSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiHlpSourceDir[] = {
        hmiHlpSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiProjSourceDir[] = {
        hmiProjSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiRepositorySourceDir[] = {
        hmiRepositorySourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_screwTapSourceDir[] = {
        screwTapSourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_DestDirParent = destDirParent.c_str();
    const char* c_distMainDir = destDir.c_str();
    const char* c_cmaDestDir = cmaDirRef.insert(0, destDir).c_str();
    const char* c_mpfDestDir = mpfDirRef.insert(0, destDir).c_str();
    const char* c_defDestDir = defDirRef.insert(0, destDir).c_str();
    const char* c_hmiDestDir = hmiDirRef.insert(0, destDir).c_str();
    const char* c_hmiIcoDestDir = hmiIcoDirRef.insert(0, destDir).c_str();
    const char* c_hmiCfgDestDir = hmiCfgDirRef.insert(0, destDir).c_str();
    const char* c_hmiHlpDestDir = hmiHlpDirRef.insert(0, destDir).c_str();
    const char* c_hmiIco640DestDir = hmiIco640DirRef.insert(0, destDir).c_str();
    const char* c_hmiIco800DestDir = hmiIco800DirRef.insert(0, destDir).c_str();
    //const char* c_hmiIco800DefaultDestDir = hmiIco800DefaultDirRef.insert(0, destDir).c_str();
    const char* c_hmiLngDestDir = hmiLngDirRef.insert(0, destDir).c_str();
    const char* c_hmiProjDestDir = hmiProjDirRef.insert(0, destDir).c_str();

    //*********************************************************

    specificationInfo.append(to_string(machineType));
    if (machineType ==0)
        specificationInfo.append(to_string(ifHasScrewTap));
    specificationInfo.append(to_string(wareType));
    if (machineType == 0 && (wareType == 0 || wareType == 2))
        specificationInfo.append(to_string(ifHasWorm));
    if (wareType == 0 || wareType == 2) {
        specificationInfo.append(to_string(wheelType));
        specificationInfo.append(to_string(shapeType));
    }
    if (machineType == 0)
        specificationInfo.append(to_string(ifHasReOp));
    specificationInfo.append(to_string(ifOperation));
    if (ifOperation == 0)
        specificationInfo.append(to_string(measureMethord));
    if (machineType == 0) {
        specificationInfo.append(to_string(ifCenter));
        if (ifCenter == 0)
            specificationInfo.append(to_string(ifHasU));
    }
    specificationInfo.append(to_string(ifHasA));
    specificationInfo.append(to_string(grindWheelType));
    specificationInfo.append(to_string(dressWheelType));
    specificationInfo.append(to_string(roughFeedInput));
    specificationInfo.append(to_string(ifRemoveComments));
    char* toSpecificationInfo = (char*)specificationInfo.c_str();
    //************************************************

    cout << "\n\nprocessing:\n";

    if (!sourceDir.empty() && !destDir.empty())
    {
        project.lngIn = lng;

        cout << "\n\ncreating needed folders:\n";

        fs::path destPathParent = fs::system_complete(c_DestDirParent);
        fs::path destPath = fs::system_complete(destDir);
        fs::path hmiPath = fs::system_complete(c_hmiDestDir);
        fs::path hmiIcoPath = fs::system_complete(c_hmiIcoDestDir);
        fs::path hmiIco800Path = fs::system_complete(c_hmiIco800DestDir);
        fs::create_directory(destPathParent);
        fs::create_directory(destPath);
        fs::create_directory(hmiPath);
        fs::create_directory(hmiIcoPath);
        fs::create_directory(hmiIco800Path);

        cout << "\n\ncopy files:\n";
        project.copyFilesToNewDirWithIgnore(c_defSourceDir[0], c_defDestDir, NULL, 0);
        project.copyFilesToNewDirWithIgnore(c_hmiCfgSourceDir[0], c_hmiCfgDestDir, NULL, 0);
        project.copyFileFolderToNewDir(c_hmiHlpSourceDir[0], c_hmiHlpDestDir);
        project.copyFilesToNewDirWithIgnore(c_hmiLngSourceDir[0], c_hmiLngDestDir, NULL, 0);
        project.copyFilesToNewDirWithIgnore(c_hmiIco640SourceDir[0], c_hmiIco640DestDir, NULL, 0);
        project.copyFilesToNewDirWithIgnore(c_hmiIco800DefaultSourceDir[0], c_hmiIco800DestDir, NULL, 0);

        project.copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, commonProjFiles, commonPFCount);
        project.copyFilesToNewDirWithInclude(c_souceLibraryDir[0], c_distMainDir, ncPlcParaFiles, ncPlcParaCount);

        if (machineType == 0)
        {
            if (wareType == 0 || wareType == 1)
            {
                for (int i = 0; i < commonSDSize; i++) {
                    project.copyFilesToNewDirWithIgnoreRefDirs(c_commonSourceDir[i], swvwSourceDirRef, swvwSDCount, c_cmaDestDir, NULL, 0);
                }
            }
            else
            {
                for (int i = 0; i < commonSDSize; i++) {
                    project.copyFilesToNewDirWithIgnoreRefDirs(c_commonSourceDir[i], swxzSourceDirRef, swxzSDCount, c_cmaDestDir, NULL, 0);
                }
            }

            if (wareType != 1)
            {
                project.copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, cbProjFiles, cbPFCount);
                project.copyFilesToNewDirWithIgnore(c_commonShapeDir[0], c_cmaDestDir, NULL, 0);
                project.copyFilesToNewDirWithIgnore(c_externalShapeDir[0], c_cmaDestDir, NULL, 0);
            }

            if (wareType == 0 || wareType == 2)
            {
                if (ifHasWorm == 1)
                {
                    project.copyFilesToNewDirWithIgnore(c_wormShapeDir[0], c_cmaDestDir, NULL, 0);
                }
            }

            project.copyFilesToNewDirWithInclude(c_mpfsourceDir[0], c_mpfDestDir, swIncludeFiles, swIFCount);

            if (ifOperation == 0)
            {
                project.copyFilesToNewDirWithIgnoreRefDirs(c_operationSourceDir[0], swvwSourceDirRef, swvwSDCount, c_cmaDestDir, NULL, 0);
                project.copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, autoProjFiles, autoPFCount);
            }

            if (ifHasScrewTap == 0)
            {
                project.copyFilesToNewDirWithIgnore(c_screwTapSourceDir[0], c_cmaDestDir, NULL, 0);
            }
        }
        else
        {
            for (int i = 0; i < commonSDSize; i++) {
                project.copyFilesToNewDirWithIgnoreRefDirs(c_commonSourceDir[i], snxzSourceDirRef, snxzSDCount, c_cmaDestDir, NULL, 0);
            }

            if (wareType != 3)
            {
                project.copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, cbProjFiles, cbPFCount);
                project.copyFilesToNewDirWithIgnore(c_commonShapeDir[0], c_cmaDestDir, NULL, 0);
                project.copyFilesToNewDirWithIgnore(c_externalShapeDir[0], c_cmaDestDir, NULL, 0);
            }

            project.copyFilesToNewDirWithInclude(c_mpfsourceDir[0], c_mpfDestDir, snIncludeFiles, snIFCount);

            if (ifOperation == 0)
            {
                project.copyFilesToNewDirWithIgnoreRefDirs(c_operationSourceDir[0], snxzSourceDirRef, snxzSDCount, c_cmaDestDir, NULL, 0);
                project.copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, autoProjFiles, autoPFCount);
            }

            if (ifCenter == 0)
            {
                project.copyFilesToNewDirWithIgnoreRecursion(c_centerSourceDir[0], c_cmaDestDir, NULL, 0);
                project.copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, centerProjFiles, centerPFCount);
            }
        }

        cout << "\n\nreplacing in files:\n";
        if (machineType == 0)
        {
            if (wareType != 0 && wareType != 1)
            {
                project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsExternalVW, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsExternalVW, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            }

            if (wareType == 0 || wareType == 2)
            {
                if (ifHasWorm == 1)
                {
                    project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsNotHasWorm, rmUnusedPart, NULL, 0);
                    project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsNotHasWorm, rmUnusedPart, NULL, 0);
                }
                else
                {
                    project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsHasWorm, rmUnusedPart, NULL, 0);
                    project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsHasWorm, rmUnusedPart, NULL, 0);
                }
            }
            else
            {
                project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsHasWorm, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsHasWorm, rmUnusedPart, NULL, 0);
            }

            if (ifHasReOp == 0)
            {
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsNotHasReOperate, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsNotHasReOperate, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);

            }
            else
            {
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsHasReOperate, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsHasReOperate, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);

            }
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsInternal, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsInternalOnly, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsCenter, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiLngDestDir, ifIsInternal, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsInternal, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsCenter, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsCenter, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsCenter, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsInternal, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsInternal, rmUnusedPart, NULL, 0);

            if (ifHasScrewTap == 1)
            {
                project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsScrewTap, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsScrewTap, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsScrewTap, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsScrewTap, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            }
            else
            {
                project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsNotScrewTap, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsNotScrewTap, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsNotScrewTap, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsNotScrewTap, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            }
        }
        else
        {
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsExternal, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsExternalVW, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsExternal, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsExternalVW, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsExternal, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsExternal, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiLngDestDir, ifIsExternal, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsScrewTap, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsScrewTap, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsScrewTap, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsScrewTap, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);

            project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsHasWorm, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsHasWorm, rmUnusedPart, NULL, 0);

            if (ifCenter == 0)
            {
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsNotCenter, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsNotCenter, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsNotCenter, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsInternalOnly, rmUnusedPart, NULL, 0);
                if (ifHasU == 0)
                {
                    project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsNotHasU, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                    project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsNotHasU, rmUnusedPart, NULL, 0);
                }
                else
                {
                    project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsHasU, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                    project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsHasU, rmUnusedPart, NULL, 0);
                }
            }
            else
            {
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsCenter, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsCenter, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsCenter, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsCenter, rmUnusedPart, NULL, 0);
            }
        }

        if (ifOperation == 0)
        {
            switch (measureMethord)
            {
            case 0:
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsCeTouCeLiang, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsKaiGuanAndCeTouCeLiang, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsCenter, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsCeTouCeLiang, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsKaiGuanAndCeTouCeLiang, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsCenter, rmUnusedPart, NULL, 0);
                break;
            case 1:
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsKaiGuanCeLiang, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsKaiGuanAndCeTouCeLiang, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsKaiGuanCeLiang, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsKaiGuanAndCeTouCeLiang, rmUnusedPart, NULL, 0);
                if (machineType == 1 && ifCenter == 0)
                {
                    project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsNotCenter, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                    project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsNotCenter, rmUnusedPart, NULL, 0);
                }
                else
                {
                    project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsCenter, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                    project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsCenter, rmUnusedPart, NULL, 0);
                }
                break;
            case 2:
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsKaiGuanCeLiang, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsCeTouCeLiang, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsCenter, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsKaiGuanCeLiang, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsCeTouCeLiang, rmUnusedPart, NULL, 0);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsCenter, rmUnusedPart, NULL, 0);
                break;
            default:
                break;
            }
        }
        else
        {
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsAuto, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsAuto, rmUnusedPart, NULL, 0);
        }

        switch (wareType)
        {
        case 0:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare2, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare3, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare4, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare5, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare2, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare3, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare4, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare5, rmUnusedPart, NULL, 0);

            if (wheelType == 0)
            {
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsVWSide, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSide, rmUnusedPart, NULL, 0);
            }
            else
            {
                project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsVWSR, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSR, rmUnusedPart, NULL, 0);
            }
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsXZSR, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsXZSide, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsXNeiFront, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsXNeiBack, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsXWai, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsVH, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsBackDress, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSR, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSide, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXNeiFront, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXNeiBack, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXWai, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVH, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsBackDress, rmUnusedPart, NULL, 0);

            break;
        case 1:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare1, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare3, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare4, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare5, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare1, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare3, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare4, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare5, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVW, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsVW, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSR, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSide, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSR, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSide, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXNeiFront, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXNeiBack, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXWai, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVH, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsBackDress, rmUnusedPart, NULL, 0);

            break;
        case 2:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare1, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare2, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare4, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare5, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare1, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare2, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare4, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare5, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSR, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSide, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsV, rmUnusedPart, NULL, 0);
            if (wheelType == 0)
            {
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSide, rmUnusedPart, NULL, 0);
            }
            else
            {
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSR, rmUnusedPart, NULL, 0);
            }
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXNeiBack, rmUnusedPart, NULL, 0);

            if (machineType == 0)
            {
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXNeiFront, rmUnusedPart, NULL, 0);
            }
            else
            {
                project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXWai, rmUnusedPart, NULL, 0);
            }

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVH, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsBackDress, rmUnusedPart, NULL, 0);

            break;
        case 3:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare1, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare2, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare3, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare5, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare1, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare2, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare3, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare5, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsFrontDress, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSR, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSide, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsV, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSR, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSide, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXNeiFront, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXWai, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVH, rmUnusedPart, NULL, 0);
            break;
        case 4:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare1, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare2, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare3, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsDressWare4, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare1, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare2, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare3, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsDressWare4, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSR, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsVWSide, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsV, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSR, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXZSide, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXNeiBack, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXNeiFront, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsXWai, rmUnusedPart, NULL, 0);

            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsBackDress, rmUnusedPart, NULL, 0);

            break;
        default:
            break;
        }

        switch (wheelType)
        {
        case 0:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsSide, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsSide, rmUnusedPart, NULL, 0);
            break;
        case 1:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsSingleAndRound, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsSingleAndRound, rmUnusedPart, NULL, 0);
            break;
        default:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsSide, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsSingleAndRound, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsSide, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsSingleAndRound, rmUnusedPart, NULL, 0);
            break;
        }

        switch (shapeType)
        {
        case 0:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsOnlyArc, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsOnlyArc, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsHasOtherCommonShape, rmUnusedPart, NULL, 0);
            break;
        case 1:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsAllShape, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsAllShape, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsHasOtherCommonShape, rmUnusedPart, NULL, 0);
            break;
        default:
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsOnlyArc, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsArc, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsAllShape, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsOnlyArc, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsArc, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsAllShape, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsHasOtherCommonShape, rmUnusedPart, NULL, 0);
            break;
        }

        if (roughFeedInput == 1)
        {
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsNotRoughToAmount, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsNotRoughToAmount, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
        }
        else
        {
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, ifIsRoughToAmount, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, ifIsRoughToAmount, rmUnusedPartInHTML, hmiHlpIgnoreFiles, hmiHlpIgnoreFilesCount);
        }

        if (lng == 1)
        {
            project.findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, chsInPanel, toEngInPanel, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_hmiCfgDestDir, chsInPanel, toEngInPanel, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsCHS, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsCHS, rmUnusedPart, NULL, 0);
        }
        else
        {
            project.findAndRepleaceInDirWithIgnore(c_cmaDestDir, ifIsENG, rmUnusedPart, NULL, 0);
            project.findAndRepleaceInDirWithIgnore(c_mpfDestDir, ifIsENG, rmUnusedPart, NULL, 0);
        }

        cout << "\n\ncopy pictures:\n";
        project.copyFilesToNewDirWithRefDir(c_hmiIco800SourceDir[0], c_hmiIco800DestDir, c_hmiProjDestDir, NULL, 0);

        project.copyFilesToNewDirWithIncludeDir(c_hmiRepositorySourceDir[0], c_hmiIco800DestDir, c_machineName, 1, machinePic800, machinePic800Count);
        project.copyFilesToNewDirWithIncludeDir(c_hmiRepositorySourceDir[0], c_hmiIco640DestDir, c_machineName, 1, machinePic640, machinePic640Count);

        cout << "\n\nmodify machine spcifications:\n";
        if (ifHasA == 0) {
            project.findAndRepleaceInDirWithInclude(c_cmaDestDir, ifIsHasA, itIsHasA, cmaMachineINIProgram, 1);
        }
        if (grindWheelType == 0) {
            project.findAndRepleaceInDirWithInclude(c_cmaDestDir, ifIsSiFuInGrindWheel, itIsSiFuInGrindWheel, cmaMachineINIProgram, 1);
        }
        if (dressWheelType == 0) {
            project.findAndRepleaceInDirWithInclude(c_cmaDestDir, ifIsSiFuInDressWheel, itIsSiFuInDressWheel, cmaMachineINIProgram, 1);
        }
        if (ifOperation == 0) {
            project.findAndRepleaceInDirWithInclude(c_cmaDestDir, ifIsAutoOp, itIsAutoOp, cmaMachineINIProgram, 1);
        }
        if (machineType == 0)
        {
            if (ifHasReOp == 0)
            {
                project.findAndRepleaceInDirWithInclude(c_cmaDestDir, ifIsReOp, itIsReOp, cmaMachineINIProgram, 1);
            }
        }

        project.findAndRepleaceInDirWithInclude(c_mpfDestDir, fromMachineNameInMain, toMachineNameInMain, mpfMachineMainProgram, 1);
        project.findAndRepleaceInDirWithInclude(c_hmiLngDestDir, fromMachineNameInMain, toMachineNameInMain, NULL, 0);

        project.findAndRepleaceInDirWithInclude(c_mpfDestDir, fromMachineNameCHS, toMachineNameLng, mpfMachineMainProgram, 1);
        project.findAndRepleaceInDirWithInclude(c_hmiLngDestDir, fromMachineNameCHS, toMachineNameLng, NULL, 0);

        project.findAndRepleaceInDirWithInclude(c_mpfDestDir, fromMachineIndex, toMachineIndex, mpfMachineMainProgram, 1);
        project.findAndRepleaceInDirWithInclude(c_hmiLngDestDir, fromMachineIndex, toMachineIndex, NULL, 0);

        project.findAndRepleaceInDirWithInclude(c_mpfDestDir, fromSoftwareVersion, toSoftwareVersion, mpfMachineMainProgram, 1);
        project.findAndRepleaceInDirWithInclude(c_mpfDestDir, fromDebugDate, toDebugDate, mpfMachineMainProgram, 1);
        project.findAndRepleaceInDirWithInclude(c_mpfDestDir, fromSpecificationInfo, toSpecificationInfo, mpfMachineMainProgram, 1);
        project.findAndRepleaceInDirWithInclude(c_mpfDestDir, fromCustomInfo, toCustomInfo, mpfMachineMainProgram, 1);

        if (ifRemoveComments == 0)
        {
            cout << "\n\nremoving comments:\n";
            project.findAndRepleaceInDirWithInclude(c_cmaDestDir, isComments, rmUnusedPart, commentsInFiles, commentsInFilesCount);
            project.findAndRepleaceInDirWithInclude(c_hmiProjDestDir, isComments, rmUnusedPart, commentsInFiles, commentsInFilesCount);
            project.findAndRepleaceInDirWithInclude(c_mpfDestDir, isComments, rmUnusedPart, commentsInFiles, commentsInFilesCount);
        }

        cout << "\n\nrenaming main file:\n";
        project.renameFileInDir(c_mpfDestDir, mpfMachineMainProgram, machineNameForFileName);

    }
    else {
        std::cout << "pleace enter the right directory." << std::endl;
    }

    emit triggerFinishedProcess();
}

