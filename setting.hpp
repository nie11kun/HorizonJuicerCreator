#ifndef SETTING_HPP
#define SETTING_HPP

#include <QWidget>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void on_abortButton_clicked();

    void on_saveButton_clicked();

    void on_sourceButton_clicked();

    void on_destButton_clicked();

private:
    Ui::Setting *ui;
    QString sourceDir;
    QString destDir;
    void loadDir();
};

#endif // SETTING_HPP
