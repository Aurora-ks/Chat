#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "mainwindow.h"
#include "chatmessage.h"
#include "tcpmanager.h"
#include <QVBoxLayout>

ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->UserList->setFocusPolicy(Qt::NoFocus);
    ui->UserList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->UserList->setFont(QFont("Microsoft YaHei UI", 12));
    ui->UserList->setIconSize(QSize(50,50));
    connect(ui->UserList, &QListWidget::currentItemChanged, this, &ChatWindow::SwitchUser);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::ReceivedMessage(QListWidgetItem *item, QString message)
{
    //判断是否存在该项
    auto items = ui->UserList->findItems("", Qt::MatchContains);
    QListWidgetItem *cur = nullptr;
    for(const auto &i : items){
        if(i->text() == item->text()){
            cur = i;
            break;
        }
    }
    //需要创建新项
    if(cur == nullptr){
        QListWidgetItem *person = new QListWidgetItem(*item);
        ui->UserList->addItem(person);
        //创建对话界面
        QListWidget *NewPage = new QListWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        NewPage->setLayout(layout);
        NewPage->setSelectionMode(QListWidget::NoSelection);
        int index = ui->stackedWidget->addWidget(NewPage);
        UserMap_.insert(person, index);

        ChatMessage *MsgWidget = new ChatMessage();
        QListWidgetItem *newItem = new QListWidgetItem(NewPage);
        ShowMessage(MsgWidget, newItem, message, UserType::he);
    }
    else{
        //判断是否需要创建对话界面
        auto it = UserMap_.find(cur);
        if(it == UserMap_.end()){
            QListWidget *NewPage = new QListWidget();
            QVBoxLayout* layout = new QVBoxLayout();
            NewPage->setLayout(layout);
            NewPage->setSelectionMode(QListWidget::NoSelection);
            int index = ui->stackedWidget->addWidget(NewPage);
            ui->stackedWidget->setCurrentIndex(index);
            UserMap_.insert(cur, index);
            it = UserMap_.find(cur);
        }
        ChatMessage *MsgWidget = new ChatMessage();
        QListWidgetItem *newItem = new QListWidgetItem(qobject_cast<QListWidget*>(ui->stackedWidget->widget(it.value())));
        ShowMessage(MsgWidget, newItem, message, UserType::he);
    }
}

void ChatWindow::SwitchToLists(QListWidgetItem *item)
{
    //判断是否存在该项
    auto items = ui->UserList->findItems("", Qt::MatchContains);
    QListWidgetItem *cur = nullptr;
    for(const auto &i : items){
        if(i->text() == item->text()){
            cur = i;
            break;
        }
    }
    //创建一个新项
    if(cur == nullptr){
        QListWidgetItem *person = new QListWidgetItem(*item);
        ui->UserList->addItem(person);
        cur = person;
    }
    ui->UserList->setCurrentItem(cur);
}

void ChatWindow::ShowMessage(ChatMessage *messageW, QListWidgetItem *item, QString text, int UserType)
{
    messageW->setFixedWidth(ui->stackedWidget->currentWidget()->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, size, UserType);
    int index = UserMap_[item];
    qobject_cast<QListWidget*>(ui->stackedWidget->widget(index))->setItemWidget(item, messageW);
}

void ChatWindow::SwitchUser(QListWidgetItem *current)
{
    auto it = UserMap_.find(current);
    //需要创建新的聊天界面
    if(it == UserMap_.end()){
        QListWidget *NewPage = new QListWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        NewPage->setLayout(layout);
        NewPage->setSelectionMode(QListWidget::NoSelection);
        int index = ui->stackedWidget->addWidget(NewPage);
        ui->stackedWidget->setCurrentIndex(index);
        UserMap_.insert(current, index);
    }
    //切换到相应的聊天界面
    else{
        int index = it.value();
        ui->stackedWidget->setCurrentIndex(index);
    }
}

void ChatWindow::on_SendButton_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    if(msg.isEmpty()) return;
    ui->textEdit->clear();
    ChatMessage *MsgWidget = new ChatMessage();
    QListWidgetItem *item = new QListWidgetItem(qobject_cast<QListWidget*>(ui->stackedWidget->currentWidget()));

    QJsonObject json;
    auto i = ui->UserList->currentItem();
    json["id_to"] = i->data(Qt::UserRole).toInt();
    json["id_from"] = i->data(Qt::UserRole+2).toInt();
    json["message"] = msg;
    // QJsonDocument doc(json);
    // QString data = QString::fromUtf8(doc.toJson());
    // TcpManager::Instance().OnSendData(ID_CHAT, data);
    emit TcpManager::Instance().SendData(ID_CHAT, json);
    ShowMessage(MsgWidget, item, msg, UserType::me);
}

void ChatWindow::resizeEvent(QResizeEvent *event)
{
    QListWidget *list = qobject_cast<QListWidget*>(ui->stackedWidget->currentWidget());
    for(int i = 0; i < list->count(); ++i){
        QListWidgetItem *item = list->item(i);
        ChatMessage* msg = qobject_cast<ChatMessage*>(list->itemWidget(item));
        ShowMessage(msg, item, msg->text(), msg->UserType());
    }
}
