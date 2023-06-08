#ifndef DIF_LEVEL_H
#define DIF_LEVEL_H
#include"my_button.h"
#include <QWidget>
#include<QPushButton>
#include <QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QLabel>
class Dif_level : public QWidget
{
    Q_OBJECT
public:
    explicit Dif_level(QWidget *parent = nullptr);

private:
    QLabel *napis;
    my_button *lvl1;
    my_button *lvl2;
    my_button *lvl3;
    int tmp;
public:
    void show_window();
    int get_lvl();
    void change_size();
 signals:
    void chosen();
    void buttonClicked(int buttonId);
};

#endif // DIF_LEVEL_H
