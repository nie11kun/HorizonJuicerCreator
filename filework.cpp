//
//  FileWork.cpp
//  BoostTest
//
//  Created by Marco Nie on 2018/5/18.
//  Copyright © 2018 Marco Nie. All rights reserved.
//


#ifndef BOOST_FILESYSTEM_NO_DEPRECATED
#  define BOOST_FILESYSTEM_NO_DEPRECATED
#endif
#ifndef BOOST_SYSTEM_NO_DEPRECATED
#  define BOOST_SYSTEM_NO_DEPRECATED
#endif


#include "filework.hpp"
#include <fstream>
#include "boost/regex.hpp"
#include <string>
#include "boost/filesystem.hpp"
#include "boost/progress.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <QString>
#include <QStringList>
#include <QImage>

namespace fs = boost::filesystem;
using namespace std;
namespace pt = boost::property_tree;

int lngIn;

FileWork::FileWork()
{

}

// 转义所有正则表达式的特殊字符
std::string escapeRegex(const std::string &s) {
    const std::string specialChars = ".^$|()[]*+?{}\\";
    std::string result;
    for (char c : s) {
        if (specialChars.find(c) != std::string::npos) {
            result.push_back('\\');
        }
        result.push_back(c);
    }
    return result;
}

bool FileWork::findAndReplaceInString(string &in, const char* find, const char* replace)
{
    boost::regex e;
    e.assign(find);
    std::ostringstream t(std::ios::out | std::ios::binary);
    std::ostream_iterator<char, char> oi(t);
    boost::regex_replace(oi, in.begin(), in.end(),
        e, replace, boost::match_default | boost::format_all);

    in = t.str();

    return 0;
}

bool FileWork::findAndRepleaceInFile(string filename, const char* findMe, const char* replaceMe)
{
    boost::regex e;

    try {
        e.assign(findMe);
        std::cout << "find in file: " << filename << std::endl;
        std::ifstream fs(filename);
        std::string in;
        load_file(in, fs);
        fs.close();
        std::string out_name(filename + std::string(".tmp"));
        std::ofstream os(out_name.c_str());
        std::ostream_iterator<char, char> out(os);
        boost::regex_replace(out, in.begin(), in.end(),
            e, replaceMe, boost::match_default | boost::format_all);
        os.close();
        if (std::remove(filename.c_str()) != 0)
        {
            std::cout << "error when removing file!\n" << std::endl;
        }
        if (std::rename(out_name.c_str(), filename.c_str()) != 0)
        {
            std::cout << "error when renaming file!\n" << std::endl;
        }
    }
    catch (...)
    {
        std::cout << "error when replace string!\n" << std::endl;
        return 1;

    }
    return 0;
}

bool FileWork::findAndReplaceFromJSONWithIgnore(const char* dir, const char* jsonData, const char* ignore[], int ignoreCount)
{
    // 解析JSON并创建替换映射
    std::map<std::string, std::string> replacements;
    std::istringstream jsonStream(jsonData);
    pt::ptree root;

    if (jsonData == nullptr || strlen(jsonData) == 0) {
        std::cerr << "error ：jsonData is null" << std::endl;
        return false;
    }

    try {
        pt::read_json(jsonStream, root);
        for (const auto& pair : root) {
            // 如果键名为空，直接跳过
            if (pair.first.empty()) {
                continue;
            }
            replacements[pair.first] = pair.second.get_value<std::string>();
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "JSON parse error: " << ex.what() << std::endl;
        return false;
    }

    fs::path p = fs::system_complete(dir);

    if (!fs::exists(p)) {
        std::cout << "\nsource dir error: " << p << std::endl;
        return false;
    }

    if (fs::is_directory(p)) {
        std::cout << "\nin dir: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p); dir_itr != end_iter; ++dir_itr) {
            try {
                if (fs::is_directory(dir_itr->status())) {
                    // 如果需要可以处理子目录
                    this->findAndReplaceFromJSONWithIgnore(dir_itr->path().string().c_str(), jsonData, ignore, ignoreCount);
                }
                else if (fs::is_regular_file(dir_itr->status())) {
                    if (ignore == NULL || searchWithKey(dir_itr->path().filename().string(), ignore, ignoreCount) == 0) {
                        // 使用所有替换处理文件
                        findAndReplaceMultipleInFile(dir_itr->path().string(), replacements);
                    }
                    else {
                        cout << "******ignored file: " << dir_itr->path().filename().string() << endl;
                    }
                }
                else {
                    std::cout << dir_itr->path().filename() << " [others]\n";
                }
            }
            catch (const std::exception& ex) {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else { // 必须是文件
        std::cout << "\nfinding file: " << p << "\n";
        findAndReplaceMultipleInFile(p.string(), replacements);
    }

    return true;
}

bool FileWork::findAndReplaceMultipleInFile(const std::string& filePath, const std::map<std::string, std::string>& replacements)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "open file error: " << filePath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string content = buffer.str();
    std::string original = content;

    // 对每个要替换的字符串进行转义，然后执行替换
    for (const auto& pair : replacements) {
        // 使用自定义的 escapeRegex 函数进行转义
        std::string escapedPattern = escapeRegex(pair.first);
        boost::regex pattern(escapedPattern);
        content = boost::regex_replace(content, pattern, pair.second);
    }

    // 如果内容发生变化，则写回文件
    if (content != original) {
        std::ofstream outFile(filePath);
        if (!outFile.is_open()) {
            std::cerr << "writing file error: " << filePath << std::endl;
            return false;
        }

        outFile << content;
        outFile.close();
        std::cout << "updating file: " << filePath << std::endl;
    }

    return true;
}

bool FileWork::findAndRepleaceInDirWithIgnore(const char* dir, const char *findMe, const char *replaceMe, const char* ignore[], int ignoreCount)
{
    fs::path p = fs::system_complete(dir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    //this->findAndRepleaceInDir(dirNow, findMe, replaceMe, fileEx, iCount);
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (ignore == NULL || searchWithKey(dir_itr->path().filename().string(), ignore, ignoreCount) == 0)
                    {
                        findAndRepleaceInFile(dir_itr->path().string(), findMe, replaceMe);
                    }
                    else {
                        cout << "******ignored file: " << dir_itr->path().filename().string() << endl;
                    }
                }
                else
                {
                    std::cout << dir_itr->path().filename() << " [other]\n";
                }

            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        findAndRepleaceInFile(p.string(), findMe, replaceMe);
    }

    return 0;
}

bool FileWork::findAndRepleaceInDirWithInclude(const char* dir, const char *findMe, const char *replaceMe, const char* include[], int includeCount)
{
    fs::path p = fs::system_complete(dir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {

                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (include == NULL || searchWithKey(dir_itr->path().filename().string(), include, includeCount) == 1)
                    {
                        findAndRepleaceInFile(dir_itr->path().string(), findMe, replaceMe);
                    }
                    else {
                        cout << "******ignored file: " << dir_itr->path().filename().string() << endl;
                    }
                }
                else
                {
                    std::cout << dir_itr->path().filename() << " [other]\n";
                }

            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        findAndRepleaceInFile(p.string(), findMe, replaceMe);
    }

    return 0;
}

bool FileWork::findAndRepleaceInDirWithIgnoreRecursion(const char* dir, const char *findMe, const char *replaceMe, const char* ignore[], int ignoreCount)
{
    fs::path p = fs::system_complete(dir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    string dirNow = dir_itr->path().string();
                    const char* c_dirNow = dirNow.c_str();
                    this->findAndRepleaceInDirWithIgnoreRecursion(c_dirNow, findMe, replaceMe, ignore, ignoreCount);
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (ignore == NULL || searchWithKey(dir_itr->path().filename().string(), ignore, ignoreCount) == 0)
                    {
                        findAndRepleaceInFile(dir_itr->path().string(), findMe, replaceMe);
                    }
                    else {
                        cout << "******ignored file: " << dir_itr->path().filename().string() << endl;
                    }
                }
                else
                {
                    std::cout << dir_itr->path().filename() << " [other]\n";
                }

            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else // must be a file
    {
        std::cout << "\nFound file: " << p << "\n";
        findAndRepleaceInFile(p.string(), findMe, replaceMe);
    }

    return 0;
}

bool FileWork::findAndRepleaceInDirWithIncludeRecursion(const char* dir, const char *findMe, const char *replaceMe, const char* include[], int includeCount)
{
    fs::path p = fs::system_complete(dir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    string dirNow = dir_itr->path().string();
                    const char* c_dirNow = dirNow.c_str();
                    this->findAndRepleaceInDirWithIncludeRecursion(c_dirNow, findMe, replaceMe, include, includeCount);
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (include == NULL || searchWithKey(dir_itr->path().filename().string(), include, includeCount) == 1)
                    {
                        findAndRepleaceInFile(dir_itr->path().string(), findMe, replaceMe);
                    }
                    else {
                        cout << "******ignored file: " << dir_itr->path().filename().string() << endl;
                    }
                }
                else
                {
                    std::cout << dir_itr->path().filename() << " [other]\n";
                }

            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else // must be a file
    {
        std::cout << "\nFound file: " << p << "\n";
        findAndRepleaceInFile(p.string(), findMe, replaceMe);
    }

    return 0;
}

bool FileWork::copyFilesToNewDirWithIgnore(const char* oldDir, const char* newDir, const char* ignore[], int ignoreCount)
{
    fs::path p = fs::system_complete(oldDir);
    fs::path np = fs::system_complete(newDir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    fs::create_directory(np);

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    //this->copyFilesToNewDir(dirNow, newDir, ignore, iCount);
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (ignore == NULL || searchWithKey(dir_itr->path().string(), ignore, ignoreCount) == 0)
                    {

                        fs::path newDic = np;
                        newDic += seg + dir_itr->path().filename().string();

                        if (fs::is_regular_file(newDic))
                        {
                            fs::remove(newDic);
                        }
                        fs::copy_file(*dir_itr, newDic);
                        std::cout << "copied file: " << dir_itr->path().filename().string() << endl;
                    }
                    else {
                        cout << "******ignored file: " << dir_itr->path().filename().string() << endl;
                    }
                }
            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }

    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        return 1;
    }

    return 0;
}

bool FileWork::copyFilesToNewDirWithInclude(const char* oldDir, const char* newDir, const char* include[], int includeCount)
{
    fs::path p = fs::system_complete(oldDir);
    fs::path np = fs::system_complete(newDir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    fs::create_directory(np);

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {

                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (include == NULL || searchWithKey(dir_itr->path().string(), include, includeCount) == 1)
                    {

                        fs::path newDic = np;
                        newDic += seg + dir_itr->path().filename().string();

                        if (fs::is_regular_file(newDic))
                        {
                            fs::remove(newDic);
                        }
                        fs::copy_file(*dir_itr, newDic);
                        std::cout << "copied file: " << dir_itr->path().filename().string() << endl;
                    }
                    else {
                        cout << "******ignored file: " << dir_itr->path().filename().string() << endl;
                    }
                }
            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }

    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        return 1;
    }

    return 0;
}

bool FileWork::copyFilesToNewDirWithIncludeDir(const char* oldDir, const char* newDir, const char* includeDir[], int includeDirCount, const char* includeFiles[], int includeFilesCount)
{
    fs::path p = fs::system_complete(oldDir);
    fs::path np = fs::system_complete(newDir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    fs::create_directory(np);

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    if (includeDir == NULL || searchWithKey(dir_itr->path().string(), includeDir, includeDirCount) == 1)
                    {
                        string dirNow = dir_itr->path().string();
                        string slng;
                        if (lngIn == 0)
                        {
                            slng = seg + "chs";
                        }
                        else
                        {
                            slng = seg + "eng";
                        }
                        dirNow = dirNow + slng;
                        const char* c_dirNow = dirNow.c_str();
                        this->copyFilesToNewDirWithIncludeDir(c_dirNow, newDir, includeDir, includeDirCount, includeFiles, includeFilesCount);
                    }
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (includeFiles == NULL || searchWithKey(dir_itr->path().string(), includeFiles, includeFilesCount) == 1)
                    {
                        fs::path newDic = np;
                        newDic += seg + dir_itr->path().filename().string();

                        if (fs::is_regular_file(newDic))
                        {
                            fs::remove(newDic);
                        }
                        fs::copy_file(*dir_itr, newDic);
                        std::cout << "copied file: " << dir_itr->path().filename().string() << endl;
                    }
                }
            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }

    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        return 1;
    }

    return 0;
}

bool FileWork::copyFilesToNewDirWithRefDir(const char* oldDir, const char* newDir, const char* refDir, const char* include[], int includeCount)
{
    fs::path p = fs::system_complete(oldDir);
    fs::path np = fs::system_complete(newDir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    fs::create_directory(np);

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    string dirNow = dir_itr->path().string();
                    if (searchWithKeyAndRefDir(refDir, dirNow))
                    {
                        string slng;
                        if (lngIn == 0)
                        {
                            slng = seg + "chs";
                        }
                        else
                        {
                            slng = seg + "eng";
                        }
                        dirNow = dirNow + slng;
                        const char* oldDIrChs = dirNow.c_str();
                        copyFilesToNewDirWithInclude(oldDIrChs, newDir, include, includeCount);
                    }
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    fs::path newDic = np;
                    newDic += seg + dir_itr->path().filename().string();

                    if (fs::is_regular_file(newDic))
                    {
                        fs::remove(newDic);
                    }
                    fs::copy_file(*dir_itr, newDic);
                    std::cout << "copied file: " << dir_itr->path().filename().string() << endl;
                }
            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        return 1;
    }

    return 0;
}

bool FileWork::copyFilesToNewDirWithIgnoreRefDirs(const char* oldDir, const char* refDir[], int refDirCount, const char* newDir, const char* ignore[], int ignoreCount)
{
    fs::path p = fs::system_complete(oldDir);
    fs::path np = fs::system_complete(newDir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    fs::create_directory(np);

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    if (refDir != NULL && searchWithKey(dir_itr->path().string(), refDir, refDirCount) == 1)
                    {
                        string dirNow = dir_itr->path().string();
                        const char* c_dirNow = dirNow.c_str();
                        this->copyFilesToNewDirWithIgnore(c_dirNow, newDir, ignore, ignoreCount);
                    }
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (ignore == NULL || searchWithKey(dir_itr->path().string(), ignore, ignoreCount) == 0)
                    {

                        fs::path newDic = np;
                        newDic += seg + dir_itr->path().filename().string();

                        if (fs::is_regular_file(newDic))
                        {
                            fs::remove(newDic);
                        }
                        //cout << dir_itr->path().string() << "   " << newDic.string();

                        fs::copy_file(*dir_itr, newDic);
                        std::cout << "copied file: " << dir_itr->path().filename().string() << std::endl;
                    }
                    else {
                        cout << "******ignored file: " << dir_itr->path().filename().string() << endl;
                    }
                }
            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }

    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        return 1;
    }

    return 0;
}

bool FileWork::copyFilesToNewDirWithIgnoreRecursion(const char* oldDir, const char* newDir, const char* ignore[], int ignoreCount)
{
    fs::path p = fs::system_complete(oldDir);
    fs::path np = fs::system_complete(newDir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    fs::create_directory(np);

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    string dirNow = dir_itr->path().string();
                    const char* c_dirNow = dirNow.c_str();
                    this->copyFilesToNewDirWithIgnore(c_dirNow, newDir, ignore, ignoreCount);
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (ignore == NULL || searchWithKey(dir_itr->path().string(), ignore, ignoreCount) == 0)
                    {

                        fs::path newDic = np;
                        newDic += seg + dir_itr->path().filename().string();

                        if (fs::is_regular_file(newDic))
                        {
                            fs::remove(newDic);
                        }
                        fs::copy_file(*dir_itr, newDic);
                        std::cout << "copied file: " << dir_itr->path().filename().string() << std::endl;
                    }
                    else {
                        cout << "******ignored file: " << dir_itr->path().filename().string() << endl;
                    }
                }
            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }

    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        return 1;
    }

    return 0;
}

bool FileWork::copyFileFolderToNewDir(const char* oldDir, const char* newDir)
{
    fs::path p = fs::system_complete(oldDir);
    fs::path np = fs::system_complete(newDir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    fs::create_directory(np);

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    string s_childDir = newDir;
                    s_childDir += seg + dir_itr->path().filename().string();
                    const char* c_childDir = s_childDir.c_str();

                    string s_p = oldDir;
                    s_p += seg + dir_itr->path().filename().string();
                    const char* c_p = s_p.c_str();

                    copyFileFolderToNewDir(c_p, c_childDir);
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    fs::path newDic = np;
                    newDic += seg + dir_itr->path().filename().string();

                    if (fs::is_regular_file(newDic))
                    {
                        fs::remove(newDic);
                    }
                    fs::copy_file(*dir_itr, newDic);
                    std::cout << "copied file: " << dir_itr->path().filename().string() << std::endl;

                }
            }
            catch(const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        return 1;
    }

    return 0;
}

void FileWork::load_file(std::string& s, std::istream& is)
{
    s.erase();
    s.reserve(is.rdbuf()->in_avail());
    char c;
    while (is.get(c))
    {
        if (s.capacity() == s.size())
            s.reserve(s.capacity() * 3);
        s.append(1, c);
    }
}

int FileWork::searchWithKey(const string str, const char* e[],  int eCount)
{
    if (e == NULL)
    {
        return -1;
    }

    boost::regex re;
    boost::match_results<std::string::const_iterator> out;
    std::string::const_iterator start, end;
    start = str.begin();
    end = str.end();
    boost::match_flag_type flags = boost::match_default;

    for (int i = 0; i < eCount; i++)
    {
        //cout << sizeof(e) << "   " << sizeof(e[0]) << "\n\n";
        re.assign(e[i]);
        boost::regex_search(start, end, out, re, flags);
        if (out[0].matched == true)
        {
            cout << "******matched string: " << out[0].str() << endl;
            return 1;//found
        }
    }

    //cout << "not ignored file: " << str << endl;
    return 0;
}

int FileWork::searchWithKeyAndRefDir(const char* refDir, string str)
{
    rsize_t found = str.find_last_of(seg);
    string name = str.substr(found + 1);
    string boundaryName = name.append("[^\\d]");

    cout << "\n******folder name is: " << name << endl;

    const char* eFind[] = { (char*)boundaryName.c_str() };

    fs::path p = fs::system_complete(refDir);

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {

                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    string dirNow = dir_itr->path().string();
                    std::ifstream fs(dirNow);
                    std::string in;
                    load_file(in, fs);
                    fs.close();
                    if (searchWithKey(in, eFind, 1))
                    {
                        return 1;//matched
                    }
                }
            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    return 0;
}

bool FileWork::renameFileInDir(const char* dir, const char* find[], string name)
{
    fs::path p = fs::system_complete(dir);
    fs::path np = p;
    np += seg + name + "\.MPF";

    if (!fs::exists(p))
    {
        std::cout << "\nsource directory error: " << p << std::endl;
        return 1;
    }

    if (fs::is_directory(p))
    {
        std::cout << "\nIn directory: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p);
            dir_itr != end_iter;
            ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {

                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    if (find != NULL && searchWithKey(dir_itr->path().string(), find, 1) == 1)
                    {
                        string dirNow = dir_itr->path().string();

                        if (fs::exists(np))
                        {
                            if (std::remove(np.string().c_str()) != 0)
                            {
                                std::cout << "error when removing existing file!\n" << std::endl;
                            }
                        }

                        if (std::rename(dirNow.c_str(), np.string().c_str()) != 0)
                        {
                            std::cout << "error when renaming file!\n" << std::endl;
                        }
                        else
                        {
                            std::cout << "renamed done.\n" << std::endl;
                        }
                    }
                }
            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else // must be a file
    {
        std::cout << "\nFound: " << p << "\n";
        return 1;
    }

    return 0;
}

void FileWork::readFileLineByLineToCout(string filename)
{
    string line;
    std::fstream fs(filename);
    while (getline(fs, line))
    {
        cout << line << endl;
    }
    fs.close();
}

bool FileWork::resizeImageFile(const std::string &filePath, int targetWidth, int targetHeight)
{
    QImage image;
    // 尝试加载图片
    if (!image.load(QString::fromStdString(filePath))) {
        std::cout << "loading picture error: " << filePath << std::endl;
        return false;
    }
    // 使用 scaled() 调整图片尺寸，此处设置为忽略宽高比（可根据需要选择 Qt::KeepAspectRatio）
    QImage newImage = image.scaled(targetWidth, targetHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // 保存图片到原路径（也可以保存为新文件）
    if (!newImage.save(QString::fromStdString(filePath))) {
        std::cout << "saving picture error: " << filePath << std::endl;
        return false;
    }
    return true;
}

bool FileWork::resizeImageInDirWithInclude(const char* dir, const char* resolution, const char* include[], int includeCount)
{
    // 获取目录的完整路径
    fs::path p = fs::system_complete(dir);
    if (!fs::exists(p))
    {
        std::cout << "\nwrong dir: " << p << std::endl;
        return false;
    }

    // 解析目标分辨率字符串，例如 "1170*595"
    QString resStr = QString::fromUtf8(resolution);
    QStringList resList = resStr.split('*');
    if (resList.size() != 2)
    {
        std::cout << "resolution format invaild: " << resolution << std::endl;
        return false;
    }
    int targetWidth = resList[0].toInt();
    int targetHeight = resList[1].toInt();

    // 如果是目录，则遍历目录中的所有文件
    if (fs::is_directory(p))
    {
        std::cout << "\nprocessing dir: " << p << "\n\n";
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(p); dir_itr != end_iter; ++dir_itr)
        {
            try
            {
                if (fs::is_directory(dir_itr->status()))
                {
                    // 如果需要可递归处理子目录
                }
                else if (fs::is_regular_file(dir_itr->status()))
                {
                    // 根据 include 参数判断是否需要处理该文件
                    if (include == NULL || searchWithKey(dir_itr->path().filename().string(), include, includeCount) == 1)
                    {
                        if (!resizeImageFile(dir_itr->path().string(), targetWidth, targetHeight))
                        {
                            std::cout << "resizing error: " << dir_itr->path().filename().string() << std::endl;
                        }
                    }
                    else {
                        std::cout << "******ignored: " << dir_itr->path().filename().string() << std::endl;
                    }
                }
                else
                {
                    std::cout << dir_itr->path().filename() << " [others]\n";
                }
            }
            catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else // 如果 p 不是目录，而是单个文件
    {
        std::cout << "\nfinding file: " << p << "\n";
        if (!resizeImageFile(p.string(), targetWidth, targetHeight))
        {
            std::cout << "resizing error: " << p.string() << std::endl;
        }
    }
    return true;
}
