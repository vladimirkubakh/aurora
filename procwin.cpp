#include "mainwindow.h"
#include <QtCore>
#include <QtGui>
forproc::forproc() {
    this->proc=new QProcess();
    this->program = "C:\\programming\\C++\\Qt\\build-getcurinfo-Desktop_Qt_5_0_2_MinGW_32bit-Debug\\debug\\getcurinfo.exe";
    this->counter=1;
    this->arguments<<QString::number(this->counter);
    QObject::connect(this->proc, SIGNAL(finished(int)), this, SLOT(whenProcFinished(int)));
    this->proc->start(this->program, this->arguments);
}

void forproc::whenProcFinished(int) {
    if(counter<1000) {
        counter++;
        QStringList par2;
        par2<<QString::number(counter);
        this->proc->start(this->program, par2);
    }

}
/*void forproc::startP() {
    QObject::connect(this->proc, SIGNAL(finished(int)), this, SLOT(whenProcFinished(int)));
    this->proc->start(this->program, this->arguments);
}*/
