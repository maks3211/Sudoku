#include "licznik.h"



Licznik::Licznik(QWidget *parent)
    : QWidget{parent}
{





QFont font("Arial Rounded MT Bold", 13);
icon = new QPushButton(this);
connect(icon, &QPushButton::clicked, this, &Licznik::stopButtonClicked);
icon->setIcon(QIcon(":/Tex/Tex/pause.png"));
icon->setIconSize(QSize(60,60));
icon->setStyleSheet("background-color: transparent" );
icon->setFixedSize(60,60);
icon->move(820,27);

czas_rozpoczecia = QTime(0,0,0);
licznik = new QTimer(this);
connect(licznik, SIGNAL(timeout()), this, SLOT(update()));
czas_gry_int = 0;
label_czas_gry = new QLabel("00:00:00", this);
label_czas_gry->setFont(font);
label_czas_gry->setAlignment(Qt::AlignCenter);

label_czas_gry->setFixedSize(135, 65);
label_czas_gry->move(680,25);
label_czas_gry->setStyleSheet("QLabel { border: 3px solid grey; border-radius: 6px; background-color:white}");





big = new QPropertyAnimation(icon,"iconSize");
big->setDuration(85);
big->setEndValue(QSize(10,10));
big->setEndValue(QSize(60,60));


small = new QPropertyAnimation(icon,"iconSize");
small->setDuration(85);
small->setEndValue(QSize(10,10));



connect(icon,  SIGNAL(clicked()), small,  SLOT(start()));
connect(icon, SIGNAL(clicked()), this, SLOT(stop()));
connect(small, &QPropertyAnimation::finished, [=]() {
  if (is_pause)
    {
      icon->setIcon(QIcon(":/Tex/Tex/play.png"));
    }
  else
  {
    icon->setIcon(QIcon(":/Tex/Tex/pause.png"));
  }
    big->start();
});

}


void Licznik::update()
{

       czas_gry_int++;
       QTime czas_gry = czas_rozpoczecia.addSecs(czas_gry_int);
       QString czas_gry_str = czas_gry.toString("hh:mm:ss");
       label_czas_gry->setText(czas_gry_str);
}

void Licznik::stop()
{
    if (!is_pause)
  {
    licznik->stop();
    is_pause=true;
    }
    else
    {
       licznik->start();
       is_pause=false;
    }
}

void Licznik::start()
{
    licznik->start(1000);
    icon->setIcon(QIcon(":/Tex/Tex/pause.png"));
    is_pause=false;
}

void Licznik::reset()
{
czas_gry_int = -1;
update();
}

QTime Licznik::getTime()
{
return czas_rozpoczecia.addSecs(czas_gry_int);
}

void  Licznik::stopButtonClicked()
{
    emit stopClicked();
}

void Licznik::disable()
{
    this->hide();
}
void Licznik::setTime(QTime time)
{
    czas_rozpoczecia = time;
}
