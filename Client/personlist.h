#ifndef PERSONLIST_H
#define PERSONLIST_H

#include <QListWidget>

class PersonList : public QListWidget
{
    Q_OBJECT
public:
    explicit PersonList(QWidget *parent);

private:
    void InitMenu();

    QMenu *menu_;
    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
signals:
    void OpenChatWindow(QListWidgetItem *item);
public slots:
    void AddPerson(const QString &name, int uid, int self_id);
    void DelPerson();
};

#endif // PERSONLIST_H
