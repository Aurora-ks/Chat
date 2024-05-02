#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "httpmanager.h"

namespace Ui {
class LoginDialog;
}

class Qstring;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    void InitHandlers();
    void ShowState(const QString &msg);

    Ui::LoginDialog *ui;
    QMap<RequestID, std::function<void(const QJsonObject&)>> handlers_;
    QString name_;
    quint16 uid_;
    QString token_;
signals:
    void SwitchResister();
    void SwitchToMain(QString, int);

private slots:
    void DoLoginFinished(RequestID id, QString res, ErrorCodes err);
    void DoConnected(bool success);
    void LoginSuccess(bool success);
    void on_showPwd_toggled(bool checked);
    void on_LoginButton_clicked();
};

#endif // LOGINDIALOG_H
