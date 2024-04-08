#include "mainwindow.h"
#include "logindialog.h"
#include "registerdialog.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // LoginDialog loginDlg;
    // loginDlg.exec();
    RegisterDialog regDlg;
    regDlg.exec();
    w.show();
    return a.exec();
}
