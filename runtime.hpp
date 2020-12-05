#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <QWidget>

namespace Ui {
class Runtime;
}

class Runtime : public QWidget
{
    Q_OBJECT

public:
    explicit Runtime(QWidget *parent = nullptr);
    ~Runtime();

private:
    Ui::Runtime *ui;
};

#endif // RUNTIME_HPP
