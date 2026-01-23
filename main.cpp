/**
 * @file main.cpp
 * @brief Application entry point for HorizonJuicerCreator
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "horizonjuicercreator.hpp"

#include <QApplication>
#include <QFile>
#include <QTextStream>

/**
 * @brief Application main entry point
 * @param argc Argument count
 * @param argv Argument values
 * @return Application exit code
 */
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  HorizonJuicerCreator mainWindow;

  // Load dark theme stylesheet
  QFile styleFile(":qdarkstyle/dark/style.qss");
  styleFile.open(QFile::ReadOnly | QFile::Text);
  QTextStream styleStream(&styleFile);
  app.setStyleSheet(styleStream.readAll());

  mainWindow.show();
  return app.exec();
}
