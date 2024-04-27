#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include <QTcpSocket>
#include <QObject>
#include "Singleton.h"
#include "types.h"

class TcpManager : public Singleton<TcpManager>, public std::enable_shared_from_this<TcpManager>, public QObject
{
    friend class Singleton<TcpManager>;
    Q_OBJECT
public:
    TcpManager();
private:
    QTcpSocket socket_;
    QString host_;
    quint16 port_;
    QByteArray buffer_;
    bool ReceivedHeadr_;
    quint16 DataID_;
    quint16 DataLength_;

public slots:
    void OnConnect(ServerInfo);
    void OnSendData(RequestID, QString);
signals:
    void connected(bool);
    void SendData(RequestID, QString);
};

#endif // TCPMANAGER_H
