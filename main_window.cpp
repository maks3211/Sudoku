#include "main_window.h"
#include "gra.h"
#include"licznik.h"
#include <QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QPen>
#include<QPainter>
#include<QPoint>
#include <QTimer>
#include<QPixmap>
#include<QPropertyAnimation>
#include<QParallelAnimationGroup>
#include<QMessageBox>
#include<QCloseEvent>



/*
 *              ZMIENNA STAN
 * = 0-> NOWA, GRA, BEZ SAVA
 * = 1-> GDY ROZPOCZNE GRE TO NA 1
 *
 *
*/

Main_Window::Main_Window(std::string user,QWidget *parent)
    :  QWidget(parent),user(user)
{




    setWindowTitle("Sudoku");
    resize(1000,900);  //prawo gora
    this->setMinimumSize(500,450);
    this->setMaximumSize(1000,900);
continuie=false;


    widget1 = new QWidget();
    QWidget *widget3 = new QWidget();  //STATYSTYKI

    statystyki_okno = new Statistics_Window(user,widget3);
    connect(statystyki_okno,&Statistics_Window::go_back,this,&Main_Window::Statystyki); //Wracanie do menu z Statystyki



uzytkownik = new QLabel(widget1);
if (user == "gu")
{
uzytkownik->setText("Grasz jako Gość");
}
else
{
   uzytkownik->setText("Witaj, " + QString::fromStdString(user));
}

    nowa_gra_button = new my_button("Nowa gra", widget1);
    wznow_button = new my_button("Wznów", widget1);
    stat_button = new my_button("Statystyki", widget1);
    instrukcja_button = new my_button("Opis Gry", widget1);
    wyjdz_button = new my_button("Wyjdź", widget1);
    wyloguj = new my_button("Wyloguj się", widget1);
    wyloguj->setGeometry((800-(wyjdz_button->width()))/2 , 825,125,42);



 //connect(wyjdz_button, &QPushButton::clicked, this, &Main_Window::Koniec);
 connect(wyloguj, &QPushButton::clicked, this,&Main_Window::onLogoutButtonClicked);
 nowa_gra_button->setFixedSize(125,42);
  //nowa_gra_button->setMaximumWidth(80);
  // nowa_gra_button->setMinimumWidth(80);

licznik = new Licznik(widget1);
licznik->hide();

  wznow_button->setGeometry((800-(wznow_button->width()))/2 , 50,125,42);
    connect(wznow_button, SIGNAL(clicked()) , this , SLOT(Wznow()));
if (!continuie)
{
wznow_button->hide();
}
else
{
wznow_button->hide();
}

    // Strona 1-> INDX 0
   // QWidget *widget1 = new QWidget();
    plansza = new QLabel (widget1); //251
    QPixmap zdjecie(":Tex/Sudoku.png");
    QPixmap zdjeciemale =zdjecie.scaled(QSize(252, 252), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //Grafika sudoku
    plansza->setPixmap(zdjeciemale);
    plansza->setAlignment(Qt::AlignCenter);
    plansza->setGeometry(50, 50, zdjeciemale.width(), zdjeciemale.height());


        wstecz = new my_button("Wstecz", widget1);
        wstecz->setFixedSize(125,42);
wstecz->hide();
        //QPushButton *nowa_guzik = new QPushButton("Nowa gra", widget1);
       // QPushButton *statystyki = new QPushButton("Statystyki", widget1);

        stat_button->setGeometry((800-(stat_button->width()))/2 , 250,125,42); //ZMIANA ROZMIARU PRZYCISKU - GDZIE, ROZMIAR
       // QPushButton *wznow = new QPushButton("Wznów", widget1);


       // QPushButton *wyjdz = new QPushButton("Wyjdź", widget1);
        wyjdz_button->setGeometry((800-(wyjdz_button->width()))/2 , 750,125,42);
        connect(wyjdz_button, &QPushButton::clicked, this, &Main_Window::Koniec);




//nowa_gra_button->raise();




int buttonWidth = wstecz->width();

//Licznik l;

wstecz->move((800-buttonWidth)/2 , 650);
nowa_gra_button->move((800-buttonWidth)/2 , 150);  // tak ma być srodek ekranu -> nowa_guzik->move((800-buttonWidth)/2 , 150);

//bez tego stat_button->move((800-buttonWidth)/2 , 250);

instrukcja_button->move((800-buttonWidth)/2 , 350);
instrukcja_button->setFixedSize(125,42);
  //instrukcja_button->setGeometry((800-(stat_button->width()))/2 , 350,80,50);


nowa = new QPropertyAnimation(plansza, "size");
nowa->setDuration(350);
plansza->setScaledContents(true); // Ustawia, aby zdjęcie było wyskalowane i całe widoczne
plansza->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



// !!!! !!! connect(nowa_gra_button, &QPushButton::clicked, std::bind(&Widget::Start_gry, this, plansza, nowa, gra)); !!!!

/* Zmieniona lambda na to co wyżej -/\ BIND TWORZY FUNKTOR
connect(nowa_guzik, &QPushButton::clicked, [=](){
if (stan == 0 ){
       QSize startSize = plansza->size();
       QSize endSize = QSize(startSize.width() * 2.026, startSize.height() * 2.026);

     //nowa->setStartValue(startSize);
       nowa->setEndValue(endSize);

       // uruchomienie animacji
       nowa->start();
       nowa->setEasingCurve(QEasingCurve::InOutSine);  // ustawienie interpolacji na algorytm Lanczos
       stan =1;
       gra->Start_game();
}
});
*/



QPropertyAnimation *animation2 = new QPropertyAnimation(nowa_gra_button, "pos");
int endValue = nowa_gra_button->pos().x()+ 250;
animation2->setDuration(250);
animation2->setEndValue(QPoint(endValue, nowa_gra_button->pos().y()));
animation2->setPropertyName("pos");
QParallelAnimationGroup *group = new QParallelAnimationGroup;

group->addAnimation(animation2);








//strona 2
    QWidget *widget2= new QWidget();


    QLabel *napis3 = new QLabel(widget2);
    napis3->setText("<center><font color='#0e0b78', size = 9><b>Zasady gry</b></font></center><br><font color= '#092D8C', size = 5>W celu wygrania gry należy uzupełnić całą planszę Sudoku. "
                    "<br>Dostępne są trzy poziomy trudności- wpływają one na liczbę uzupełnionych już pól."
                    "<br>Najlepszy wynik danego gracza umieszczony jest na pierwszej pozycji w tabeli"
                    "<br>Popełnienie trzech błędów skutkuje przerwaniem gry."
                    "<br>Do dyspozycji graczą są:"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Trzy podpowiedzi- uzupełniają one jedno losowe pole, które nie jest poprawnie rozwiązane."
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Opcja notatek- wpisywane wartości nie są brane pod uwagę- w dane pole można wpisać kilka wartości"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Pauza- gracz w dowolnej chwili może zatrzymać rozgrywkę"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Automatyczny zapis- gra jest automatycznie zapisywana"
                    "<br><center><font size = 7><b>Punktacja</b></font></center>"
                    "<br>Gracz otrzymuje bazowo 10 000 punktów."
                    "<br>Na liczbę zdobydych punktów wpłyają następujące czynniki:"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Czas - od całego wyniku odejmowana jest liczba sekund potrzebych na rozwiązanie"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Poziom - gracz otrzymuje 2000 punktów za poziom łatwy, 4000 za poziom średni, 6000 za poziom trudny"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Błędy - za każdy błęd gracz traci 1000 punktów"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Podpowiedzi - za każdą podpowiedź gracz traci 500 punktów"
                    "</font>");
    wstecz_instrukcja = new my_button("Wstecz",widget2);
    wstecz_instrukcja->setFixedSize(125,42);
    wstecz_instrukcja->move(420,650);
    QVBoxLayout *layout2 = new QVBoxLayout();






QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

   layout2->addWidget(napis3);
   layout2->addItem(spacer);
 //   layout2->addWidget(wstecz_instrukcja);
   widget2->setLayout(layout2);
layout2->setAlignment(Qt::AlignCenter);


    QVBoxLayout *layout3 = new QVBoxLayout();

  widget3->setLayout(layout3);

    strony->addWidget(widget1);
    strony->addWidget(widget2);
    strony->addWidget(widget3);


    strony->setCurrentWidget(0);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(strony);
    setLayout(mainLayout);
    poziomik = new Dif_level(this);
    poziomik->move(nowa_gra_button->pos().x(),nowa_gra_button->pos().y()+50);
 poziomik->raise();

 connect(wstecz, SIGNAL(clicked()) , this , SLOT(Go_menu()));
    connect(wstecz_instrukcja, SIGNAL(clicked()) , this , SLOT(Show_instruction()));
    connect(instrukcja_button, SIGNAL(clicked()) , this , SLOT(Show_instruction()));
   // instrukcja_button->move((800-buttonWidth)/2 , 250);
   //TUTAJ CONNECT POKAZYWANIA SAT
    connect(stat_button, SIGNAL(clicked()) , this , SLOT(Statystyki()));


    connect(nowa_gra_button, &QPushButton::clicked,poziomik, &Dif_level::show_window);
connect(nowa_gra_button, &QPushButton::clicked, stat_button, &QPushButton::hide);

    // !!  connect(nowa_gra_button, SIGNAL(clicked()), group, SLOT(start()));
        connect(poziomik,SIGNAL(chosen()), animation2, SLOT(start())); //group
level =1;



    connect(poziomik, &Dif_level::buttonClicked, this, &Main_Window::lvlchoose);
 //TO JEST DO RESETU

   //connect(poziomik,&Dif_level::chosen,this, std::bind(&Widget::Start_gry, this,  nowa));
  // connect(poziomik, &Dif_level::buttonClicked, [=](){
 //poziomik->move(800,800);
   //});


gra = new Gra(widget1,user);



//connect(gra, &Gra::was_saved, this, &Main_Window::Start_from_file); // zrobnic lambde do pokazania guzika

connect(gra,&Gra::was_saved,this, [=](){
    wznow_button->show();
    stan=2;
continuie=true;});

connect(wznow_button, &QPushButton::clicked , gra,[=](){
    if(continuie)
    {
        QTime czas = licznik->getTime();
        gra->Load(czas,level);
        qDebug() << "Wczytany poziom trudności: " << level;
        licznik->setTime(czas);
        continuie= false;
        connect(licznik, &Licznik::stopClicked, gra, &Gra::Pause);
    }

});

gra->show_resume();

//connect(wznow_button, &QPushButton::clicked , gra, &Gra::Load);
//gra->Load();
//connect(gra, &Gra::was_saved , gra, &Gra::Load);

connect(gra,&Gra::new_signal,poziomik, &Dif_level::show_window);

connect(gra,&Gra::reset_time,licznik, &Licznik::reset);


connect(gra,&Gra::new_signal,licznik, [=](){ licznik->setEnabled(false); licznik->stop(); });

connect(poziomik, &Dif_level::chosen, licznik, [=](){ licznik->setEnabled(true);licznik->reset();licznik->start(); });

/* OD TEGO
connect(this,&Main_Window::closeApp,gra,&Gra::Save);
connect(wstecz,&QPushButton::clicked,gra,&Gra::Save);
*/

connect(this, &Main_Window::closeApp, gra, [=]() {
    gra->Save(licznik->getTime(),level);

});
connect(wstecz, &QPushButton::clicked, gra, [=]() {
    gra->Save(licznik->getTime(),level);
});

connect(gra, &Gra::full_filled,this,&Main_Window::Game_win);


connect(statystyki_okno, &Statistics_Window::go_stat, stat_button, &QPushButton::click); //Przejscie do statystyk z okienka po wyhranej
connect(statystyki_okno, &Statistics_Window::go_menu, wstecz, &QPushButton::click);//Przejscie do menu glownego po wygranej




nowa_gra_button->raise();
}

Main_Window::~Main_Window()
{
}
void Main_Window::lvlchoose(int buttonId)
{
    if (buttonId == 1 || buttonId == 2 || buttonId == 3) {
           level = buttonId;
       }
     Start_gry();
     nowa_gra_button->raise();
}


void Main_Window::Statystyki()
{
    if ( strony->currentIndex() ==0) // jesli na menu glownym
    {
        strony->setCurrentIndex(2);  // idz to statsytki
    }
    else if ( strony->currentIndex() ==2) // jesli statystyki
    {
        strony->setCurrentIndex(0);  // idz to menu glowne
    }
}
void Main_Window::Show_instruction() // Zmiana menu
{


    if (strony->currentIndex() ==1)
    {
        strony->setCurrentIndex(0);

    }
    else if ( strony->currentIndex() ==0) // strona 0 - menu główne -> też podczas gry na stronie 0
    {

        strony->setCurrentIndex(1);

    }
}



void Main_Window::Go_menu() // Zmiana menu
{

if ( strony->currentIndex() ==0)
{
    Wstecz();
            stan = 2;
}
}


void Main_Window::Start_gry() // zwieksza rozmiar planszy+ pokazuje liczby
{
wstecz->show();
uzytkownik->hide();
    if (stan == 0 ){//rozpoczynamy od małej planszy - nowa gra
        qDebug() <<"Nowa gra ";
             // poziomik->move(nowa_gra_button->pos().x()+250,nowa_gra_button->pos().y()+50);
             make_Bigger(true);
              stan =1;
              gra->Start_game(level);
              wznow_button->hide();
              stat_button->hide();
              licznik->show();
              licznik->start();
              qDebug()<< "PIERWSZA GIERKA";
              connect(licznik, &Licznik::stopClicked, gra, &Gra::Pause);
              //tu dałem
              /*od tego
              connect(wstecz,&QPushButton::clicked,gra,&Gra::Save);
              connect(this,&Main_Window::closeApp,gra,&Gra::Save);
              */


              connect(this, &Main_Window::closeApp, gra, [=]() {
                  gra->Save(licznik->getTime(),level);
              });
              connect(wstecz, &QPushButton::clicked, gra, [=]() {
                  gra->Save(licznik->getTime(),level);
              });





wstecz->show();
       }
   else if (stan == 1)
{

       delete gra;
       gra = new Gra(widget1,user);

       connect(gra,&Gra::new_signal,licznik, [=](){ licznik->setEnabled(false); licznik->stop(); });
       gra->Start_game(level);
       // gra->Reset(); ??
          connect(licznik, &Licznik::stopClicked, gra, &Gra::Pause);
        licznik->reset();
connect(gra,&Gra::reset_time,licznik, &Licznik::reset);
connect(gra,&Gra::new_signal,poziomik, &Dif_level::show_window);
// tu dałem
/*od tego
connect(wstecz,&QPushButton::clicked,gra,&Gra::Save);
connect(this,&Main_Window::closeApp,gra,&Gra::Save);
*/
connect(this, &Main_Window::closeApp, gra, [=]() {
    gra->Save(licznik->getTime(),level);
});
connect(wstecz, &QPushButton::clicked, gra, [=]() {
    gra->Save(licznik->getTime(),level);
});

connect(gra, &Gra::full_filled,this,&Main_Window::Game_win);


        qDebug()<< "NOWA GIERKA: " << level;
}
        else if (stan == 2) // stworzenie nowej  gry jezeli dałem wstecz
    {
        //poziomik->move(nowa_gra_button->pos().x()+250,nowa_gra_button->pos().y()+50);
        make_Bigger(true);
        delete gra;
        gra = new Gra(widget1,user);

        connect(gra,&Gra::new_signal,licznik, [=](){ licznik->setEnabled(false); licznik->stop(); });
        //tu dałem

        /*od tego
        connect(wstecz,&QPushButton::clicked,gra,&Gra::Save);
        connect(this,&Main_Window::closeApp,gra,&Gra::Save);
        */
        connect(this, &Main_Window::closeApp, gra, [=]() {
            gra->Save(licznik->getTime(),level);
        });
        connect(wstecz, &QPushButton::clicked, gra, [=]() {
            gra->Save(licznik->getTime(),level);
        });


        gra->Start_game(level);
        // gra->Reset(); ??
           connect(licznik, &Licznik::stopClicked, gra, &Gra::Pause);
         licznik->reset();
         licznik->show();
         licznik->start();
         connect(gra,&Gra::reset_time,licznik, &Licznik::reset);
        connect(gra,&Gra::new_signal,poziomik, &Dif_level::show_window);
        stan =1;
        wznow_button->hide();
        stat_button->hide();
        connect(gra, &Gra::full_filled,this,&Main_Window::Game_win);
    }


}




//Do przycisku koniec
void Main_Window::Koniec()
{
    QMessageBox::StandardButton potwierdz;
        potwierdz = QMessageBox::question(this, "Sudoku", "Czy na pewno chcesz opuścić aplikację?", QMessageBox::Yes | QMessageBox::No);
        if (potwierdz == QMessageBox::Yes)
        {
            emit closeApp();
            confirm_exit= true;
            this->close();

        }


}




//Do krzyzyka z windowsa
void Main_Window::closeEvent(QCloseEvent *event)
{
    if (!confirm_exit){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Sudoku", "Czy na pewno chcesz wyjść z aplikacji?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // zamknięcie aplikacji
        emit closeApp();
        event->accept();
    } else {
        // zablokowanie zamknięcia aplikacji
        event->ignore();
    }
    }
}

void Main_Window::Wstecz() // Powrót do menu głównego podczas gry.
{

uzytkownik->show();
    make_Bigger(false);
    gra->hide();
    licznik->stop();
    licznik->hide();
    QPropertyAnimation *animation3 = new QPropertyAnimation(nowa_gra_button, "pos");
    int endValue = nowa_gra_button->pos().x()- 250;
    animation3->setDuration(250);
    animation3->setEndValue(QPoint(endValue, nowa_gra_button->pos().y()));
    animation3->setPropertyName("pos");
    animation3->start();


    //
    wstecz->hide();
    stat_button->show();
    wznow_button->show();
}

void Main_Window::Wznow()
{
    uzytkownik->hide();
    if (stan == 2)
    {
                make_Bigger(true);
                QPropertyAnimation *animation3 = new QPropertyAnimation(nowa_gra_button, "pos");
                int endValue = nowa_gra_button->pos().x()+ 250;
                animation3->setDuration(250);
                animation3->setEndValue(QPoint(endValue, nowa_gra_button->pos().y()));
                animation3->setPropertyName("pos");
                animation3->start();
                QObject::connect(animation3, &QPropertyAnimation::finished, [=]() {
                gra->show();
                qDebug()<<"Njanowsza zmiana";

               gra->setEnabled(true);


 });
qDebug() << "TUTAJ";
               licznik->show();
               licznik->start();

               wstecz->show();
               stan =1;
    }
}


void Main_Window::make_Bigger(bool bigger)
{
    if (bigger)
{
         poziomik->move(nowa_gra_button->pos().x()+250,nowa_gra_button->pos().y()+50);
        QSizeF startSize = plansza->size();
        QSizeF endSize = QSizeF(startSize.width() +258.552, startSize.height() +258.552);
      nowa->setStartValue(startSize);
        nowa->setEndValue(endSize);
        nowa->start();
        nowa->setEasingCurve(QEasingCurve::InOutSine); //InOutSine
qDebug() << "zwiekszanie";
    }
    else if (!bigger)
    {

        QSizeF startSize = plansza->size();
        QSizeF endSize = QSizeF(startSize.width() -258.552, startSize.height() -258.552);
        nowa->setStartValue(startSize);
        nowa->setEndValue(endSize);
        // uruchomienie animacji
        nowa->start();
        nowa->setEasingCurve(QEasingCurve::InOutSine);
qDebug() << "zmniejszanie";
    poziomik->move(nowa_gra_button->pos().x()-250,nowa_gra_button->pos().y()+50);
    }
}



void Main_Window::Start_from_file() // connectemn z was_saved z gra
{
    stan =2;
    wznow_button->show();
}


void Main_Window::onLogoutButtonClicked()
{
    qDebug()<<"Wylogowano";

    emit loggedOut();
    delete this;
}


void Main_Window::Game_win()
{
    licznik->stop();
    licznik->setEnabled(false);
    statystyki_okno->Win_Sumarry(level,gra->Get_mistakes(),gra->Get_hints_used(),licznik->getTime());    

}
