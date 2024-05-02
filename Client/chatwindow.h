#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChatWindow;
}
class QListWidgetItem;
class ChatMessage;

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
    inline QMap<QListWidgetItem*,int>& users() {return UserMap_;}
    void ReceivedMessage(QListWidgetItem* item, QString message);
private:
    Ui::ChatWindow *ui;
    QMap<QListWidgetItem*,int> UserMap_;

public slots:
    void SwitchToLists(QListWidgetItem *item);
    void ShowMessage(ChatMessage *messageW, QListWidgetItem *item, QString text, int UserType);
private slots:
    void SwitchUser(QListWidgetItem *current);
    void on_SendButton_clicked();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CHATWINDOW_H
