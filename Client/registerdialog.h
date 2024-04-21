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
    void ShowState(QString str);
private:
    void InitHandlers();

    Ui::RegisterDialog *ui;
    QMap<RequestID, std::function<void(const QJsonObject&)>> handlers_;
public slots:
    void DoRegFinished(RequestID id, QString res, ErrorCodes err);
private slots:
    void on_GetCodeBtn_clicked();
    void on_RegisterButton_clicked();
};

#endif // REGISTERDIALOG_H
