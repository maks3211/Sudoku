#ifndef MY_CHECKBOX_H
#define MY_CHECKBOX_H

#include <QCheckBox>
#include<QPropertyAnimation>
#include<QLabel>

class my_checkbox : public QCheckBox
{
public:
    my_checkbox(QWidget *parent = nullptr);
    void setLeftText(QString text);
    void setRightText(QString text);
    void setTopText(QString text);
};

#endif // MY_CHECKBOX_H
