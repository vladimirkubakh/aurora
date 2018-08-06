#include "mainwindow.h"

#include <QTextEdit>
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QWebView>
#include <QWebFrame>
#include <QWebPage>
#include <windows.h>
#include <windowsx.h>
#include <QNetworkProxy>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QDesktopWidget>
#include <QWebHistory>
QBotNetworkAccessManager::QBotNetworkAccessManager() {
    this->referer="http://tr.anidub.com";
    this->browser="";
}
void QBotNetworkAccessManager::setB(QString st) {
    this->browser=st;

}
void QBotNetworkAccessManager::setR(QString st) {
    this->referer=st;
}
QNetworkReply * QBotNetworkAccessManager::createRequest ( Operation op, const QNetworkRequest & req, QIODevice * outgoingData) {


    QNetworkRequest myReq(req);//-- copy data from const QNetworkRequest& req

 /*   QString strUA = "MY_USER_AGENT";//-- custom value for User-Agent
    QString strRef = "MY_REFERRER";//-- custom value for Referer
    QString strLocat = "MY_LOCATE";//-- custom value for Referer
    QString strAcc = "MY_ACCEPT";//-- custom value for Referer

    QByteArray str_1 = myReq.rawHeader("User-Agent");
    QByteArray str_2 = myReq.rawHeader("Accept");
    QByteArray str_3 = myReq.rawHeader("Referer");*/

    myReq.setRawHeader( "User-Agent", "Opera/9.80 (X11; Linux x86_64; U; fr) Presto/2.9.168 Version/11.50" );
//      myReq.setRawHeader( "Referer", this->referer.toUtf8() );
//    myReq.setRawHeader( "Accept", strAcc.toUtf8() );
//    myReq.setHeader(QNetworkRequest::LocationHeader, strLocat);

//    myReq.setRawHeader("Accept-Language", "MY_LANGUAGE");
 //   myReq.setRawHeader("Accept-Encoding", "MY_ENCODING");
 //   myReq.setRawHeader("Accept-Charset", "MY_CHAR");
 //   myReq.setRawHeader("Keep-Alive", "MY_KEEP-ALIVE");
 //   myReq.setRawHeader("Connection", "MY_CONNECTION");


    return QNetworkAccessManager::createRequest( op, myReq, outgoingData);

}
void glav::timeOutExit() {
    ::exit(0);
}
void glav::whenLastPageDownloaded() {
   ::exit(0);
}
void glav::downloadThirdPage() {
    this->timer->stop();
    QObject::disconnect(this->timer, SIGNAL(timeout()), this, SLOT(downloadThirdPage()));
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, 130*51,890*64,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
    Sleep(300);
    mouse_event(MOUSEEVENTF_LEFTUP, 0,0,0,0);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(whenLastPageDownloaded()));
    this->timer->start();
}
void glav::downloadSecondPage() {
    this->timer->stop();
    QObject::disconnect(this->timer, SIGNAL(timeout()), this, SLOT(downloadSecondPage()));
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, 110*51,286*64,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
    Sleep(300);
    mouse_event(MOUSEEVENTF_LEFTUP, 0,0,0,0);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(downloadThirdPage()));
    this->timer->start();
}
void glav::downloadFirstPage() {
    this->timer->stop();
    QObject::disconnect(this->timer, SIGNAL(timeout()), this, SLOT(downloadFirstPage()));
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, 161*51,303*64,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
    Sleep(300);
    mouse_event(MOUSEEVENTF_LEFTUP, 0,0,0,0);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(downloadSecondPage()));
    this->timer->start();

}
void glav::whenSiteDownloaded() {
    QObject::disconnect(this->v, SIGNAL(loadStated(bool)), this->timer, SLOT(start()));
    QObject::disconnect(this->timer, SIGNAL(timeout()), this, SLOT(timeOutExit()));
    QObject::disconnect(this->v, SIGNAL(loadFinished(bool)), this, SLOT(whenSiteDownloaded()));
    qDebug()<<"avrora downloaded!";
    this->timer->setInterval(4000);
    this->timer->start();
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(downloadFirstPage()));

}
void glav::clearCookies() {
    this->v->page()->networkAccessManager()->setCookieJar(new QNetworkCookieJar());
}
void glav::whenRefDownloaded() {
     this->timer->stop();
     QObject::disconnect(this->v, SIGNAL(loadFinished(bool)), this, SLOT(whenRefDownloaded()));
     QObject::disconnect(this->v, SIGNAL(loadStarted()), this->timer, SLOT(start()));
     QObject::disconnect(this->timer, SIGNAL(timeout()), this, SLOT(timeOutExit()));
     QObject::connect(this->v, SIGNAL(loadStated(bool)), this->timer, SLOT(start()));
     QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(timeOutExit()));
     QObject::connect(this->v, SIGNAL(loadFinished(bool)), this, SLOT(whenSiteDownloaded()));
     //QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(clearCookies()));
     this->timer->start();
     this->v->page()->mainFrame()->evaluateJavaScript("document.write('<a id=\"avroraurl\" href=\"http://avroragroup.ucoz.net\"></a>');var e = document.createEvent('HTMLEvents');e.initEvent('click', true, true );document.getElementById('avroraurl').dispatchEvent(e);");
     qDebug()<<"avrora downloading..";

}
void glav::start() {
    //QObject::connect(this->v, SIGNAL(loadStarted()), this->timer, SLOT(start()));
    QObject::connect(this->v, SIGNAL(loadFinished(bool)), this, SLOT(whenRefDownloaded()));
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(timeOutExit()));
    this->timer->start();
    this->v->load(QUrl("http://vk.com/onlyorly"));
    this->v->resize(1280,950);

}
glav::glav(QWebView *& view, QApplication*& a, QWidget*& w, QString id) {
    this->ipid=id.toInt();
    qDebug()<<this->ipid;
    //Открытие файла с проксями
    QFile file("C:\\programming\\C++\\Qt\\avrora\\servers.txt");
    file.open(QIODevice::ReadWrite);
    QString bigProxyList = file.readAll();
    QStringList splittedProxyList = bigProxyList.split(QString("\n"));
    int ipscount = splittedProxyList.length();

    QString ports[ipscount];
    for(int i =0; i<ipscount; i++) {

        QString address = splittedProxyList.at(i);
        QStringList splittedAddress = address.split(":");
        this->ips[i] = splittedAddress.at(0);
        ports[i] = splittedAddress.at(1);


    }

    this->emptyJar=new QNetworkCookieJar();
    QNetworkProxy p(QNetworkProxy::HttpProxy);
    this->proxy = p;
    this->proxyHost=QString(this->ips[this->ipid]);
    this->proxy.setHostName(this->proxyHost);
    this->proxy.setPort(8085);

    this->mgr=new QBotNetworkAccessManager();
    this->timer=new QTimer();
    this->timer->setInterval(60000);
    this->v=view;

   /* DEVMODE dm2;
            dm2.dmSize = sizeof(DEVMODE);

        dm2.dmPelsWidth = 1920;
        dm2.dmPelsHeight = 1080;
        dm2.dmFields = DM_PELSWIDTH |DM_PELSHEIGHT;
        ChangeDisplaySettings(&dm2, 0);*/

    this->v->page()->setNetworkAccessManager(this->mgr);
    QNetworkProxy::setApplicationProxy(this->proxy);
    this->counter=100;
    this->mainWidget=w;
    this->ap=a;

}
