#include "generatepro.h"
#include <iostream>
#include "filework.hpp"
#include "boost/filesystem.hpp"
#include "parameters.hpp"

namespace fs = boost::filesystem;

#ifdef _WIN32
    string seg = "\\";
#else
    string seg = "/";
#endif

GeneratePro::GeneratePro(QObject *parent) : QObject(parent)
{
    c = new ConvertCode;
    r = new ReadAndWriteJson;
    project = new FileWork;
}

GeneratePro::~GeneratePro() {
    delete c;
    delete r;
    delete project;
}

void GeneratePro::test() {
    qDebug() << "Current thread:" << thread();
}

void GeneratePro::getJsonValue(){
    QJsonObject obj = r->readJsonToObj();
    QJsonObject obj2 = obj["programDir"].toObject();

    softwareVersion = obj["version"].toString().toStdString();

    sourceDir = obj2["sourceDir"].toString().toStdString();
    destDir = obj2["destDir"].toString().toStdString();

    machineName = obj["machineName"].toString().toStdString();
    machineNameLng = obj["machineNameLng"].toString().toStdString();
    machineIndex = obj["machineIndex"].toString().toStdString();
    customInfo = obj["customInfo"].toString().toStdString();
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
    Parameters *p;

    emit triggerStartingProcess();

    getJsonValue();

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

    project->findAndReplaceInString(machineName, p->MultiSymbel, p->MultiRepleace);

    project->findAndReplaceInString(machineName, p->MultiRepleace, p->XiaHua);
    project->findAndReplaceInString(machineName, p->Half, p->HenGang);
    string machineNameForFileName = machineName;

    project->findAndReplaceInString(machineName, p->XiaHua, p->MultiRepleace);
    project->findAndReplaceInString(machineName, p->HenGang, p->Half);
    string machineNameForInfo = machineName;

    const char* toMachineNameInMain = (char*)machineNameForInfo.c_str();
    string nameFixed = machineNameForFileName + "$";
    const char* c_machineName[] = { (char*)nameFixed.c_str() };

    //*************************************************
    char* toMachineNameLng = (char*)machineNameLng.c_str();
    char* toMachineIndex = (char*)machineIndex.c_str();
    //************************************************

    char* toCustomInfo = (char*)customInfo.c_str();

    string customInfoGBK = c->UTF8ToGBK(customInfo);
    string machineNameForDirName = machineNameForFileName + "(#" + machineIndex + "-" + customInfoGBK + ")";

    //************************************************

    if (lng == 0)
        p->hmiIco800DefaultSourceDir[0] += seg + "chs";
    else
        p->hmiIco800DefaultSourceDir[0] += seg + "eng";

    string destDirParent = destDir;
    destDir = destDir + seg + machineNameForDirName;

    //*******************************************

    const int commonSDSize = sizeof(p->commonSourceDir) / sizeof(p->commonSourceDir[0]);

    const char* c_commonSourceDir[] = {
        p->commonSourceDir[0].insert(0, sourceDir).c_str(),
        p->commonSourceDir[1].insert(0, sourceDir).c_str(),
        p->commonSourceDir[2].insert(0, sourceDir).c_str()
    };

    //const int commonSDSize = sizeof(c_commonSourceDir) / sizeof(c_commonSourceDir[0]);

    const char* c_souceLibraryDir[] = {
        p->souceLibraryDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_commonShapeDir[] = {
        p->commonShapeDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_externalShapeDir[] = {
        p->externalShapeDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_wormShapeDir[] = {
        p->wormShapeDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_operationSourceDir[] = {
        p->operationSourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_centerSourceDir[] = {
        p->centerSourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_defSourceDir[] = {
        p->defSourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_mpfsourceDir[] = {
        p->mpfsourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_hmiCfgSourceDir[] = {
        p->hmiCfgSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiIco640SourceDir[] = {
        p->hmiIco640SourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiIco800SourceDir[] = {
        p->hmiIco800SourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiIco800DefaultSourceDir[] = {
        p->hmiIco800DefaultSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiLngSourceDir[] = {
        p->hmiLngSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiHlpSourceDir[] = {
        p->hmiHlpSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiProjSourceDir[] = {
        p->hmiProjSourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_hmiRepositorySourceDir[] = {
        p->hmiRepositorySourceDir[0].insert(0, sourceDir).c_str()
    };
    const char* c_screwTapSourceDir[] = {
        p->screwTapSourceDir[0].insert(0, sourceDir).c_str()
    };

    const char* c_DestDirParent = destDirParent.c_str();
    const char* c_distMainDir = destDir.c_str();
    const char* c_cmaDestDir = p->cmaDirRef.insert(0, destDir).c_str();
    const char* c_mpfDestDir = p->mpfDirRef.insert(0, destDir).c_str();
    const char* c_defDestDir = p->defDirRef.insert(0, destDir).c_str();
    const char* c_hmiDestDir = p->hmiDirRef.insert(0, destDir).c_str();
    const char* c_hmiIcoDestDir = p->hmiIcoDirRef.insert(0, destDir).c_str();
    const char* c_hmiCfgDestDir = p->hmiCfgDirRef.insert(0, destDir).c_str();
    const char* c_hmiHlpDestDir = p->hmiHlpDirRef.insert(0, destDir).c_str();
    const char* c_hmiIco640DestDir = p->hmiIco640DirRef.insert(0, destDir).c_str();
    const char* c_hmiIco800DestDir = p->hmiIco800DirRef.insert(0, destDir).c_str();
    //const char* c_hmiIco800DefaultDestDir = hmiIco800DefaultDirRef.insert(0, destDir).c_str();
    const char* c_hmiLngDestDir = p->hmiLngDirRef.insert(0, destDir).c_str();
    const char* c_hmiProjDestDir = p->hmiProjDirRef.insert(0, destDir).c_str();

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
        project->lngIn = lng;

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
        project->copyFilesToNewDirWithIgnore(c_defSourceDir[0], c_defDestDir, NULL, 0);
        project->copyFilesToNewDirWithIgnore(c_hmiCfgSourceDir[0], c_hmiCfgDestDir, NULL, 0);
        project->copyFileFolderToNewDir(c_hmiHlpSourceDir[0], c_hmiHlpDestDir);
        project->copyFilesToNewDirWithIgnore(c_hmiLngSourceDir[0], c_hmiLngDestDir, NULL, 0);
        project->copyFilesToNewDirWithIgnore(c_hmiIco640SourceDir[0], c_hmiIco640DestDir, NULL, 0);
        project->copyFilesToNewDirWithIgnore(c_hmiIco800DefaultSourceDir[0], c_hmiIco800DestDir, NULL, 0);

        project->copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, p->commonProjFiles, p->commonPFCount);
        project->copyFilesToNewDirWithInclude(c_souceLibraryDir[0], c_distMainDir, p->ncPlcParaFiles, p->ncPlcParaCount);

        if (machineType == 0)
        {
            if (wareType == 0 || wareType == 1)
            {
                for (int i = 0; i < commonSDSize; i++) {
                    project->copyFilesToNewDirWithIgnoreRefDirs(c_commonSourceDir[i], p->swvwSourceDirRef, p->swvwSDCount, c_cmaDestDir, NULL, 0);
                }
            }
            else
            {
                for (int i = 0; i < commonSDSize; i++) {
                    project->copyFilesToNewDirWithIgnoreRefDirs(c_commonSourceDir[i], p->swxzSourceDirRef, p->swxzSDCount, c_cmaDestDir, NULL, 0);
                }
            }

            if (wareType != 1)
            {
                project->copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, p->cbProjFiles, p->cbPFCount);
                project->copyFilesToNewDirWithIgnore(c_commonShapeDir[0], c_cmaDestDir, NULL, 0);
                project->copyFilesToNewDirWithIgnore(c_externalShapeDir[0], c_cmaDestDir, NULL, 0);
            }

            if (wareType == 0 || wareType == 2)
            {
                if (ifHasWorm == 1)
                {
                    project->copyFilesToNewDirWithIgnore(c_wormShapeDir[0], c_cmaDestDir, NULL, 0);
                }
            }

            project->copyFilesToNewDirWithInclude(c_mpfsourceDir[0], c_mpfDestDir, p->swIncludeFiles, p->swIFCount);

            if (ifOperation == 0)
            {
                project->copyFilesToNewDirWithIgnoreRefDirs(c_operationSourceDir[0], p->swvwSourceDirRef, p->swvwSDCount, c_cmaDestDir, NULL, 0);
                project->copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, p->autoProjFiles, p->autoPFCount);
            }

            if (ifHasScrewTap == 0)
            {
                project->copyFilesToNewDirWithIgnore(c_screwTapSourceDir[0], c_cmaDestDir, NULL, 0);
            }
        }
        else
        {
            for (int i = 0; i < commonSDSize; i++) {
                project->copyFilesToNewDirWithIgnoreRefDirs(c_commonSourceDir[i], p->snxzSourceDirRef, p->snxzSDCount, c_cmaDestDir, NULL, 0);
            }

            if (wareType != 3)
            {
                project->copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, p->cbProjFiles, p->cbPFCount);
                project->copyFilesToNewDirWithIgnore(c_commonShapeDir[0], c_cmaDestDir, NULL, 0);
                project->copyFilesToNewDirWithIgnore(c_externalShapeDir[0], c_cmaDestDir, NULL, 0);
            }

            project->copyFilesToNewDirWithInclude(c_mpfsourceDir[0], c_mpfDestDir, p->snIncludeFiles, p->snIFCount);

            if (ifOperation == 0)
            {
                project->copyFilesToNewDirWithIgnoreRefDirs(c_operationSourceDir[0], p->snxzSourceDirRef, p->snxzSDCount, c_cmaDestDir, NULL, 0);
                project->copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, p->autoProjFiles, p->autoPFCount);
            }

            if (ifCenter == 0)
            {
                project->copyFilesToNewDirWithIgnoreRecursion(c_centerSourceDir[0], c_cmaDestDir, NULL, 0);
                project->copyFilesToNewDirWithInclude(c_hmiProjSourceDir[0], c_hmiProjDestDir, p->centerProjFiles, p->centerPFCount);
            }
        }

        cout << "\n\nreplacing in files:\n";
        if (machineType == 0)
        {
            if (wareType != 0 && wareType != 1)
            {
                project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsExternalVW, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsExternalVW, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            }

            if (wareType == 0 || wareType == 2)
            {
                if (ifHasWorm == 1)
                {
                    project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsNotHasWorm, p->rmUnusedPart, NULL, 0);
                    project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsNotHasWorm, p->rmUnusedPart, NULL, 0);
                }
                else
                {
                    project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsHasWorm, p->rmUnusedPart, NULL, 0);
                    project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsHasWorm, p->rmUnusedPart, NULL, 0);
                }
            }
            else
            {
                project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsHasWorm, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsHasWorm, p->rmUnusedPart, NULL, 0);
            }

            if (ifHasReOp == 0)
            {
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsNotHasReOperate, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsNotHasReOperate, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);

            }
            else
            {
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsHasReOperate, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsHasReOperate, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);

            }
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsInternal, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsInternalOnly, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsCenter, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiLngDestDir, p->ifIsInternal, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsInternal, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsCenter, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsCenter, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsCenter, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsInternal, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsInternal, p->rmUnusedPart, NULL, 0);

            if (ifHasScrewTap == 1)
            {
                project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsScrewTap, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsScrewTap, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsScrewTap, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsScrewTap, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            }
            else
            {
                project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsNotScrewTap, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsNotScrewTap, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsNotScrewTap, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsNotScrewTap, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            }
        }
        else
        {
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsExternal, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsExternalVW, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsExternal, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsExternalVW, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsExternal, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsExternal, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiLngDestDir, p->ifIsExternal, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsScrewTap, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsScrewTap, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsScrewTap, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsScrewTap, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);

            project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsHasWorm, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsHasWorm, p->rmUnusedPart, NULL, 0);

            if (ifCenter == 0)
            {
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsNotCenter, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsNotCenter, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsNotCenter, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsInternalOnly, p->rmUnusedPart, NULL, 0);
                if (ifHasU == 0)
                {
                    project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsNotHasU, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                    project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsNotHasU, p->rmUnusedPart, NULL, 0);
                }
                else
                {
                    project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsHasU, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                    project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsHasU, p->rmUnusedPart, NULL, 0);
                }
            }
            else
            {
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsCenter, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsCenter, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsCenter, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsCenter, p->rmUnusedPart, NULL, 0);
            }
        }

        if (ifOperation == 0)
        {
            switch (measureMethord)
            {
            case 0:
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsCeTouCeLiang, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsKaiGuanAndCeTouCeLiang, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsCenter, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsCeTouCeLiang, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsKaiGuanAndCeTouCeLiang, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsCenter, p->rmUnusedPart, NULL, 0);
                break;
            case 1:
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsKaiGuanCeLiang, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsKaiGuanAndCeTouCeLiang, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsKaiGuanCeLiang, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsKaiGuanAndCeTouCeLiang, p->rmUnusedPart, NULL, 0);
                if (machineType == 1 && ifCenter == 0)
                {
                    project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsNotCenter, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                    project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsNotCenter, p->rmUnusedPart, NULL, 0);
                }
                else
                {
                    project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsCenter, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                    project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsCenter, p->rmUnusedPart, NULL, 0);
                }
                break;
            case 2:
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsKaiGuanCeLiang, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsCeTouCeLiang, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsCenter, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsKaiGuanCeLiang, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsCeTouCeLiang, p->rmUnusedPart, NULL, 0);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsCenter, p->rmUnusedPart, NULL, 0);
                break;
            default:
                break;
            }
        }
        else
        {
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsAuto, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsAuto, p->rmUnusedPart, NULL, 0);
        }

        switch (wareType)
        {
        case 0:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare2, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare3, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare4, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare5, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare2, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare3, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare4, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare5, p->rmUnusedPart, NULL, 0);

            if (wheelType == 0)
            {
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsVWSide, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSide, p->rmUnusedPart, NULL, 0);
            }
            else
            {
                project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsVWSR, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSR, p->rmUnusedPart, NULL, 0);
            }
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsXZSR, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsXZSide, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsXNeiFront, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsXNeiBack, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsXWai, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsVH, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsBackDress, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSR, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSide, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXNeiFront, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXNeiBack, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXWai, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVH, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsBackDress, p->rmUnusedPart, NULL, 0);

            break;
        case 1:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare1, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare3, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare4, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare5, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare1, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare3, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare4, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare5, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVW, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsVW, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSR, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSide, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSR, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSide, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXNeiFront, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXNeiBack, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXWai, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVH, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsBackDress, p->rmUnusedPart, NULL, 0);

            break;
        case 2:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare1, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare2, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare4, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare5, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare1, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare2, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare4, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare5, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSR, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSide, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsV, p->rmUnusedPart, NULL, 0);
            if (wheelType == 0)
            {
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSide, p->rmUnusedPart, NULL, 0);
            }
            else
            {
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSR, p->rmUnusedPart, NULL, 0);
            }
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXNeiBack, p->rmUnusedPart, NULL, 0);

            if (machineType == 0)
            {
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXNeiFront, p->rmUnusedPart, NULL, 0);
            }
            else
            {
                project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXWai, p->rmUnusedPart, NULL, 0);
            }

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVH, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsBackDress, p->rmUnusedPart, NULL, 0);

            break;
        case 3:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare1, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare2, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare3, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare5, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare1, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare2, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare3, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare5, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsFrontDress, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSR, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSide, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsV, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSR, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSide, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXNeiFront, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXWai, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVH, p->rmUnusedPart, NULL, 0);
            break;
        case 4:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare1, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare2, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare3, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsDressWare4, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare1, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare2, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare3, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsDressWare4, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSR, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsVWSide, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsV, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSR, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXZSide, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXNeiBack, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXNeiFront, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsXWai, p->rmUnusedPart, NULL, 0);

            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsBackDress, p->rmUnusedPart, NULL, 0);

            break;
        default:
            break;
        }

        switch (wheelType)
        {
        case 0:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsSide, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsSide, p->rmUnusedPart, NULL, 0);
            break;
        case 1:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsSingleAndRound, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsSingleAndRound, p->rmUnusedPart, NULL, 0);
            break;
        default:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsSide, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsSingleAndRound, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsSide, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsSingleAndRound, p->rmUnusedPart, NULL, 0);
            break;
        }

        switch (shapeType)
        {
        case 0:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsOnlyArc, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsOnlyArc, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsHasOtherCommonShape, p->rmUnusedPart, NULL, 0);
            break;
        case 1:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsAllShape, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsAllShape, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsHasOtherCommonShape, p->rmUnusedPart, NULL, 0);
            break;
        default:
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsOnlyArc, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsArc, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsAllShape, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsOnlyArc, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsArc, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsAllShape, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsHasOtherCommonShape, p->rmUnusedPart, NULL, 0);
            break;
        }

        if (roughFeedInput == 1)
        {
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsNotRoughToAmount, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsNotRoughToAmount, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
        }
        else
        {
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->ifIsRoughToAmount, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnoreRecursion(c_hmiHlpDestDir, p->ifIsRoughToAmount, p->rmUnusedPartInHTML, p->hmiHlpIgnoreFiles, p->hmiHlpIgnoreFilesCount);
        }

        if (lng == 1)
        {
            project->findAndRepleaceInDirWithIgnore(c_hmiProjDestDir, p->chsInPanel, p->toEngInPanel, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_hmiCfgDestDir, p->chsInPanel, p->toEngInPanel, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsCHS, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsCHS, p->rmUnusedPart, NULL, 0);
        }
        else
        {
            project->findAndRepleaceInDirWithIgnore(c_cmaDestDir, p->ifIsENG, p->rmUnusedPart, NULL, 0);
            project->findAndRepleaceInDirWithIgnore(c_mpfDestDir, p->ifIsENG, p->rmUnusedPart, NULL, 0);
        }

        cout << "\n\ncopy pictures:\n";
        project->copyFilesToNewDirWithRefDir(c_hmiIco800SourceDir[0], c_hmiIco800DestDir, c_hmiProjDestDir, NULL, 0);

        project->copyFilesToNewDirWithIncludeDir(c_hmiRepositorySourceDir[0], c_hmiIco800DestDir, c_machineName, 1, p->machinePic800, p->machinePic800Count);
        project->copyFilesToNewDirWithIncludeDir(c_hmiRepositorySourceDir[0], c_hmiIco640DestDir, c_machineName, 1, p->machinePic640, p->machinePic640Count);

        cout << "\n\nmodify machine spcifications:\n";
        if (ifHasA == 0) {
            project->findAndRepleaceInDirWithInclude(c_cmaDestDir, p->ifIsHasA, p->itIsHasA, p->cmaMachineINIProgram, 1);
        }
        if (grindWheelType == 0) {
            project->findAndRepleaceInDirWithInclude(c_cmaDestDir, p->ifIsSiFuInGrindWheel, p->itIsSiFuInGrindWheel, p->cmaMachineINIProgram, 1);
        }
        if (dressWheelType == 0) {
            project->findAndRepleaceInDirWithInclude(c_cmaDestDir, p->ifIsSiFuInDressWheel, p->itIsSiFuInDressWheel, p->cmaMachineINIProgram, 1);
        }
        if (ifOperation == 0) {
            project->findAndRepleaceInDirWithInclude(c_cmaDestDir, p->ifIsAutoOp, p->itIsAutoOp, p->cmaMachineINIProgram, 1);
        }
        if (machineType == 0)
        {
            if (ifHasReOp == 0)
            {
                project->findAndRepleaceInDirWithInclude(c_cmaDestDir, p->ifIsReOp, p->itIsReOp, p->cmaMachineINIProgram, 1);
            }
        }

        project->findAndRepleaceInDirWithInclude(c_mpfDestDir, p->fromMachineNameInMain, toMachineNameInMain, p->mpfMachineMainProgram, 1);
        project->findAndRepleaceInDirWithInclude(c_hmiLngDestDir, p->fromMachineNameInMain, toMachineNameInMain, NULL, 0);

        project->findAndRepleaceInDirWithInclude(c_mpfDestDir, p->fromMachineNameCHS, toMachineNameLng, p->mpfMachineMainProgram, 1);
        project->findAndRepleaceInDirWithInclude(c_hmiLngDestDir, p->fromMachineNameCHS, toMachineNameLng, NULL, 0);

        project->findAndRepleaceInDirWithInclude(c_mpfDestDir, p->fromMachineIndex, toMachineIndex, p->mpfMachineMainProgram, 1);
        project->findAndRepleaceInDirWithInclude(c_hmiLngDestDir, p->fromMachineIndex, toMachineIndex, NULL, 0);

        project->findAndRepleaceInDirWithInclude(c_mpfDestDir, p->fromSoftwareVersion, toSoftwareVersion, p->mpfMachineMainProgram, 1);
        project->findAndRepleaceInDirWithInclude(c_mpfDestDir, p->fromDebugDate, toDebugDate, p->mpfMachineMainProgram, 1);
        project->findAndRepleaceInDirWithInclude(c_mpfDestDir, p->fromSpecificationInfo, toSpecificationInfo, p->mpfMachineMainProgram, 1);
        project->findAndRepleaceInDirWithInclude(c_mpfDestDir, p->fromCustomInfo, toCustomInfo, p->mpfMachineMainProgram, 1);

        if (ifRemoveComments == 0)
        {
            cout << "\n\nremoving comments:\n";
            project->findAndRepleaceInDirWithInclude(c_cmaDestDir, p->isComments, p->rmUnusedPart, p->commentsInFiles, p->commentsInFilesCount);
            project->findAndRepleaceInDirWithInclude(c_hmiProjDestDir, p->isComments, p->rmUnusedPart, p->commentsInFiles, p->commentsInFilesCount);
            project->findAndRepleaceInDirWithInclude(c_mpfDestDir, p->isComments, p->rmUnusedPart, p->commentsInFiles, p->commentsInFilesCount);
        }

        cout << "\n\nrenaming main file:\n";
        project->renameFileInDir(c_mpfDestDir, p->mpfMachineMainProgram, machineNameForFileName);

    }
    else {
        std::cout << "pleace enter the right directory." << std::endl;
    }

    emit triggerFinishedProcess();
}

