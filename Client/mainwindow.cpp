#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "logindialog.h"
#include "registerdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loginDlg_(new LoginDialog())
    , registerDlg_(new RegisterDialog())
{
    connect(loginDlg_, &LoginDialog::SwitchResister, this, &MainWindow::SwitchRegister);
    connect(registerDlg_, &RegisterDialog::SwitchLogin, this, &MainWindow::SwitchLogin);
    ui->setupUi(this);
    // setCentralWidget(loginDlg_);
    loginDlg_->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete loginDlg_;
    delete registerDlg_;
}

void MainWindow::SwitchRegister()
{
    // setCentralWidget(registerDlg_);
    // loginDlg_->hide();
    registerDlg_->exec();
}

void MainWindow::SwitchLogin()
{
    // registerDlg_->close();
    // loginDlg_->show();
    registerDlg_->reject();
}
