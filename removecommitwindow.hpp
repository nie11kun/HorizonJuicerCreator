#ifndef REMOVECOMMITWINDOW_HPP
#define REMOVECOMMITWINDOW_HPP

#include <QWidget>

namespace Ui {
class RemoveCommitWindow;
}

class RemoveCommitWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RemoveCommitWindow(QWidget *parent = nullptr);
    ~RemoveCommitWindow();

private:
    Ui::RemoveCommitWindow *ui;
};

#endif // REMOVECOMMITWINDOW_HPP
