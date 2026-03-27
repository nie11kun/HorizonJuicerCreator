/**
 * @file horizonjuicercreator.hpp
 * @brief Main application window header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef HORIZONJUICERCREATOR_HPP
#define HORIZONJUICERCREATOR_HPP

#include <QMainWindow>

#include "about.hpp"
#include "creatorwindow.hpp"
#include "history.hpp"
#include "readandwritejson.hpp"
#include "removecommitwindow.hpp"
#include "setting.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class HorizonJuicerCreator;
}
QT_END_NAMESPACE

/**
 * @class HorizonJuicerCreator
 * @brief Main application window for HorizonJuicerCreator
 *
 * Provides the main menu with options to create new machine programs
 * or remove comments from existing programs.
 */
class HorizonJuicerCreator : public QMainWindow {
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param parent Parent widget
   */
  HorizonJuicerCreator(QWidget *parent = nullptr);

  /**
   * @brief Destructor
   */
  ~HorizonJuicerCreator();

private slots:
  void on_creatNewMachineButton_clicked();
  void on_removeCommitsButton_clicked();
  void on_actionSettings_triggered();
  void on_actionAbout_triggered();
  void on_actionHistory_triggered();
  void showWindow();

private:
  Ui::HorizonJuicerCreator *ui;           ///< UI pointer
  CreatorWindow *creatorWindow;           ///< Machine program creator window
  RemoveCommitWindow *removeCommitWindow; ///< Comment removal window
  Setting *settingDialog;                 ///< Settings dialog
  About *aboutDialog;                     ///< About dialog
  History *historyDialog;                 ///< History dialog
  ReadAndWriteJson *jsonHandler;          ///< JSON configuration handler

  QString version = "3.25.0"; ///< Current application version

  /**
   * @brief Initialize or update version in configuration
   */
  void setVersion();
};

#endif // HORIZONJUICERCREATOR_HPP
