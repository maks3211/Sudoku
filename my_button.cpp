#include "my_button.h"
//Dodać jakieś metody na zmiane kolor np my_button->setcolor(wybór) np. słabo wygląda wybóR poziomow
my_button::my_button(QString str,QWidget *parent)
    : QPushButton{parent}
{

this->setStyleSheet("QPushButton {"
                    "border-radius: 10px;"
                    "background-color:rgb(52,94,229); "
                    "color:white;font-size:18px; }"
                    ""
                    "QPushButton:hover:!pressed{background-color:rgb(28,72,225)}");
this->setText(str);
//this->setEnabled(true);


    this->setFixedSize(125,42);

}
