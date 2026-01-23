/**
 * @file removecommitwindow.hpp
 * @brief Comment removal window widget header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef REMOVECOMMITWINDOW_HPP
#define REMOVECOMMITWINDOW_HPP

#include <QThread>
#include <QWidget>

#include "convertcode.hpp"
#include "readandwritejson.hpp"
#include "removecommit.hpp"

namespace Ui {
class RemoveCommitWindow;
}

/**
 * @class RemoveCommitWindow
 * @brief Widget for removing comments from CNC program files
 *
 * Provides a user interface for selecting a directory and removing
 * comment lines from CNC program files (COM, SPF, MPF).
 */
class RemoveCommitWindow : public QWidget {
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param parent Parent widget
   */
  explicit RemoveCommitWindow(QWidget *parent = nullptr);

  /**
   * @brief Destructor
   */
  ~RemoveCommitWindow();

private slots:
  void on_pushButtonDir_clicked();
  void on_pushButtonStart_clicked();
  void on_pushButtonCancel_clicked();
  void startingProcess();
  void finishedProcess();

signals:
  void triggerProcess();
  void triggerBackToMain();

private:
  Ui::RemoveCommitWindow *ui;    ///< UI pointer
  RemoveCommit *removeWorker;    ///< Worker for comment removal
  QThread *workerThread;         ///< Worker thread
  ReadAndWriteJson *jsonHandler; ///< JSON configuration handler
  ConvertCode *converter;        ///< Character encoding converter

  /**
   * @brief Load directory from configuration
   */
  void loadDir();
};

#endif // REMOVECOMMITWINDOW_HPP
