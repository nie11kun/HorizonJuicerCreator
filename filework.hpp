/**
 * @file filework.hpp
 * @brief File operation utilities header
 * @author Marco Nie
 * @date 2018/5/18
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef FILEWORK_HPP
#define FILEWORK_HPP

#include <map>
#include <string>

/**
 * @class FileWork
 * @brief Utility class for file and directory operations
 *
 * Provides methods for:
 * - Find and replace operations in files and directories
 * - Copying files with include/ignore filters
 * - File searching and renaming
 * - Image resizing operations
 */
class FileWork {
public:
  FileWork();

  int lngIn; ///< Language index for operations

  // String and file replacement operations
  bool findAndReplaceInString(std::string &in, const char *find,
                              const char *replace);
  bool findAndRepleaceInFile(std::string filename, const char *findMe,
                             const char *replaceMe);
  bool findAndReplaceFromJSONWithIgnore(const char *dir, const char *jsonData,
                                        const char *ignore[], int ignoreCount);
  bool findAndReplaceMultipleInFile(
      const std::string &filePath,
      const std::map<std::string, std::string> &replacements);

  // Directory replacement operations
  bool findAndRepleaceInDirWithIgnore(const char *dir, const char *findMe,
                                      const char *replaceMe,
                                      const char *ignore[], int ignoreCount);
  bool findAndRepleaceInDirWithInclude(const char *dir, const char *findMe,
                                       const char *replaceMe,
                                       const char *include[], int includeCount);
  bool findAndRepleaceInDirWithIgnoreRecursion(const char *dir,
                                               const char *findMe,
                                               const char *replaceMe,
                                               const char *ignore[],
                                               int ignoreCount);
  bool findAndRepleaceInDirWithIncludeRecursion(const char *dir,
                                                const char *findMe,
                                                const char *replaceMe,
                                                const char *include[],
                                                int includeCount);

  // File copy operations
  bool copyFilesToNewDirWithIgnore(const char *oldDir, const char *newDir,
                                   const char *ignore[], int ignoreCount);
  bool copyFilesToNewDirWithInclude(const char *oldDir, const char *newDir,
                                    const char *include[], int includeCount);
  bool copyFilesToNewDirWithIncludeDir(const char *oldDir, const char *newDir,
                                       const char *includeDir[],
                                       int includeDirCount,
                                       const char *includeFiles[],
                                       int includeFilesCount);
  bool copyFilesToNewDirWithRefDir(const char *oldDir, const char *newDir,
                                   const char *refDir, const char *include[],
                                   int includeCount);
  bool copyFilesToNewDirWithIgnoreRefDirs(const char *oldDir,
                                          const char *refDir[], int refDirCount,
                                          const char *newDir,
                                          const char *ignore[],
                                          int ignoreCount);
  bool copyFilesToNewDirWithIgnoreRecursion(const char *oldDir,
                                            const char *newDir,
                                            const char *ignore[],
                                            int ignoreCount);
  bool copyFileFolderToNewDir(const char *oldDir, const char *newDir);

  // Utility operations
  void load_file(std::string &s, std::istream &is);
  int searchWithKey(const std::string str, const char *e[], int eCount);
  int searchWithKeyAndRefDir(const char *refDir, std::string str);
  bool renameFileInDir(const char *dir, const char *find[], std::string name);
  void readFileLineByLineToCout(std::string filename);

  // Image operations
  bool resizeImageFile(const std::string &filePath, int targetWidth,
                       int targetHeight);
  bool resizeImageInDirWithInclude(const char *dir, const char *resolution,
                                   const char *include[], int includeCount);

private:
#ifdef _WIN32
  std::string pathSeparator = "\\";
#else
  std::string pathSeparator = "/";
#endif
};

#endif // FILEWORK_HPP
