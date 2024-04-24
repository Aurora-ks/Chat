#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "httpmanager.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private:
    void InitHandlers();
    void ShowState(QString str);

    Ui::RegisterDialog *ui;
    QMap<RequestID, std::function<void(const QJsonObject&)>> handlers_;

signals:
    void SwitchLogin();

private slots:
    void DoRegFinished(RequestID id, QString res, ErrorCodes err);
    void on_GetCodeBtn_clicked();
    void on_RegisterButton_clicked();
    void on_showPwd_toggled(bool checked);
    void on_showPwd1_toggled(bool checked);
};

#endif // REGISTERDIALOG_H
