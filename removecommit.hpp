/**
 * @file removecommit.hpp
 * @brief Comment removal process handler header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef REMOVECOMMIT_HPP
#define REMOVECOMMIT_HPP

#include <QObject>

#include "convertcode.hpp"
#include "filework.hpp"
#include "readandwritejson.hpp"

/**
 * @class RemoveCommit
 * @brief Worker class for removing comments from CNC program files
 *
 * This class processes CNC program files (COM, SPF, MPF) and removes
 * comment lines. It runs in a separate thread to avoid blocking the UI.
 */
class RemoveCommit : public QObject {
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param parent Parent QObject
   */
  explicit RemoveCommit(QObject *parent = nullptr);

  /**
   * @brief Destructor
   */
  ~RemoveCommit();

public slots:
  /**
   * @brief Start the comment removal process
   */
  void startProcess();

signals:
  /**
   * @brief Emitted when processing starts
   */
  void triggerStartingProcess();

  /**
   * @brief Emitted when processing completes
   */
  void triggerFinishedProcess();

private:
  FileWork *fileHandler;         ///< File operations handler
  ReadAndWriteJson *jsonHandler; ///< JSON configuration handler
  ConvertCode *converter;        ///< Character encoding converter
};

#endif // REMOVECOMMIT_HPP
