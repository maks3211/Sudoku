#include "notatki.h"


Notatki::Notatki(QWidget *parent)
    : QWidget{parent}
{
   for (int i = 0; i< 9  ; i++)
 {
   cyfry.append(new QLabel(this));// = new QLabel;
   cyfry[i] -> setText(QString::number(i+1));
   cyfry[i]->setStyleSheet("color: transparent");
 }
   set_pos(cyfry);

}



void Notatki::set_pos(QList <QLabel*>&c)
{
 int index = 0 ;
for (int i = 0 ; i<3 ;i++)
{
    for (int j = 0 ; j< 3; j++)
    {
       c[index]->move(65+15*j,56+15*i);
       index ++;

    }

}

}

void Notatki::set_notes(int val)
{


    if (cyfry[val-1]->palette().text().color() ==Qt::transparent)
    {
          cyfry[val-1]->setStyleSheet("color: black");

    }
    else
    {
       cyfry[val-1]->setStyleSheet("color: transparent");
    }

}

void Notatki::clear_notes()
{
    for (int j = 0 ; j< 9; j++)
    {
       cyfry[j]->setStyleSheet("color: transparent");
    }

}
