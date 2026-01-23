/**
 * @file setting.hpp
 * @brief Settings dialog widget header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef SETTING_HPP
#define SETTING_HPP

#include <QWidget>

#include "readandwritejson.hpp"

namespace Ui {
class Setting;
}

/**
 * @class Setting
 * @brief Widget for configuring source and destination directories
 */
class Setting : public QWidget {
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param parent Parent widget
   */
  explicit Setting(QWidget *parent = nullptr);

  /**
   * @brief Destructor
   */
  ~Setting();

private slots:
  void on_abortButton_clicked();
  void on_saveButton_clicked();
  void on_sourceButton_clicked();
  void on_destButton_clicked();

private:
  Ui::Setting *ui;               ///< UI pointer
  QString sourceDir;             ///< Source directory path
  QString destDir;               ///< Destination directory path
  ReadAndWriteJson *jsonHandler; ///< JSON configuration handler

  /**
   * @brief Load directories from configuration
   */
  void loadDir();
};

#endif // SETTING_HPP
