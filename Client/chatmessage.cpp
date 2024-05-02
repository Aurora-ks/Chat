#include "chatmessage.h"
#include <QFontMetricsF>
#include <QPaintEvent>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>

ChatMessage::ChatMessage(QWidget *parent)
    : QWidget(parent)
{
    QFont te_font = this->font();
    // te_font.setFamily("Microsoft YaHei UI");
    te_font.setFamily("MicrosoftYaHei");
    te_font.setPointSize(12);
    //    te_font.setWordSpacing(0);
    //    te_font.setLetterSpacing(QFont::PercentageSpacing,0);
    //    te_font.setLetterSpacing(QFont::PercentageSpacing, 100);          //300%,100为默认  //设置字间距%
    //    te_font.setLetterSpacing(QFont::AbsoluteSpacing, 0);             //设置字间距为3像素 //设置字间距像素值
    this->setFont(te_font);
    m_leftPixmap = QPixmap(":/icon1.jpg");
    m_rightPixmap = QPixmap(":/icon1.jpg");
}

void ChatMessage::setText(QString text, QSize allSize, int UserType)
{
    m_msg = text;
    UserType_ = UserType;
    m_allSize = allSize;

    this->update();
}

QSize ChatMessage::fontRect(QString str)
{
    m_msg = str;
    int minHei = 30;
    int iconWH = 40;
    int iconSpaceW = 20;
    int iconRectW = 5;
    int iconTMPH = 5;
    int sanJiaoW = 6;
    int kuangTMP = 20;
    int textSpaceRect = 12;
    m_kuangWidth = this->width() - kuangTMP - 2*(iconWH+iconSpaceW+iconRectW);
    m_textWidth = m_kuangWidth - 2*textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
    m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

    QSize size = getRealString(m_msg); // 整个的size

    int hei = size.height() < minHei ? minHei : size.height();

    m_sanjiaoLeftRect = QRect(iconWH+iconSpaceW+iconRectW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);

    if(size.width() < (m_textWidth+m_spaceWid)) {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
                                 m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
    } else {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
        m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
    }
    m_textLeftRect.setRect(m_kuangLeftRect.x()+textSpaceRect,m_kuangLeftRect.y()+iconTMPH,
                           m_kuangLeftRect.width()-textSpaceRect,m_kuangLeftRect.height()-iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x()+textSpaceRect,m_kuangRightRect.y()+iconTMPH,
                            m_kuangRightRect.width()-textSpaceRect,m_kuangRightRect.height()-iconTMPH);

    return QSize(size.width(), hei);
}

QSize ChatMessage::getRealString(QString src)
{
    QFontMetricsF fm(this->font());
    QFontMetricsF f(this->font());
    int charW = f.maxWidth(); //单字符宽度
    m_lineHeight = fm.lineSpacing();
    int nCount = src.count("\n");// 计算文本中的换行数量
    int nMaxWidth = 0; // 用于存储每行文本的最大宽度
    if(nCount == 0) { // 如果没有换行，即单行文本
        nMaxWidth = qCeil(f.boundingRect(src).width());
        QString value = src;
        if(nMaxWidth > m_textWidth) { // 如果文本宽度超过控件宽度
            int t = nMaxWidth;
            nMaxWidth = m_textWidth; // 使用控件宽度作为最大宽度
            int size = m_textWidth / charW; // 计算每行能容纳的字符数
            int num = t / m_textWidth; // 计算需要换行的行数
            nCount += num;
            QString temp = "";
            for(int i = 0; i < num; i++) {
                temp += value.mid(i*size, (i+1)*size) + "\n";
            }
            src.replace(value, temp); // 替换原文本为换行后的文本
        }
    } else { // 多行文本
        for(int i = 0; i < (nCount + 1); i++) { // 遍历每一行
            QString value = src.split("\n").at(i);
            int textWidth = qCeil(f.boundingRect(value).width());
            nMaxWidth = textWidth > nMaxWidth ? textWidth : nMaxWidth; // 更新最大宽度
            if(textWidth > m_textWidth) { // 如果当前行宽度超过控件宽度
                nMaxWidth = m_textWidth; // 使用控件宽度作为最大宽度
                int size = m_textWidth / charW; // 计算每行能容纳的字符数
                int num = textWidth / m_textWidth; // 计算需要增加的换行数
                num = ((i+num)*charW + textWidth) / m_textWidth;
                nCount += num; // 更新总换行数
                QString temp = "";
                for(int i = 0; i < num; i++) {
                    temp += value.mid(i*size, (i+1)*size) + "\n";
                }
                src.replace(value, temp); // 替换当前行文本为换行后的文
            }
        }
    }
    return QSize(nMaxWidth+m_spaceWid, (nCount + 1) * m_lineHeight+2*m_lineHeight);
}

void ChatMessage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    if(UserType_ == he) { // 对方
        //头像
        //        painter.drawRoundedRect(m_iconLeftRect,m_iconLeftRect.width(),m_iconLeftRect.height());
        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        //框加边
        QColor col_KuangB(234, 234, 234);
        painter.setBrush(QBrush(col_KuangB));
        painter.drawRoundedRect(m_kuangLeftRect.x()-1,m_kuangLeftRect.y()-1,m_kuangLeftRect.width()+2,m_kuangLeftRect.height()+2,4,4);
        //框
        QColor col_Kuang(255,255,255);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangLeftRect,4,4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoLeftRect.x(), 30),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 25),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //三角加边
        QPen penSanJiaoBian;
        penSanJiaoBian.setColor(col_KuangB);
        painter.setPen(penSanJiaoBian);
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 24));
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 36));

        //内容
        QPen penText;
        penText.setColor(QColor(51,51,51));
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textLeftRect, m_msg,option);
    }
    else if(UserType_ == me){ // 自己
        //头像
        //        painter.drawRoundedRect(m_iconRightRect,m_iconRightRect.width(),m_iconRightRect.height());
        painter.drawPixmap(m_iconRightRect, m_rightPixmap);

        //框
        QColor col_Kuang(75,164,242);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangRightRect,4,4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoRightRect.x()+m_sanjiaoRightRect.width(), 30),
            QPointF(m_sanjiaoRightRect.x(), 25),
            QPointF(m_sanjiaoRightRect.x(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //内容
        QPen penText;
        penText.setColor(Qt::white);
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textRightRect,m_msg,option);
    }
    QWidget::paintEvent(event);
}
