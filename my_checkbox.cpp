#include "my_checkbox.h"

my_checkbox::my_checkbox(QWidget *parent)
    : QCheckBox{parent}
{

    setStyleSheet("QCheckBox::indicator {"
                      "width: 200px;"
                      "height: 40px;"
                      "background-color: transparent;"
                      "}");





       QLabel *ramka = new QLabel(this);
       QPixmap pixmap1(":/Tex/Tex/ramka.png");
       pixmap1 = pixmap1.scaled(QSize(75, 75), Qt::KeepAspectRatio, Qt::SmoothTransformation);
       ramka->setPixmap(pixmap1);
       ramka->setAlignment(Qt::AlignCenter);
       ramka->setFixedSize(80,35);
ramka->move(35,0);

       QLabel *kula = new QLabel(this);
       QPixmap pixmap2(":/Tex/Tex/kula.png");
       pixmap2 = pixmap2.scaled(QSize(22, 22), Qt::KeepAspectRatio, Qt::SmoothTransformation);
       kula->setPixmap(pixmap2);
       kula->setAlignment(Qt::AlignCenter);
       kula->move(44,6);





       connect(this, &QCheckBox::toggled, this, [kula](bool checked) {
           if (checked) {
               QPropertyAnimation *animation = new QPropertyAnimation(kula, "pos");
               animation->setDuration(100);  // Czas trwania animacji w milisekundach
               animation->setStartValue(kula->pos());  // Początkowa pozycja kuli
               animation->setEndValue(kula->pos() + QPoint(40, 0));  // Końcowa pozycja kuli (przesunięcie o -100 pikseli w lewo)
               animation->start();  // Uruchomienie animacji
           }
       });

       connect(this, &QCheckBox::toggled, this, [kula](bool checked) {
           if (!checked) {
               QPropertyAnimation *animation = new QPropertyAnimation(kula, "pos");
               animation->setDuration(100);  // Czas trwania animacji w milisekundach
               animation->setStartValue(kula->pos());  // Początkowa pozycja kuli
               animation->setEndValue(kula->pos() + QPoint(-40, 0));  // Końcowa pozycja kuli (przesunięcie o -100 pikseli w lewo)
               animation->start();  // Uruchomienie animacji
           }
       });
}


void my_checkbox::setLeftText(QString text)
{
    QLabel *label = new QLabel(this);
    label->move(0,6);
    label ->setText(text);
   // QFont font = ;
   // font.setPointSize(10);

    QFont font = label->font();
    font.setPointSize(11);
    label->setFont(font);



}

void my_checkbox::setRightText(QString text)
{
    QLabel *label = new QLabel(this);
    label->move(115,6);
    label ->setText(text);

    QFont font = label->font();
    font.setPointSize(11);
    label->setFont(font);

}



