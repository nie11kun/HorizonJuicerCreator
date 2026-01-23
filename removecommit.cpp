/**
 * @file removecommit.cpp
 * @brief Comment removal process handler implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "removecommit.hpp"

#include <iostream>

using namespace std;

RemoveCommit::RemoveCommit(QObject *parent) : QObject(parent) {
  fileHandler = new FileWork;
  jsonHandler = new ReadAndWriteJson;
  converter = new ConvertCode;
}

RemoveCommit::~RemoveCommit() {
  delete fileHandler;
  delete jsonHandler;
  delete converter;
}

void RemoveCommit::startProcess() {
  // Regex pattern to match comment lines (starting with ; but not string
  // literals)
  const char *commentPattern = "(;[^\\n\\*\\\"][^\\n]+)";
  const char *removePattern = "(;)";

  // File extensions to process
  const char *targetExtensions[] = {"com$", "spf$", "mpf$",
                                    "COM$", "SPF$", "MPF$"};
  const int extensionCount =
      sizeof(targetExtensions) / sizeof(targetExtensions[0]);

  emit triggerStartingProcess();

  // Get target directory from configuration
  QJsonObject config = jsonHandler->readJsonToObj();
  string targetDir = config["removeDir"].toString().toStdString();
  targetDir = converter->UTF8ToGBK(targetDir);
  const char *dirPath = targetDir.c_str();

  cout << "\n\nremoving comments:\n";
  fileHandler->findAndRepleaceInDirWithIncludeRecursion(
      dirPath, commentPattern, removePattern, targetExtensions, extensionCount);

  emit triggerFinishedProcess();
}
