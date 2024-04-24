#include "verificationbtn.h"
#include <QTimer>
#include <QMouseEvent>

VerificationBtn::VerificationBtn(QWidget *parent)
    :QPushButton(parent),
    timer_(new QTimer(this)),
    TimeForWait_(60)
{
    QObject::connect(timer_, &QTimer::timeout, this, [this]{
        --TimeForWait_;
        if(TimeForWait_ <= 0)
        {
            timer_->stop();
            TimeForWait_ = 60;
            this->setText(tr("获取验证码"));
            this->setEnabled(true);
            return;
        }
        this->setText(QString::number(TimeForWait_));
    });
}

VerificationBtn::~VerificationBtn()
{
    timer_->stop();
}


void VerificationBtn::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setEnabled(false);
        setText(QString::number(TimeForWait_));
        timer_->start(1000);
        emit clicked();
    }
    QPushButton::mouseReleaseEvent(event);
}
