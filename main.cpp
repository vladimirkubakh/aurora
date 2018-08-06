#include <mainwindow.h>
#include <QApplication>
#include <QtCore>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    forproc* fp = new forproc();
    return a.exec();
}
