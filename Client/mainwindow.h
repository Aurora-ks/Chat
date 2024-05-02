#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "httpmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class LoginDialog;
class RegisterDialog;
class ChatWindow;
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void InitHandlers();
    void tip(const QString &message);

    Ui::MainWindow *ui;
    LoginDialog* loginDlg_;
    RegisterDialog* registerDlg_;
    ChatWindow *ChatWindow_;
    QString name_;
    int uid_;
    QMap<RequestID, std::function<void(const QJsonObject&)>> handlers_;
signals:
    void AddList(QListWidgetItem *item);
private slots:
    void DoSendFinished(RequestID id, QString res, ErrorCodes err);
    void DoReceived(RequestID, QJsonObject);
    void SwitchRegister();
    void SwitchLogin();
    void OnLogin(QString, int);
    void on_SearchButton_clicked();
    void DoOpenChatWindow(QListWidgetItem *item);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
