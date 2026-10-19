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
#include <QFont>
#include <QStringList>
#include <QTextStream>

/**
 * @brief Application main entry point
 * @param argc Argument count
 * @param argv Argument values
 * @return Application exit code
 */
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Configure modern, high-clarity UI typography
  QFont defaultFont;
  defaultFont.setFamilies(
      {"Microsoft YaHei UI", "Microsoft YaHei", "Segoe UI", "PingFang SC", "sans-serif"});
  defaultFont.setPointSize(9);
  defaultFont.setStyleHint(QFont::SansSerif);
  defaultFont.setStyleStrategy(static_cast<QFont::StyleStrategy>(
      QFont::PreferAntialias | QFont::PreferQuality));
  app.setFont(defaultFont);

  // Load dark theme stylesheet and inject global font-family rule
  QFile styleFile(":qdarkstyle/dark/style.qss");
  styleFile.open(QFile::ReadOnly | QFile::Text);
  QTextStream styleStream(&styleFile);
  QString qss = styleStream.readAll();

  // Ensure all styled widgets inherit the modern UI font family
  QString fontRule =
      "QWidget { font-family: 'Microsoft YaHei UI', 'Microsoft YaHei', 'Segoe UI', sans-serif; }\n";
  app.setStyleSheet(fontRule + qss);

  HorizonJuicerCreator mainWindow;
  mainWindow.show();
  return app.exec();
}
