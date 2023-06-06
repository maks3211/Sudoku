#include "statistics_window.h"



Statistics_Window::Statistics_Window(std::string user,QWidget *parent)    : QWidget{parent}, user(user)
{
qDebug() << "KOnsturkot" << QString::fromStdString(user) ;
std::vector<Result> Wyniki_vec;

tabela = new QTableView(parent);
model = new QStandardItemModel(parent);
model->setHorizontalHeaderLabels({ "Wynik", "Czas gry", "Poziom trudności", "Ilość błędów", "Podpowiedzi" });

tabela->setModel(model);
tabela->setFixedSize(520,350);

brak_statystyk= new QLabel (parent);
brak_statystyk->setText(" ");
brak_statystyk->setFixedSize(165,50);
brak_statystyk->move(590,5);

napis= new QLabel (parent);
napis->setText("<font color='#0e0b78', size = 9><b>Statystyki</b></font><br>");
napis->setFixedSize(165,50);
napis->move(10,5);



back_button = new QPushButton(parent);
back_button->setFixedSize(165,50);

back_button->setText("Wstecz");
connect(back_button, &QPushButton::clicked, this, &Statistics_Window::emit_go_back);

layout = new QVBoxLayout(parent);
player_choice = new QComboBox(parent);
player_choice->setFixedSize(165,50);
int a =2;
int b =2;


//player_choice->move( (800-player_choice->width())/2 , 150);


QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

 //spacer->changeSize(125,120);

statystyki.Get_users(player_choice); // Dodanie użytkowników do listy
if(user!="gu")
{
    player_choice->setCurrentIndex(Get_user_num());
}
statystyki.Load(wyniki);


player_choice->currentIndex();


layout->addWidget(player_choice);
//layout->addItem(spacer);
//layout->addWidget(brak_statystyk);
layout->addItem(spacer);
//layout->addWidget(tabela);
layout->addWidget(back_button);
layout->setAlignment(Qt::AlignCenter);
qDebug() <<"ROZMIAR: " <<tabela->width();
tabela->move(230 ,150);




//TU WSTAWIC METODE ZWRACJACA NUMER USERA
Show_results(Get_user_num());
//Set_best(0);


QObject::connect(player_choice, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index){
    qDebug() << "Wybrany indeks: " << index;
    Choice();
});
}


void Statistics_Window::Show_results(int player)
{

if (player != -1){

    Remove_rows();

    QString timeString;
    qDebug()<<"przd best";
    if (!wyniki[player].empty()){
        brak_statystyk->setText(" ");
     int best = statystyki.Get_best(player,wyniki);
         qDebug() << "PPo best";
    QList<QStandardItem*> rowItems;
     rowItems.append(new QStandardItem( QString::number(wyniki[player][best].result)));
     rowItems.append(new QStandardItem(wyniki[player][best].time.toString("hh:mm:ss")));
     rowItems.append(new QStandardItem(Get_level(player,best)));
     rowItems.append(new QStandardItem(QString::number(wyniki[player][best].mistakes)));
     rowItems.append(new QStandardItem(QString::number(wyniki[player][best].hints)));
     model->appendRow(rowItems);


for (auto i = 0 ; i < wyniki[player].size() ; i++)
{
    if (i != best)
 {   timeString =  wyniki[player][i].time.toString("hh:mm:ss");

QList<QStandardItem*> rowItems;
rowItems.append(new QStandardItem( QString::number(wyniki[player][i].result)));
rowItems.append(new QStandardItem(timeString));
rowItems.append(new QStandardItem(Get_level(player,i)));
rowItems.append(new QStandardItem(QString::number(wyniki[player][i].mistakes)));
rowItems.append(new QStandardItem(QString::number(wyniki[player][i].hints)));


model->appendRow(rowItems);
    }
    }
}
    else {
brak_statystyk->setText("Brak zapisanych statystyk");
        qDebug() << "Nie ma best - psuty plik";
    }
}
else
{
    Show_results(0);
}
}


void Statistics_Window::Choice()
{
qDebug() << player_choice->currentIndex();
Show_results(player_choice->currentIndex());
//Set_best(player_choice->currentIndex());
}


QString Statistics_Window::Get_level(int p, int i)
{
    int level =-1;
if ( p == -1)
{
    level = i;
}
else
{
    level =wyniki[p][i].lvl;
}

if (level == 1)
  {
    return "Łatwy";

}
 else if (level == 2)
{
     return "Średni";
}
else
{

    return "Trudny";
}
}

void Statistics_Window::Set_best(int player)
{
    if (player !=-1)
   { int best = statystyki.Get_best(player,wyniki);

    model->removeRow(best+1);


    QList<QStandardItem*> rowItems;
    rowItems.append(new QStandardItem( wyniki[player][best].result));
    rowItems.append(new QStandardItem(wyniki[player][best].time.toString("hh:mm:ss")));
    rowItems.append(new QStandardItem(Get_level(player,best)));
    rowItems.append(new QStandardItem(wyniki[player][best].mistakes));
    rowItems.append(new QStandardItem(wyniki[player][best].hints));
    //model->appendRow(rowItems);
    model->insertRow(0, rowItems);


  // lista->takeItem(best+1);
  // lista->insertItem(1,QString::number(wyniki[player][best].result)+ QString(" ").repeated(Get_length("Punkty   ",wyniki[player][best].result)) +Get_level(player,best) +QString(" ").repeated(Get_length("Poziom Trudności   ",Get_level(player,best).length())-3)+wyniki[player][best].time.toString("hh:mm:ss")+ QString(" ").repeated(Get_length("Czas Gry   ",8))+QString::number(wyniki[player][best].mistakes)+ QString(" ").repeated(Get_length("Ilość błędów   ",wyniki[player][best].mistakes))  +QString::number(wyniki[player][best].hints));


  //USTAWIEANIE KOLORU
  // QListWidgetItem* item = lista->item(1);
  // item->setForeground(QColor(66, 126, 227));
    }
}

 int Statistics_Window::Get_length(QString str, int i)
 {
   QString liczbaStr = QString::number(i);
   qDebug() <<str <<"Liczba str: " << liczbaStr.length() << "Długos napisu " << str.length() << "Ile spacji " <<str.length() - liczbaStr.length()+3 ;
   return str.length() - liczbaStr.length()-1 ;
   //return 10;
 }


/*ZWRACANIE NUMERU GRACZA
QString targetText = "user1";
int currentIndex = comboBox->currentIndex();
QString currentText = comboBox->currentText();
if (currentText == targetText) {
    // Aktualnie wybrany element ma tekst "user1"
    // Indeks jest przechowywany w zmiennej 'currentIndex'
    // Można wykonać odpowiednie operacje na elemencie
} else {
    // Aktualnie wybrany element nie ma tekstu "user1"
}
*/


 void Statistics_Window::Remove_rows()
 {
     // model->removeRows();
     int rowCount = model->rowCount();
      // model->clear();

     model->removeRows(0,rowCount);
 }



 void Statistics_Window::Win_Sumarry(int _lvl, int _m, int _h, QTime _time)
 {
   if (user !="gu")
 {
   statystyki.Save(statystyki.Count(_lvl,_m,_h,_time),user,Get_user_num(),wyniki);
   statystyki.Count(_lvl,_m,_h,_time);
   }
     QString tekst = QString("<center><font size = 4><br>Twój wynik: %1<br>Czas: %2<br>Poziom trudności: %3<br>Liczba popełnionych błędów: %4<br> Liczba użytych podpowiedźi: %5</font><center>")
             .arg( statystyki.Count(_lvl,_m,_h,_time))
             .arg(_time.toString("hh:mm:ss"))
             .arg( Get_level(-1,_lvl))
             .arg(_m)
             .arg(_h);

     QMessageBox msgBox;
     msgBox.setWindowTitle("Wygrałeś");
     msgBox.setStyleSheet("width:200px; height:20");
     msgBox.setInformativeText("<center><font color= \"#3f73dd\" size = 6><b>Gratulacje</b></font><br><font color='black', size = 5><b>Udało Ci się wygrać</b></font><center>" + tekst);
     QPushButton* yesButton = msgBox.addButton("Menu Główne", QMessageBox::YesRole);
     QPushButton* noButton = msgBox.addButton("Statystyki", QMessageBox::NoRole);
     msgBox.exec();
     if (msgBox.clickedButton() == yesButton)
     { //Menu główne
         qDebug() << "Idz do menu";
        emit go_menu();
     }
     else if (msgBox.clickedButton() == noButton)
     {  //Nowa gra
         qDebug() << "Idz do stat";
        emit go_stat();
     }
Show_results(Get_user_num());
 }


 int Statistics_Window::Get_user_num()
 {

  int index = player_choice->findText(QString::fromStdString(user));
  qDebug() << "Numer usera: " << index;
  return index;

 }

 void Statistics_Window::emit_go_back()
 {
     emit go_back();
 }
