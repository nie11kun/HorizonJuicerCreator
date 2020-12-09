#ifndef REMOVECOMMITWINDOW_HPP
#define REMOVECOMMITWINDOW_HPP

#include <QWidget>
#include "removecommit.hpp"
#include <QThread>
#include "readandwritejson.hpp"
#include "convertcode.hpp"

namespace Ui {
class RemoveCommitWindow;
}

class RemoveCommitWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RemoveCommitWindow(QWidget *parent = nullptr);
    ~RemoveCommitWindow();

private slots:
    void on_pushButtonDir_clicked();

    void on_pushButtonStart_clicked();

    void on_pushButtonCancel_clicked();

    void startingProcess();
    void finishedProcess();

private:
    Ui::RemoveCommitWindow *ui;
    RemoveCommit *remove;
    QThread *t;
    ReadAndWriteJson *r;
    void loadDir();
    ConvertCode *c;

signals:
    void triggerProcess();
};

#endif // REMOVECOMMITWINDOW_HPP
