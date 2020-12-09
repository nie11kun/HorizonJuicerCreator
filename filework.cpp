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

namespace fs = boost::filesystem;
using namespace std;

int lngIn;

FileWork::FileWork()
{

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
