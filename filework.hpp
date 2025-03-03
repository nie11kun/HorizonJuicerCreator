//
//  FileWork.hpp
//  BoostTest
//
//  Created by Marco Nie on 2018/5/18.
//  Copyright © 2018 Marco Nie. All rights reserved.
//

#ifndef FileWork_hpp
#define FileWork_hpp

#include <stdio.h>
#include <string>
#include <map>

using namespace std;

class FileWork
{
public:
    FileWork();
    int lngIn;
    bool findAndReplaceInString(string &in, const char* find, const char* replace);
    bool findAndRepleaceInFile(string filename, const char* findMe, const char* replaceMe);
    bool findAndReplaceFromJSONWithIgnore(const char* dir, const char* jsonData, const char* ignore[], int ignoreCount);
    bool findAndReplaceMultipleInFile(const std::string& filePath, const std::map<std::string, std::string>& replacements);
    bool findAndRepleaceInDirWithIgnore(const char* dir, const char* findMe, const char* replaceMe, const char* ignore[], int ignoreCount);
    bool findAndRepleaceInDirWithInclude(const char* dir, const char* findMe, const char* replaceMe, const char* include[], int includeCount);
    bool findAndRepleaceInDirWithIgnoreRecursion(const char* dir, const char *findMe, const char *replaceMe, const char* ignore[], int ignoreCount);
    bool findAndRepleaceInDirWithIncludeRecursion(const char* dir, const char *findMe, const char *replaceMe, const char* include[], int includeCount);
    bool copyFilesToNewDirWithIgnore(const char* oldDir, const char* newDir, const char* ignore[], int ignoreCount);
    bool copyFilesToNewDirWithInclude(const char* oldDir, const char* newDir, const char* include[], int includeCount);
    bool copyFilesToNewDirWithIncludeDir(const char* oldDir, const char* newDir, const char* includeDir[], int includeDirCount, const char* includeFiles[], int includeFilesCount);
    bool copyFilesToNewDirWithRefDir(const char* oldDir, const char* newDir, const char* refDir, const char* include[], int includeCount);
    bool copyFilesToNewDirWithIgnoreRefDirs(const char* oldDir, const char* refDir[],int refDirCount, const char* newDir, const char* ignore[], int IgnoreCount);
    bool copyFilesToNewDirWithIgnoreRecursion(const char* oldDir, const char* newDir, const char* ignore[], int ignoreCount);
    bool copyFileFolderToNewDir(const char* oldDir, const char* newDir);
    void load_file(std::string& s, std::istream& is);
    int searchWithKey(const string str, const char* e[], int eCount);
    int searchWithKeyAndRefDir(const char* refDir, string str);
    bool renameFileInDir(const char* dir, const char* find[], string name);
    void readFileLineByLineToCout(string filename);
    bool resizeImageFile(const std::string &filePath, int targetWidth, int targetHeight);
    bool resizeImageInDirWithInclude(const char* dir, const char* resolution, const char* include[], int includeCount);
protected:
private:
#ifdef _WIN32
    string seg = "\\";
#else
    string seg = "/";
#endif

};

#endif /* FileWork_hpp */
