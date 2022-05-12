#include "removecommit.hpp"
#include <iostream>

using namespace std;

RemoveCommit::RemoveCommit(QObject *parent) : QObject(parent)
{
    project = new FileWork;
    r = new ReadAndWriteJson;
    c = new ConvertCode;
}

RemoveCommit::~RemoveCommit() {
    delete project;
    delete r;
    delete c;
}

void RemoveCommit::startProcess() {
    const char* isComments =
    "(;[^\n\*\"][^\n]+)";

    const char* rmUnusedPart =
    "(;)"
    ;

    const char* commentsInFiles[] = {
        "com$",
        "spf$",
        "mpf$",
        "COM$",
        "SPF$",
        "MPF$"
    };

    const int commentsInFilesCount = sizeof(commentsInFiles) / sizeof(commentsInFiles[0]);

    emit triggerStartingProcess();

    QJsonObject obj = r->readJsonToObj();

    string dir = obj["removeDir"].toString().toStdString();
    dir = c->UTF8ToGBK(dir);
    const char* c_dir = dir.c_str();

    cout << "\n\nremoving comments:\n";
    project->findAndRepleaceInDirWithIncludeRecursion(c_dir, isComments, rmUnusedPart, commentsInFiles, commentsInFilesCount);

    emit triggerFinishedProcess();
}
