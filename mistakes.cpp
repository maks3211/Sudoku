#include "mistakes.h"

Mistakes::Mistakes(QWidget *parent)
    : QWidget{parent}
{
mistakes = new QLabel(this);
mistakes->setText("Błędy: 0/3");


/*info = new QLabel(this);
info ->setText("Koniec gry\nPopełniłeś 3 błędy");
reset = new QPushButton(this);
newgame = new QPushButton(this);

reset->setText("Druga szansa");
newgame->setText("Nowa gra");
ustaw->addWidget(info);
ustaw->addWidget(reset);
ustaw->addWidget(newgame);

this->raise();
*/
//this->setLayout(ustaw);
connect(this, SIGNAL(too_many()), this, SLOT(Loss()));

}




void Mistakes::Add_mistake()
{
  mis++;
if (mis < 3)
   {
   mistakes->setText("Błędy: "+ QString::number(mis) + "/3");
   }
else if (mis == 3)
    {
    mistakes->setText("Błędy: "+ QString::number(mis) + "/3");
    mistakes->setStyleSheet("color: red");
    emit too_many();  //KONIEC GRY
    }

}

void Mistakes::Loss()
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("Koniec gry");
    msgBox.setStyleSheet("width:200px; height:20");
    msgBox.setInformativeText("<center><font color='red', size = 6><b>Koniec gry</b></font><br><font color='black', size = 5>Masz 3 błedy, więc przegrywasz tę grę</font><center>");
//msgBox.setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);

    QPushButton* yesButton = msgBox.addButton("Nowa gra", QMessageBox::YesRole);
    QPushButton* noButton = msgBox.addButton("Powtórz", QMessageBox::NoRole);



    msgBox.exec();
    if (msgBox.clickedButton() == yesButton) { //reset
      mis = 0;
      mistakes->setStyleSheet("color: black");
       mistakes->setText("Błędy: "+ QString::number(mis) + "/3");
      emit new_game(2);
    } else if (msgBox.clickedButton() == noButton) {  //Nowa gra
      mis=0;
      mistakes->setStyleSheet("color: black");
       mistakes->setText("Błędy: "+ QString::number(mis) + "/3");
      emit new_game(1);
    }

}

int Mistakes::return_mis()
{
    return mis;
}
