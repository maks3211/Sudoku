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
 * = 2 -> Nowa gra po wcisnieciu wstecz
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



uzytkownik = std::make_shared<QLabel>(widget1);
if (user == "gu")
{
uzytkownik->setText("Grasz jako Gość");
}
else
{
   uzytkownik->setText("Witaj, " + QString::fromStdString(user));
}

    nowa_gra_button = std::make_shared<my_button>("Nowa gra", widget1);
    wznow_button = std::make_shared<my_button>("Wznów", widget1);
    stat_button = std::make_shared<my_button>("Statystyki", widget1);
    instrukcja_button = std::make_shared<my_button>("Opis Gry", widget1);
    wyjdz_button = std::make_shared<my_button>("Wyjdź", widget1);
    wyloguj = std::make_shared<my_button>("Wyloguj się", widget1);
    wstecz = std::make_shared<my_button>("Wstecz", widget1);

    zapisz_button = std::make_shared<my_button>("Zapisz", widget1);
    zapisz_button->hide();

    zapis_label = std::make_shared<QLabel>("Zapisano",widget1);
    zapis_label->hide();

    int width = 125;
zapis_label->move((800-(width))/2 + 365,280);
   stat_button->setGeometry((800-(width))/2 , 250,125,42);
   zapisz_button->setGeometry((800-(width))/2 + 325, 300,125,42);
   nowa_gra_button->setGeometry((800-(width))/2 , 150,125,42);

    wznow_button->setGeometry((800-(width))/2 , 50,125,42);


    instrukcja_button->setGeometry((800-(width))/2 , 350,125,42);

    wyjdz_button->setGeometry((800-(width))/2 , 750,125,42);

    wyloguj->setGeometry((800-(width))/2 , 825,125,42);

    wstecz->setGeometry((800-(width))/2 , 650,125,42);
    wstecz->hide();


 connect(wyloguj.get(), &QPushButton::clicked, this,&Main_Window::onLogoutButtonClicked);



    licznik = new Licznik(widget1);
    licznik->move(680,25);
    licznik->hide();


    connect(wznow_button.get(), SIGNAL(clicked()) , this , SLOT(Wznow()));
        wznow_button->hide();



    plansza = std::make_shared<QLabel> (widget1); //251
    QPixmap zdjecie(":/Tex/Tex/Sudoku.png");
    QPixmap zdjeciemale =zdjecie.scaled(QSize(252, 252), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //Grafika sudoku
    plansza->setPixmap(zdjeciemale);
    plansza->setAlignment(Qt::AlignCenter);
    plansza->setGeometry(50, 50, zdjeciemale.width(), zdjeciemale.height());




    connect(wyjdz_button.get(), &QPushButton::clicked, this, &Main_Window::Koniec);







nowa = new QPropertyAnimation(plansza.get(), "size");
nowa->setDuration(350);
plansza->setScaledContents(true); // Ustawia, aby zdjęcie było wyskalowane i całe widoczne
plansza->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


QPropertyAnimation *animation2 = new QPropertyAnimation(nowa_gra_button.get(), "pos");
int endValue = nowa_gra_button->pos().x()+ 325;
animation2->setDuration(250);
animation2->setEndValue(QPoint(endValue, nowa_gra_button->pos().y()));
animation2->setPropertyName("pos");
QParallelAnimationGroup *group = new QParallelAnimationGroup;
group->addAnimation(animation2);







//strona 2 - Opis gry
    QWidget *widget2= new QWidget();


    QLabel *napis3 = new QLabel(widget2);
    napis3->setText("<center><font color='#0e0b78', size = 9><b>Zasady gry</b></font></center><br><font color= '#092D8C', size = 5>W celu wygrania gry należy uzupełnić całą planszę Sudoku. "
                    "<br>Dostępne są trzy poziomy trudności- wpływają one na liczbę uzupełnionych już pól."
                    "<br>Najlepszy wynik danego gracza umieszczony jest na pierwszej pozycji w tabeli."
                    "<br>Popełnienie trzech błędów skutkuje przerwaniem gry."
                    "<br>Do dyspozycji graczą są:"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Trzy podpowiedzi- uzupełniają one jedno losowe pole, które nie jest poprawnie rozwiązane"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Opcja notatek- wpisywane wartości nie są brane pod uwagę- w dane pole można wpisać kilka wartości"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Pauza- gracz w dowolnej chwili może zatrzymać rozgrywkę"
                    "<br><center><font size = 7><b>Punktacja</b></font></center>"
                    "<br>Gracz otrzymuje bazowo 10 000 punktów."
                    "<br>Na liczbę zdobydych punktów wpłyają następujące czynniki:"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Czas - od całego wyniku odejmowana jest liczba sekund potrzebych na rozwiązanie"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Poziom - gracz otrzymuje 2000 punktów za poziom łatwy, 4000 za poziom średni, 6000 za poziom trudny"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Błędy - za każdy błęd gracz traci 1000 punktów"
                    "<br>&nbsp;&nbsp;&nbsp;&nbsp;-Podpowiedzi - za każdą podpowiedź gracz traci 500 punktów"
                    "</font>");

    wstecz_instrukcja = std::make_shared<my_button>("Wstecz",widget2);
    wstecz_instrukcja->setGeometry(420,650,125,42);
    QVBoxLayout *layout2 = new QVBoxLayout();



QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

layout2->addWidget(napis3);
layout2->addItem(spacer);
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
    poziomik->move(nowa_gra_button->pos().x(),nowa_gra_button->pos().y()+35);
    poziomik->raise();

    connect(wstecz.get(), SIGNAL(clicked()) , this , SLOT(Go_menu()));
    connect(wstecz_instrukcja.get(), SIGNAL(clicked()) , this , SLOT(Show_instruction()));
    connect(instrukcja_button.get(), SIGNAL(clicked()) , this , SLOT(Show_instruction()));
    connect(stat_button.get(), SIGNAL(clicked()) , this , SLOT(Statystyki()));
    connect(nowa_gra_button.get(), &QPushButton::clicked,poziomik, &Dif_level::show_window);
    connect(nowa_gra_button.get(), &QPushButton::clicked, stat_button.get(), [=](){
        if (stat_button->isHidden())
        {
            stat_button->show();
            instrukcja_button->show();

        }
        else
        {
            stat_button->hide();
            instrukcja_button->hide();

        }
        });

        connect(poziomik,SIGNAL(chosen()), animation2, SLOT(start())); //group
        level =1;



    connect(poziomik, &Dif_level::buttonClicked, this, &Main_Window::lvlchoose);

    gra = new Gra(widget1,user);




    connect(gra,&Gra::was_saved,this, [=](){
        wznow_button->show();
        stan=2;
        continuie=true;});

    connect(wznow_button.get(), &QPushButton::clicked , gra,[=](){
        if(continuie)
        {
            QTime czas = licznik->getTime();
            gra->Load(czas,level);
            licznik->setTime(czas);
            continuie= false;
            connect(licznik, &Licznik::stopClicked, gra, &Gra::Pause);
        }
        });

gra->show_resume();


connect(gra,&Gra::new_signal,poziomik, &Dif_level::show_window);
connect(gra,&Gra::reset_time,licznik, &Licznik::reset);
connect(gra,&Gra::new_signal,licznik, [=](){ licznik->setEnabled(false); licznik->stop(); });
connect(poziomik, &Dif_level::chosen, licznik, [=](){ licznik->setEnabled(true);licznik->reset();licznik->start(); });
connect(zapisz_button.get(), &QPushButton::clicked, gra, [=]() {
    gra->Save(licznik->getTime(),level);
Label_anim(zapis_label.get());
});

connect(gra, &Gra::full_filled,this,&Main_Window::Game_win);
connect(statystyki_okno, &Statistics_Window::go_stat, stat_button.get(), &QPushButton::click); //Przejscie do statystyk z okienka po wyhranej
connect(statystyki_okno, &Statistics_Window::go_menu, wstecz.get(), &QPushButton::click);//Przejscie do menu glownego po wygranej

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
void Main_Window::Show_instruction() // Zmiana menu - instrukcja
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
              make_Bigger(true);
              stan =1;
              gra->Start_game(level);
              wznow_button->hide();
              stat_button->hide();
              licznik->show();
              licznik->start();
              connect(licznik, &Licznik::stopClicked, gra, &Gra::Pause);
              connect(zapisz_button.get(), &QPushButton::clicked, gra, [=]() {
                  gra->Save(licznik->getTime(),level);
                  Label_anim(zapis_label.get());
              });

        wstecz->show();
        if (user != "gu")
        {
          zapisz_button->show();
          zapisz_button->raise();
        }
       }
   else if (stan == 1)
{

       delete gra;
       gra = new Gra(widget1,user);

       connect(gra,&Gra::new_signal,licznik, [=](){ licznik->setEnabled(false); licznik->stop(); });
       gra->Start_game(level);
       connect(licznik, &Licznik::stopClicked, gra, &Gra::Pause);
       licznik->reset();
connect(gra,&Gra::reset_time,licznik, &Licznik::reset);
connect(gra,&Gra::new_signal,poziomik, &Dif_level::show_window);
connect(zapisz_button.get(), &QPushButton::clicked, gra, [=]() {
    gra->Save(licznik->getTime(),level);
    Label_anim(zapis_label.get());
});


connect(gra, &Gra::full_filled,this,&Main_Window::Game_win);
if (user != "gu")
{
    zapisz_button->raise();
}


}
        else if (stan == 2) // stworzenie nowej  gry jezeli dałem wstecz
    {     
        make_Bigger(true);
        delete gra;
        gra = new Gra(widget1,user);

        connect(gra,&Gra::new_signal,licznik, [=](){ licznik->setEnabled(false); licznik->stop(); });       
        connect(zapisz_button.get(), &QPushButton::clicked, gra, [=]() {
            gra->Save(licznik->getTime(),level);
             Label_anim(zapis_label.get());
        });

        gra->Start_game(level);     
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
        if (user != "gu")
                {
                  zapisz_button->show();
                  zapisz_button->raise();
                }
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
zapisz_button->hide();
uzytkownik->show();
    make_Bigger(false);
    gra->hide();
    licznik->stop();
    licznik->hide();
    QPropertyAnimation *animation3 = new QPropertyAnimation(nowa_gra_button.get(), "pos");
    int endValue = nowa_gra_button->pos().x()- 325;
    animation3->setDuration(250);
    animation3->setEndValue(QPoint(endValue, nowa_gra_button->pos().y()));
    animation3->setPropertyName("pos");
    animation3->start();

    wstecz->hide();
    stat_button->show();
    instrukcja_button->show();
    wznow_button->show();
    wyloguj->show();
    poziomik->hide();
}

void Main_Window::Wznow()
{
    qDebug() << "Wznow";
    if (user !="gu")
    {
        zapisz_button->show();
       // licznik->raise(); // to dodałem
       // gra->raise();
       // nowa_gra_button->raise();
       zapisz_button->raise();
    }

    uzytkownik->hide();
    if (stan == 2)
    {
        qDebug() << "STAN == 2";

                make_Bigger(true);
                QPropertyAnimation *animation3 = new QPropertyAnimation(nowa_gra_button.get(), "pos");
                int endValue = nowa_gra_button->pos().x()+ 325;
                animation3->setDuration(250);
                animation3->setEndValue(QPoint(endValue, nowa_gra_button->pos().y()));
                animation3->setPropertyName("pos");
                animation3->start();
                QObject::connect(animation3, &QPropertyAnimation::finished, [=]() {
                gra->show();
                gra->setEnabled(true);
                });


             //  gra->raise();
             //  licznik->raise();
             //  nowa_gra_button->raise();
             //  zapisz_button->raise();

               stat_button->hide();
               poziomik->hide();
               instrukcja_button->hide();
               wyloguj->hide();
               stan =1;
               wstecz->show();
               licznik->show();
               licznik->start();
               licznik->raise();
qDebug() << "gra: " << gra->geometry();
qDebug() << "licznik: " << licznik->geometry();

    }
}


void Main_Window::make_Bigger(bool bigger)
{
    if (bigger)
{//250
         poziomik->move(nowa_gra_button->pos().x()+315,nowa_gra_button->pos().y()+45);
poziomik->change_size();
        QSizeF startSize = plansza->size();
        QSizeF endSize = QSizeF(startSize.width() +258.552, startSize.height() +258.552);
      nowa->setStartValue(startSize);
        nowa->setEndValue(endSize);
        nowa->start();
        nowa->setEasingCurve(QEasingCurve::InOutSine);
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
        poziomik->change_size();
    poziomik->move(nowa_gra_button->pos().x()-315,nowa_gra_button->pos().y()+45);
    }
}



void Main_Window::Start_from_file() // connectemn z was_saved z gra
{
    stan =2;
    wznow_button->show();
}


void Main_Window::onLogoutButtonClicked()
{
    emit loggedOut();
    delete this;
}


void Main_Window::Game_win()
{
    licznik->stop();
    licznik->setEnabled(false);
    statystyki_okno->Win_Sumarry(level,gra->Get_mistakes(),gra->Get_hints_used(),licznik->getTime());    
}
void Main_Window::Label_anim(QLabel *l)
{
    l->show();
    QGraphicsOpacityEffect *e = new QGraphicsOpacityEffect(l);
    l->setGraphicsEffect(e);
    QPropertyAnimation *anim = new QPropertyAnimation(e, "opacity");
    anim->setDuration(250); // czas trwania animacji w ms
    anim->setStartValue(0); // wartość początkowa przezroczystości
    anim->setEndValue(1); // wartość końcowa przezroczystości
    anim->start();
//opoznienie animacji wygasania
    QTimer::singleShot(2500, [=]() { //1500
        anim->setStartValue(1.0);
        anim->setEndValue(0.0);
        anim->start(QPropertyAnimation::DeleteWhenStopped);
    });
}
