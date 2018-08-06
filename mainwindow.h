#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QWebView>
#include <QWidget>
#include <windows.h>
#include <windowsx.h>
#include <QNetworkProxy>
#include <QNetworkCookieJar>

class QBotNetworkAccessManager : public QNetworkAccessManager {
       Q_OBJECT
public:
    QString browser;
    QString referer;
    QBotNetworkAccessManager();
    void setB(QString);
    void setR(QString);
protected:
    QNetworkReply *createRequest (Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);

};

class glav : public QObject {
Q_OBJECT
public:
    int status;
    QString ips[1000];
    int ipid;
    QNetworkCookieJar* emptyJar;
    QString proxyHost;
    QNetworkProxy proxy;
    QBotNetworkAccessManager* mgr;
    QWebView* v;
    QTimer* timer;
    QApplication* ap;
    int counter;
    QWidget* mainWidget;
    HWND hwnd;
    LPARAM lParam;
    void start();
    glav(QWebView*&, QApplication*&, QWidget*&, QString);
public slots:
    void timeOutExit();
    void clearCookies();
    void whenRefDownloaded();
    void whenSiteDownloaded();
    void downloadFirstPage();
    void downloadSecondPage();
    void downloadThirdPage();
    void whenLastPageDownloaded();
};
#endif // MAINWINDOW_H
