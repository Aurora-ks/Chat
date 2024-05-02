#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QWidget>

enum UserType{
    me,
    he
};

class ChatMessage : public QWidget
{
    Q_OBJECT
public:
    explicit ChatMessage(QWidget *parent = nullptr);

    void setTextSuccess();
    void setText(QString text, QSize allSize, int UserType);

    QSize getRealString(QString src);
    QSize fontRect(QString str);

    inline QString text() {return m_msg;}
    inline bool UserType() {return UserType_;}
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QString m_msg;
    QSize m_allSize;
    int UserType_;

    int m_kuangWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight;

    QRect m_iconLeftRect;
    QRect m_iconRightRect;
    QRect m_sanjiaoLeftRect;
    QRect m_sanjiaoRightRect;
    QRect m_kuangLeftRect;
    QRect m_kuangRightRect;
    QRect m_textLeftRect;
    QRect m_textRightRect;
    QPixmap m_leftPixmap;
    QPixmap m_rightPixmap;
};

#endif // CHATMESSAGE_H
