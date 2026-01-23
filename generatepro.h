/**
 * @file generatepro.h
 * @brief Program generation worker class header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef GENERATEPRO_H
#define GENERATEPRO_H

#include <QObject>

#include <string>

#include "convertcode.hpp"
#include "filework.hpp"
#include "readandwritejson.hpp"

/**
 * @class GeneratePro
 * @brief Worker class for generating CNC machine programs
 *
 * This class handles the generation of machine programs based on
 * configuration settings. It runs in a separate thread to avoid
 * blocking the UI.
 */
class GeneratePro : public QObject {
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param parent Parent QObject
   */
  explicit GeneratePro(QObject *parent = nullptr);

  /**
   * @brief Destructor
   */
  ~GeneratePro();

public slots:
  /**
   * @brief Start the program generation process
   */
  void startGenerate();

  /**
   * @brief Load configuration values from JSON
   */
  void getJsonValue();

  /**
   * @brief Get replacement JSON string for variable substitution
   * @return JSON string for replacements
   */
  std::string getReplaceJsonValue();

  /**
   * @brief Test function for debugging
   */
  void test();

signals:
  /**
   * @brief Emitted when generation starts
   */
  void triggerStartingProcess();

  /**
   * @brief Emitted when generation completes
   */
  void triggerFinishedProcess();

private:
  ConvertCode *converter;        ///< Character encoding converter
  ReadAndWriteJson *jsonHandler; ///< JSON configuration handler
  FileWork *fileHandler;         ///< File operations handler

  // Build information
  std::string debugDate;         ///< Debug date string
  std::string specificationInfo; ///< Machine specification info
  std::string softwareVersion;   ///< Software version string

  // Directory paths
  std::string sourceDir; ///< Source directory path
  std::string destDir;   ///< Destination directory path

  // Machine information
  std::string machineName;    ///< Machine name (e.g., "SK7120A")
  std::string machineNameLng; ///< Machine name localized (e.g., "数控螺纹磨床")
  std::string machineIndex;   ///< Machine index number
  std::string customInfo;     ///< Custom information field
  int lng;                    ///< Language index

  // Machine configuration flags
  int machineType;          ///< Machine type (0=external, 1=internal)
  int wareType;             ///< Workpiece type
  int ifOperation;          ///< Operation mode flag
  int ifCenter;             ///< Center mode flag
  int ifHasU;               ///< Has U-axis flag
  int ifNotHasUExternalPos; ///< External position without U flag
  int measureMethord;       ///< Measurement method index
  int probePos;             ///< Probe position index
  int wheelType;            ///< Wheel type index
  int shapeType;            ///< Shape type index
  int ifHasA;               ///< Has A-axis flag
  int grindWheelType;       ///< Grind wheel type
  int exGrindWheelType;     ///< External grind wheel type
  int dressWheelType;       ///< Dress wheel type
  int ifRemoveComments;     ///< Remove comments flag
  int ifHasReOp;            ///< Has re-operation flag
  int ifHasScrewTap;        ///< Has screw tap flag
  int ifHasWorm;            ///< Has worm flag
  int hmiMode;              ///< HMI mode index
  int systemMode;           ///< System mode (0=standard, 1=one)
  int ifHasLoadingArm;      ///< Has loading arm flag
  int ifHasEncryption;      ///< Has encryption flag
};

#endif // GENERATEPRO_H
