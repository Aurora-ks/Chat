#include "tcpmanager.h"
#include <QJsonDocument>
#include <QJsonObject>

TcpManager::TcpManager()
    :host_(""),
    port_(0),
    ReceivedHeadr_(false),
    DataID_(0),
    DataLength_(0)
{
    QObject::connect(&socket_, &QTcpSocket::connected, this, [this]{
        emit connected(true);
    });

    QObject::connect(&socket_, &QTcpSocket::readyRead, this, [this]{
        buffer_.append(socket_.readAll());

        QDataStream stream(&buffer_, QIODevice::ReadOnly);
        while(1)
        {
            //未解析头部
            if(!ReceivedHeadr_)
            {
                //消息头未收全
                if(buffer_.size() < (sizeof(quint16) * 2)) return;
                stream >> DataID_ >> DataLength_;
                buffer_.remove(0, sizeof(quint16) * 2);
                //Debug
                qDebug() << "DataID: " << DataID_ << " DataLength: " << DataLength_;
            }
            //数据未收全
            if(buffer_.size() < DataLength_)
            {
                ReceivedHeadr_ = true;
                return;
            }
            ReceivedHeadr_ = false;
            QByteArray data = buffer_.mid(0, DataLength_);
            //Debug
            qDebug() << "Receive Data: " << data;
            buffer_.remove(0, DataLength_);
            handlers_[DataID_](data, DataLength_);
        }
    });

    QObject::connect(this, &TcpManager::SendData, this, &TcpManager::OnSendData);
    InitHandlers();
}

void TcpManager::InitHandlers()
{
    handlers_.insert(RequestID::ID_USER_LOGIN, [this](QByteArray data, int len){
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if(doc.isNull() || !doc.isObject()){
            emit LoginSuccess(false);
            return;
        }
        QJsonObject json = doc.object();
        int err = json["error"].toInt();
        if(err != ErrorCodes::SUCCESS){
            emit LoginSuccess(false);
            return;
        }

        emit LoginSuccess(true);
    });
}

void TcpManager::OnConnect(ServerInfo info)
{
    host_ = info.host;
    port_ = info.port.toUInt();
    socket_.connectToHost(host_, port_);
}

void TcpManager::OnSendData(RequestID id, QString data)
{
    QByteArray buf;
    QDataStream os(&buf, QIODevice::WriteOnly);
    os.setByteOrder(QDataStream::BigEndian);
    quint16 rid = id;
    quint16 len = data.size();
    os << rid << len;
    buf.append(data.toUtf8());
    socket_.write(buf);
}
