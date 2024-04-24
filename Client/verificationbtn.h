#ifndef VERIFICATIONBTN_H
#define VERIFICATIONBTN_H

#include <QPushButton>

class VerificationBtn : public QPushButton
{
public:
    VerificationBtn(QWidget *parent);
    ~VerificationBtn();

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QTimer *timer_;
    int TimeForWait_; // seconds
};

#endif // VERIFICATIONBTN_H
