/**
 * @file history.hpp
 * @brief Version history dialog widget header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <QWidget>

namespace Ui {
class History;
}

/**
 * @class History
 * @brief Widget displaying application version history
 */
class History : public QWidget {
  Q_OBJECT

public:
  /**
   * @brief Constructor
   * @param parent Parent widget
   */
  explicit History(QWidget *parent = nullptr);

  /**
   * @brief Destructor
   */
  ~History();

private:
  Ui::History *ui; ///< UI pointer
};

#endif // HISTORY_HPP
