#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <QWidget>

namespace Ui {
class History;
}

class History : public QWidget
{
    Q_OBJECT

public:
    explicit History(QWidget *parent = nullptr);
    ~History();

private:
    Ui::History *ui;
};

#endif // HISTORY_HPP
