/**
 * @file readandwritejson.hpp
 * @brief JSON configuration read/write utilities header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef READANDWRITEJSON_HPP
#define READANDWRITEJSON_HPP

#include <QDir>
#include <QJsonObject>
#include <QString>

#include "convertcode.hpp"

/**
 * @class ReadAndWriteJson
 * @brief Utility class for reading and writing application configuration
 *
 * Manages the application's JSON configuration file stored in the user's home
 * directory.
 */
class ReadAndWriteJson {
public:
  ReadAndWriteJson();
  ~ReadAndWriteJson();

  QString filePath; ///< Full path to the configuration file

  /**
   * @brief Read JSON configuration file to QJsonObject
   * @return Configuration as QJsonObject
   */
  QJsonObject readJsonToObj();

  /**
   * @brief Save QJsonObject to JSON configuration file
   * @param obj Configuration object to save
   */
  void saveObjToJson(QJsonObject obj);

  /**
   * @brief Get source directory from configuration
   * @return Source directory path
   */
  QString getSourceDir();

  /**
   * @brief Get destination directory from configuration
   * @return Destination directory path
   */
  QString getDestDir();

  /**
   * @brief Get application version from configuration
   * @return Version string
   */
  QString getVersionInfo();

  /**
   * @brief Set source and destination directories
   * @param sourceDir Source directory path
   * @param destDir Destination directory path
   */
  void setDirs(QString sourceDir, QString destDir);

  /**
   * @brief Get directory for comment removal operation
   * @return Directory path
   */
  QString getRemoveDir();

private:
  ConvertCode *converter; ///< Character encoding converter
  QString fileName = "HorizonJuicerCreator.json"; ///< Configuration filename

#ifdef _WIN32
  QString pathSeparator = "\\";
#else
  QString pathSeparator = "/";
#endif
};

#endif // READANDWRITEJSON_HPP
