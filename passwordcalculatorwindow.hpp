/**
 * @file passwordcalculatorwindow.hpp
 * @brief Machine unlock password calculator window widget header
 * @author Marco Nie
 * @date 2026
 * @copyright Copyright © 2018-2026 Marco Nie. All rights reserved.
 */

#ifndef PASSWORDCALCULATORWINDOW_HPP
#define PASSWORDCALCULATORWINDOW_HPP

#include <QWidget>
#include <QTimer>

namespace Ui {
class PasswordCalculatorWindow;
}

/**
 * @class PasswordCalculatorWindow
 * @brief Widget for calculating machine unlock passwords
 *
 * Provides calculations for both standard (v3.29.0+)
 * and legacy (< v3.29.0) algorithms.
 */
class PasswordCalculatorWindow : public QWidget {
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param parent Parent widget
   */
  explicit PasswordCalculatorWindow(QWidget *parent = nullptr);

  /**
   * @brief Destructor
   */
  ~PasswordCalculatorWindow();

signals:
  void triggerBackToMain();

private slots:
  void on_pushButtonBack_clicked();
  void on_pushButtonPaste_clicked();
  void on_pushButtonClear_clicked();
  void on_pushButtonCopy_clicked();
  void on_lineEditChallenge_textChanged(const QString &text);
  void on_lineEditChallenge_returnPressed();
  void on_buttonModeNew_clicked();
  void on_buttonModeLegacy_clicked();
  void resetCopyButtonText();

private:
  Ui::PasswordCalculatorWindow *ui;
  QTimer *copyFeedbackTimer;
  QString currentPassword;
  bool isNewMode = true;

  void updateModeStyles();
  void calculatePassword();
  static uint32_t computeUnlockPassword(uint32_t challenge);
  static uint32_t computeLegacyUnlockPassword(uint32_t challenge);
};

#endif // PASSWORDCALCULATORWINDOW_HPP
