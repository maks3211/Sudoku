#include "statistics_window.h"



Statistics_Window::Statistics_Window(std::string user,QWidget *parent)    : QWidget{parent}, user(user)
{

std::vector<Result> Wyniki_vec;

tabela = new QTableView(parent);
model = new QStandardItemModel(parent);
model->setHorizontalHeaderLabels({ "Wynik", "Czas gry", "Poziom trudności", "Ilość błędów", "Podpowiedzi" });

tabela->setModel(model);
tabela->setFixedSize(520,350);

brak_statystyk= std::make_shared<QLabel> (parent);
brak_statystyk->setText(" ");
brak_statystyk->setFixedSize(165,50);
brak_statystyk->move(590,5);

napis= std::make_shared<QLabel> (parent);
napis->setText("<font color='#0e0b78', size = 9><b>Statystyki</b></font><br>");
napis->setFixedSize(165,50);
napis->move(10,5);



back_button = std::make_shared<my_button>("Wstecz",parent);
back_button->setFixedSize(165,50);
//back_button->setText("Wstecz");
connect(back_button.get(), &QPushButton::clicked, this, &Statistics_Window::emit_go_back);

layout = new QVBoxLayout(parent);
player_choice = new QComboBox(parent);
player_choice->setFixedSize(150,50);

QString styleSheet = "QComboBox {"
                     "border-radius: 10px;" // Ustawienie zaokrąglonego narożnika
                     "padding: 5px 18px 1px 3px;" // Ustawienie marginesów wewnątrz komboboxa
                     "background-color: rgb(52,94,229);"
                     "font-size: 18px;" // Ustawienie rozmiaru tekstu głównego na 18px
                     "color: white;" // Ustawienie koloru tekstu
                     "}";


player_choice->setStyleSheet(styleSheet);



QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);


statystyki.Get_users(player_choice); // Dodanie użytkowników do listy
if(user!="gu")
{
    player_choice->setCurrentIndex(Get_user_num());
}
statystyki.Load(wyniki);


player_choice->currentIndex();

layout->addWidget(player_choice);
layout->addItem(spacer);
layout->addWidget(back_button.get());
layout->setAlignment(Qt::AlignCenter);
tabela->move(230 ,150);


Show_results(Get_user_num());



QObject::connect(player_choice, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index){
    Choice();
});
}


void Statistics_Window::Show_results(int player)
{

if (player != -1){

    Remove_rows();

    QString timeString;
    if (!wyniki[player].empty()){
        brak_statystyk->setText(" ");
     int best = statystyki.Get_best(player,wyniki);
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
    }
}
else
{
    Show_results(0);
}
}


void Statistics_Window::Choice()
{
Show_results(player_choice->currentIndex());
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
    model->insertRow(0, rowItems);
    }
}

 int Statistics_Window::Get_length(QString str, int i)
 {
   QString liczbaStr = QString::number(i);
   return str.length() - liczbaStr.length()-1 ;
 }



 void Statistics_Window::Remove_rows()
 {
     int rowCount = model->rowCount();
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
        emit go_menu();
     }
     else if (msgBox.clickedButton() == noButton)
     {  //Nowa gra
        emit go_stat();
     }
Show_results(Get_user_num());
 }


 int Statistics_Window::Get_user_num()
 {

  int index = player_choice->findText(QString::fromStdString(user));
  return index;

 }

 void Statistics_Window::emit_go_back()
 {
     emit go_back();
 }
