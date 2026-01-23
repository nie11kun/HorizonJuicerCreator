/**
 * @file about.hpp
 * @brief About dialog widget header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef ABOUT_HPP
#define ABOUT_HPP

#include <QWidget>

namespace Ui {
class About;
}

/**
 * @class About
 * @brief Widget displaying application information and version
 */
class About : public QWidget {
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param parent Parent widget
   */
  explicit About(QWidget *parent = nullptr);

  /**
   * @brief Destructor
   */
  ~About();

  /**
   * @brief Set version information label
   */
  void setVersionInfo();

private:
  Ui::About *ui; ///< UI pointer
};

#endif // ABOUT_HPP
