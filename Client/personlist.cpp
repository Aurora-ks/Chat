#include "personlist.h"
#include "httpmanager.h"
#include <QMenu>
#include <QMessageBox>

PersonList::PersonList(QWidget *parent)
    :QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFont(QFont("Microsoft YaHei UI", 12));
    setIconSize(QSize(50,50));
    InitMenu();
}

void PersonList::InitMenu()
{
    menu_ = new QMenu(this);
    QAction *DelAct = new QAction("删除好友", this);
    menu_->addAction(DelAct);
    connect(DelAct, &QAction::triggered, this, &PersonList::DelPerson);
}

void PersonList::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit OpenChatWindow(currentItem());
    QListWidget::mouseDoubleClickEvent(event);
}


void PersonList::contextMenuEvent(QContextMenuEvent *event)
{
    QListWidget::contextMenuEvent(event);

    if(currentItem() == nullptr) return;
    menu_->exec(QCursor::pos());
}

void PersonList::AddPerson(const QString &name, int uid, int self_id)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setText(name);
    item->setIcon(QIcon(":/icon1.jpg"));
    item->setData(Qt::UserRole, uid);
    item->setData(Qt::UserRole+1, name);
    item->setData(Qt::UserRole+2, self_id);
}

void PersonList::DelPerson()
{
    auto cur = currentItem();
    auto btn = QMessageBox::warning(this, "确认", "是否确认，该操作不可撤销!", QMessageBox::Ok | QMessageBox::Cancel);
    if(btn != QMessageBox::Ok) return;
    QJsonObject json;
    json["user_id"] = cur->data(Qt::UserRole+2).toInt();
    json["friend_id"] = cur->data(Qt::UserRole).toInt();
    HttpManager::GetInstance()->PostRequest(QUrl(HttpManager::GetPrefix()+"/del-friend"), json, RequestID::ID_DEL_PERSON);
}
