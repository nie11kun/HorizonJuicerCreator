#ifndef ABOUT_HPP
#define ABOUT_HPP

#include <QWidget>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();
    void setVersionInfo();

private:
    Ui::About *ui;
};

#endif // ABOUT_HPP
