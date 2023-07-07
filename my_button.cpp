#include "my_button.h"
//Dodać jakieś metody na zmiane kolor np my_button->setcolor(wybór) np. słabo wygląda wybóR poziomow
my_button::my_button(QString str,QWidget *parent)
    : QPushButton{parent}
{

this->setStyleSheet("QPushButton {"
                    "border-radius: 10px;"
                    "background-color:rgb(52,94,229); "
                    "color:white;font-size:18px; }"
                    "QPushButton:hover:!pressed{background-color:rgb(28,72,225)}");
this->setText(str);

connect(this, &QPushButton::pressed, this, &my_button::make_bigger);


}


  void my_button::setColor(int r, int g, int b,int hr, int hg, int hb)
  {
      QString styleSheet = QString("QPushButton {"
                                       "border-radius: 10px;"
                                       "background-color: rgb(%1, %2, %3);"
                                       "color: white; font-size: 18px; }"
                                       ""
                                       "QPushButton:hover:!pressed { background-color: rgb(%4, %5, %6); }")
                                  .arg(r)
                                  .arg(g)
                                  .arg(b)
                                  .arg(hr)
                                  .arg(hg)
                                  .arg(hb);

//46 87 228

          this->setStyleSheet(styleSheet);


  }




   void my_button::make_bigger()
   {
       if (!isAnimationRunning) {
               isAnimationRunning = true;

               QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
               animation->setDuration(100);
               animation->setStartValue(this->geometry());
               animation->setEndValue(this->geometry().adjusted(-5, -5, 5, 5));
               connect(animation, &QPropertyAnimation::finished, this, [this]() {
                   isAnimationRunning = false;
                   make_smaller();
               });
               animation->start(QPropertyAnimation::DeleteWhenStopped);
           }
   }


   void my_button::make_smaller()
   {


       if (!isAnimationRunning) {
               isAnimationRunning = true;

               QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
               animation->setDuration(100);
               animation->setStartValue(this->geometry());
               animation->setEndValue(this->geometry().adjusted(5, 5, -5, -5));
               connect(animation, &QPropertyAnimation::finished, this, [this]() {
                   isAnimationRunning = false;
               });
               animation->start(QPropertyAnimation::DeleteWhenStopped);
           }
   }

   void my_button::setDisabled(bool disabled)
   {  
      if (disabled)
      { this ->QPushButton::setDisabled(disabled);
       this->setStyleSheet("QPushButton {"
                           "border-radius: 10px;"
                           "background-color:rgb(158,177,243); "
                           "color:red}"
                           "QPushButton:hover:!pressed{background-color:rgb(28,72,225)}");
   }
   else
      {
          this ->QPushButton::setDisabled(disabled);
          this->setStyleSheet("QPushButton {"
                              "border-radius: 10px;"
                              "background-color:rgb(52,94,229); "
                              "color:white}"
                              "QPushButton:hover:!pressed{background-color:rgb(28,72,225)}");

      }

   }


