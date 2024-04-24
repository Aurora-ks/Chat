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

signals:
    void SwitchResister();

private slots:
    void DoLoginFinished(RequestID id, QString res, ErrorCodes err);
    void on_showPwd_toggled(bool checked);
    void on_LoginButton_clicked();
};

#endif // LOGINDIALOG_H
