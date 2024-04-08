#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // loginDlg_ = new LoginDialog();
    // loginDlg_->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    // delete loginDlg_;
}
