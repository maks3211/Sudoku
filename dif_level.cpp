#include "dif_level.h"
//
// !!!! TEN EMIT CHOSEN CHYBA NIE POTRZEBY- BO I TAK SIE ROBI PRZEZ BUTTONcLICKED- WYKORZYSTANE W WIDGET.CPP

Dif_level::Dif_level(QWidget *parent)
    : QWidget{parent}
{

    lvl1= new  my_button("Łatwy",this);
    lvl2= new  QPushButton(this);
    lvl3= new  QPushButton(this);
    napis= new QLabel(this);

//lvl1->setText("Łatwy");
lvl1->setFixedSize(75,40);
lvl2->setText("Średni");
lvl3->setText("Trudny");
napis->setText("Wybierz poziom trudności");

lvl1->move(30,50);
lvl2->move(30,100);
lvl3->move(30,150);

this->setFixedSize(150,180);
this->hide();




connect(lvl1, &QPushButton::clicked, this, [=]() {
    emit buttonClicked(1);
    emit chosen();
    this->close();
});



connect(lvl2, &QPushButton::clicked, this, [=]() {
    emit buttonClicked(2);
    emit chosen();
    this->close();
});

connect(lvl3, &QPushButton::clicked, this, [=]() {
    emit buttonClicked(3);
    emit chosen();
    this->close();
});

qDebug() << "to powinno byc  :" << tmp << "---";
}



void Dif_level::show_window()
{
if (this->isHidden())
  { this->show();
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(150); // czas trwania animacji w ms
    animation->setStartValue(0); // wartość początkowa przezroczystości
    animation->setEndValue(1); // wartość końcowa przezroczystości
    animation->start();
    qDebug() << "sdf";
}
else // Ponownie wciśniecie powoduje ukrycie
{
    this->hide();
}
}

int Dif_level::get_lvl()
{

    return tmp;
}


