/**
 * @file passwordcalculatorwindow.cpp
 * @brief Machine unlock password calculator window widget implementation
 * @author Marco Nie
 * @date 2026
 * @copyright Copyright © 2018-2026 Marco Nie. All rights reserved.
 */

#include "passwordcalculatorwindow.hpp"
#include "ui_passwordcalculatorwindow.h"

#include <QClipboard>
#include <QGuiApplication>
#include <QIntValidator>
#include <QRegularExpression>
#include <cmath>

PasswordCalculatorWindow::PasswordCalculatorWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::PasswordCalculatorWindow), isNewMode(true) {
  ui->setupUi(this);
  setWindowTitle("机床解锁口令计算");
  setWindowIcon(QIcon(":/icons/key.svg"));
  ui->pushButtonBack->setIcon(QIcon(":/icons/arrow-left.svg"));
  ui->pushButtonBack->setIconSize(QSize(15, 15));
  ui->pushButtonBack->setText("返回主菜单");
  ui->buttonModeNew->setIcon(QIcon(":/icons/bolt.svg"));
  ui->buttonModeNew->setIconSize(QSize(16, 16));
  ui->buttonModeLegacy->setIcon(QIcon(":/icons/clock.svg"));
  ui->buttonModeLegacy->setIconSize(QSize(16, 16));

  // Only allow 6-digit integers (100000 - 999999)
  QIntValidator *validator = new QIntValidator(100000, 999999, this);
  ui->lineEditChallenge->setValidator(validator);

  copyFeedbackTimer = new QTimer(this);
  copyFeedbackTimer->setSingleShot(true);
  connect(copyFeedbackTimer, &QTimer::timeout, this,
          &PasswordCalculatorWindow::resetCopyButtonText);

  ui->labelResult->setStyleSheet("color: #00E599; font-size: 46px; font-weight: bold; font-family: Consolas, 'Courier New', monospace; background-color: transparent;");
  ui->pushButtonCopy->setEnabled(false);
  updateModeStyles();
}

PasswordCalculatorWindow::~PasswordCalculatorWindow() {
  delete ui;
}

void PasswordCalculatorWindow::on_pushButtonBack_clicked() {
  emit triggerBackToMain();
  this->close();
}

void PasswordCalculatorWindow::on_buttonModeNew_clicked() {
  if (!isNewMode) {
    isNewMode = true;
    updateModeStyles();
    calculatePassword();
  }
}

void PasswordCalculatorWindow::on_buttonModeLegacy_clicked() {
  if (isNewMode) {
    isNewMode = false;
    updateModeStyles();
    calculatePassword();
  }
}

void PasswordCalculatorWindow::updateModeStyles() {
  ui->buttonModeNew->setChecked(isNewMode);
  ui->buttonModeLegacy->setChecked(!isNewMode);

  if (isNewMode) {
    ui->buttonModeNew->setStyleSheet(
        "QPushButton { background-color: #2563eb; color: #ffffff; border: 1px solid #3b82f6; border-radius: 6px; padding: 6px 12px; font-weight: bold; } QPushButton:hover { background-color: #1d4ed8; }");
    ui->buttonModeLegacy->setStyleSheet(
        "QPushButton { background-color: #1e293b; color: #94a3b8; border: 1px solid #334155; border-radius: 6px; padding: 6px 12px; font-weight: normal; } QPushButton:hover { background-color: #334155; color: #f1f5f9; }");
    ui->labelActiveBadge->setText("● 新版算法生效");
    ui->labelActiveBadge->setStyleSheet(
        "background-color: #1e293b; color: #38bdf8; border: 1px solid #0284c7; border-radius: 4px; padding: 2px 8px; font-size: 11px; font-weight: bold;");
  } else {
    ui->buttonModeNew->setStyleSheet(
        "QPushButton { background-color: #1e293b; color: #94a3b8; border: 1px solid #334155; border-radius: 6px; padding: 6px 12px; font-weight: normal; } QPushButton:hover { background-color: #334155; color: #f1f5f9; }");
    ui->buttonModeLegacy->setStyleSheet(
        "QPushButton { background-color: #d97706; color: #ffffff; border: 1px solid #f59e0b; border-radius: 6px; padding: 6px 12px; font-weight: bold; } QPushButton:hover { background-color: #b45309; }");
    ui->labelActiveBadge->setText("● 老版算法生效");
    ui->labelActiveBadge->setStyleSheet(
        "background-color: #1e293b; color: #fbbf24; border: 1px solid #d97706; border-radius: 4px; padding: 2px 8px; font-size: 11px; font-weight: bold;");
  }
}

void PasswordCalculatorWindow::on_pushButtonPaste_clicked() {
  QClipboard *clipboard = QGuiApplication::clipboard();
  if (!clipboard) return;

  QString text = clipboard->text().trimmed();
  // Try extracting 6 consecutive digits
  static const QRegularExpression regex(QStringLiteral(R"(\b\d{6}\b)"));
  QRegularExpressionMatch match = regex.match(text);
  if (match.hasMatch()) {
    ui->lineEditChallenge->setText(match.captured(0));
  } else {
    QString digitsOnly;
    for (const QChar &ch : text) {
      if (ch.isDigit()) {
        digitsOnly.append(ch);
        if (digitsOnly.length() == 6) break;
      }
    }
    if (digitsOnly.length() == 6) {
      ui->lineEditChallenge->setText(digitsOnly);
    } else {
      ui->labelStatus->setText("剪贴板中未检测到 6 位有效数字");
      ui->labelStatus->setStyleSheet("color: #ef4444; font-size: 12px;");
    }
  }
}

void PasswordCalculatorWindow::on_pushButtonClear_clicked() {
  ui->lineEditChallenge->clear();
  currentPassword.clear();
  ui->labelResult->setText("------");
  ui->labelStatus->setText("请输入 6 位机床挑战码开始计算");
  ui->labelStatus->setStyleSheet("color: #94a3b8; font-size: 12px;");
  ui->pushButtonCopy->setEnabled(false);
  ui->lineEditChallenge->setFocus();
}

void PasswordCalculatorWindow::on_pushButtonCopy_clicked() {
  if (currentPassword.isEmpty()) return;

  QClipboard *clipboard = QGuiApplication::clipboard();
  if (clipboard) {
    clipboard->setText(currentPassword);
    ui->pushButtonCopy->setIcon(QIcon(":/icons/check.svg"));
  ui->pushButtonCopy->setText("已复制到剪贴板");
    ui->labelStatus->setText("口令已成功复制到剪贴板");
    ui->labelStatus->setStyleSheet("color: #10b981; font-size: 12px; font-weight: bold;");
    copyFeedbackTimer->start(1500);
  }
}

void PasswordCalculatorWindow::resetCopyButtonText() {
  ui->pushButtonCopy->setIcon(QIcon(":/icons/copy.svg"));
  ui->pushButtonCopy->setText("复制解锁口令");
  if (!currentPassword.isEmpty()) {
    QString mode = isNewMode ? "新版" : "老版";
    ui->labelStatus->setText(QString("计算完成 (%1算法)").arg(mode));
    ui->labelStatus->setStyleSheet("color: #94a3b8; font-size: 12px;");
  }
}

void PasswordCalculatorWindow::on_lineEditChallenge_textChanged(const QString &text) {
  Q_UNUSED(text);
  calculatePassword();
}

void PasswordCalculatorWindow::on_lineEditChallenge_returnPressed() {
  if (!currentPassword.isEmpty()) {
    on_pushButtonCopy_clicked();
  }
}

void PasswordCalculatorWindow::calculatePassword() {
  QString challengeStr = ui->lineEditChallenge->text().trimmed();
  if (challengeStr.length() < 6) {
    currentPassword.clear();
    ui->labelResult->setText("------");
    ui->labelStatus->setText(QString("请输入 6 位机床挑战码 (已输入 %1/6 位)").arg(challengeStr.length()));
    ui->labelStatus->setStyleSheet("color: #94a3b8; font-size: 12px;");
    ui->pushButtonCopy->setEnabled(false);
    return;
  }

  bool ok = false;
  uint32_t challenge = challengeStr.toUInt(&ok);
  if (!ok || challenge < 100000 || challenge > 999999) {
    currentPassword.clear();
    ui->labelResult->setText("------");
    ui->labelStatus->setText("挑战码必须为 6 位正整数 (100000 - 999999)");
    ui->labelStatus->setStyleSheet("color: #ef4444; font-size: 12px;");
    ui->pushButtonCopy->setEnabled(false);
    return;
  }

  uint32_t pwd = 0;
  QString modeName;
  if (isNewMode) {
    pwd = computeUnlockPassword(challenge);
    modeName = "新版算法 (≥3.29.0)";
  } else {
    pwd = computeLegacyUnlockPassword(challenge);
    modeName = "老版算法 (<3.29.0)";
  }

  currentPassword = QString("%1").arg(pwd, 6, 10, QChar('0'));
  ui->labelResult->setText(currentPassword);
  ui->labelStatus->setText(QString("计算成功 (%1)").arg(modeName));
  ui->labelStatus->setStyleSheet("color: #10b981; font-size: 12px; font-weight: bold;");
  ui->pushButtonCopy->setEnabled(true);
}

uint32_t PasswordCalculatorWindow::computeUnlockPassword(uint32_t challenge) {
  const uint32_t reg2 = 837192; // secret_salt
  const uint32_t reg3 = 7;      // multiplier
  const uint32_t reg4 = 1234;   // scale
  const uint32_t modulo = 900000;
  const uint32_t base_offset = 100000;

  uint32_t reg5 = challenge / 1000;
  uint32_t reg6 = challenge % 1000;

  for (uint32_t reg0 = 0; reg0 < 4; ++reg0) {
    uint32_t shift = reg0 * 3;
    uint32_t reg8_shr = reg2 >> shift;
    uint32_t reg9_mult = reg3 * (reg0 + 13) * 101;
    uint32_t reg7 = (reg8_shr ^ reg9_mult) & 262143;

    uint32_t reg8 = (reg6 * reg3 + reg7) % 999983;
    uint32_t reg9 = static_cast<uint32_t>(std::floor(std::sqrt(reg8 + 1) * (reg4 + reg0 * 17))) % 1048575;

    uint32_t reg10_shl = (reg9 << 3) & 1048575;
    uint32_t reg11_shr = reg9 >> 17;
    uint32_t reg10 = reg10_shl | reg11_shr;
    uint32_t reg11 = (reg10 ^ (reg5 * 31 + 7)) & 524287;

    uint32_t reg12 = reg6;
    uint32_t reg13 = 0;
    if (reg12 % 2 == 1) {
      reg13 = reg11 ^ 13579;
    } else {
      reg13 = (reg11 + 24680) % 524287;
    }

    reg5 = reg12;
    reg6 = reg13;
  }

  uint32_t reg14 = (((reg5 << 11) & 1073741823) | (reg6 & 2047));
  uint32_t reg15 = reg14 ^ reg2;
  uint32_t finalPwd = (reg15 % modulo) + base_offset;
  return finalPwd;
}

uint32_t PasswordCalculatorWindow::computeLegacyUnlockPassword(uint32_t challenge) {
  return static_cast<uint32_t>(std::floor(std::sqrt(challenge) * 1000));
}
