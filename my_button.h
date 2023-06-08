#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <QPushButton>
#include<QPropertyAnimation>
class my_button : public QPushButton
{

public:
    my_button(QString str,QWidget *parent = nullptr);
    void setColor(int r, int g, int b,int hr, int hg, int hb); // kolory tła oraz kolor najechania
    void setDisabled(bool disabled);

private:
    bool isAnimationRunning = false;
    void make_bigger();
    void make_smaller();



};

#endif // MY_BUTTON_H
