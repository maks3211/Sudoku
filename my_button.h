#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <QPushButton>

class my_button : public QPushButton
{
public:
    my_button(QString str,QWidget *parent = nullptr);
};

#endif // MY_BUTTON_H
