#include "dif_level.h"


Dif_level::Dif_level(QWidget *parent)
    : QWidget{parent}
{

    lvl1= new  my_button("Łatwy",this);
    lvl2= new  my_button("Średni",this);
    lvl3= new  my_button("Trudny",this);
    napis= new QLabel(this);


lvl1->setFixedSize(75,40);
lvl2->setFixedSize(75,40);
lvl3->setFixedSize(75,40);

napis->setText("Wybierz poziom trudności");
napis->move(0,15);

lvl1->move(30,40);
lvl2->move(30,90);
lvl3->move(30,140);

lvl1->setColor(83,117,234,46,87,228);
lvl2->setColor(83,117,234,46,87,228);
lvl3->setColor(83,117,234,46,87,228);




lvl1->resize(125, 125);


this->setFixedSize(150,190);
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

}



void Dif_level::show_window()
{
if (this->isHidden())
  { this->show();
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(220); // czas trwania animacji w ms
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


void Dif_level::change_size()
{
    if (lvl1->width()!=110)
    {
    lvl1->setFixedSize(110,40);
    lvl2->setFixedSize(110,40);
    lvl3->setFixedSize(110,40);
    napis->move(10,15);
    }
    else
    {
        lvl1->setFixedSize(75,40);
        lvl2->setFixedSize(75,40);
        lvl3->setFixedSize(75,40);
        napis->move(0,15);
    }
}
