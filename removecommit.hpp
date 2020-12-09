#ifndef REMOVECOMMIT_HPP
#define REMOVECOMMIT_HPP

#include <QObject>
#include "filework.hpp"
#include "readandwritejson.hpp"
#include "convertcode.hpp"

class RemoveCommit : public QObject
{
    Q_OBJECT
public:
    explicit RemoveCommit(QObject *parent = nullptr);
    ~RemoveCommit();

public slots:
    void startProcess();

private:
    FileWork *project;
    ReadAndWriteJson *r;
    ConvertCode *c;

signals:
    void triggerStartingProcess();
    void triggerFinishedProcess();
};

#endif // REMOVECOMMIT_HPP
