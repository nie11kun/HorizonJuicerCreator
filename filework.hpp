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

using namespace std;

class FileWork
{
public:
    FileWork();
    int lngIn;
    bool findAndReplaceInString(string &in, char* find, char* replace);
    bool findAndRepleaceInFile(string filename, char* findMe, char* replaceMe);
    bool findAndRepleaceInDirWithIgnore(const char* dir, char* findMe, char* replaceMe, char* ignore[], int ignoreCount);
    bool findAndRepleaceInDirWithInclude(const char* dir, char* findMe, char* replaceMe, char* include[], int includeCount);
    bool findAndRepleaceInDirWithIgnoreRecursion(const char* dir, char *findMe, char *replaceMe, char* ignore[], int ignoreCount);
    bool copyFilesToNewDirWithIgnore(const char* oldDir, const char* newDir, char* ignore[], int ignoreCount);
    bool copyFilesToNewDirWithInclude(const char* oldDir, const char* newDir, char* include[], int includeCount);
    bool copyFilesToNewDirWithIncludeDir(const char* oldDir, const char* newDir, char* includeDir[], int includeDirCount, char* includeFiles[], int includeFilesCount);
    bool copyFilesToNewDirWithRefDir(const char* oldDir, const char* newDir, const char* refDir, char* include[], int includeCount);
    bool copyFilesToNewDirWithIgnoreRefDirs(const char* oldDir, char* refDir[],int refDirCount, const char* newDir, char* ignore[], int IgnoreCount);
    bool copyFilesToNewDirWithIgnoreRecursion(const char* oldDir, const char* newDir, char* ignore[], int ignoreCount);
    bool copyFileFolderToNewDir(const char* oldDir, const char* newDir);
    void load_file(std::string& s, std::istream& is);
    int searchWithKey(const string str, char* e[], int eCount);
    int searchWithKeyAndRefDir(const char* refDir, string str);
    bool renameFileInDir(const char* dir, char* find[], string name);
    void readFileLineByLineToCout(string filename);
protected:
private:

};

#endif /* FileWork_hpp */
