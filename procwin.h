#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
class forproc : public QObject {

    Q_OBJECT
public:
    int counter;
    QProcess* proc;
    QString program;
    QStringList arguments;
    forproc();
    void startP();
public slots:
    void whenProcFinished(int);

};

#endif // MAINWINDOW_H
