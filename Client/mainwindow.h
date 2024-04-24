#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class LoginDialog;
class RegisterDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginDialog* loginDlg_;
    RegisterDialog* registerDlg_;

public slots:
    void SwitchRegister();
    void SwitchLogin();
};
#endif // MAINWINDOW_H
