#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <string>

using namespace std;

class Parameters
{
public:
    Parameters();

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
};

#endif // PARAMETERS_HPP
