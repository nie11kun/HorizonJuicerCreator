/**
 * @file creatorwindow.hpp
 * @brief Machine program creator window header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef CREATORWINDOW_HPP
#define CREATORWINDOW_HPP

#include <QThread>
#include <QWidget>

#include "convertcode.hpp"
#include "generatepro.h"
#include "readandwritejson.hpp"
#include "setting.hpp"

namespace Ui {
class CreatorWindow;
}

/**
 * @class CreatorWindow
 * @brief Widget for configuring and generating machine programs
 *
 * Provides a user interface for configuring machine parameters
 * and generating CNC program files.
 */
class CreatorWindow : public QWidget {
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param parent Parent widget
   */
  explicit CreatorWindow(QWidget *parent = nullptr);

  /**
   * @brief Destructor
   */
  ~CreatorWindow();

private slots:
  int on_saveDataPushButton_clicked();
  void on_comboBoxMachineType_currentIndexChanged(int index);
  void on_comboBoxWareType_currentIndexChanged(int index);
  void on_comboBoxIfOperation_currentIndexChanged(int index);
  void on_comboBoxIfCenter_currentIndexChanged(int index);
  void on_creatPushButton_clicked();
  void startingProcess();
  void finishedProcess();
  void on_comboBoxIfHasU_currentIndexChanged(int index);
  void on_comboBoxMeasureMethord_currentIndexChanged(int index);
  void on_backButton_clicked();

signals:
  void triggerProcess();
  void triggerBackToMain();

private:
  Ui::CreatorWindow *ui;         ///< UI pointer
  Setting *settingDialog;        ///< Settings dialog
  GeneratePro *generator;        ///< Program generator worker
  QThread *workerThread;         ///< Worker thread
  ReadAndWriteJson *jsonHandler; ///< JSON configuration handler
  ConvertCode *converter;        ///< Character encoding converter

  void getMachineInfo();
  void loadComboBoxSet();
  void machineTypeComboBoxSet(int index);
  void wareTypeComboBoxSet(int index);
  void operationComboBoxSet(int index);
  void probePosSet(int index);
  void centerSet(int index);
  void centerExternalSet(int index);
};

#endif // CREATORWINDOW_HPP
