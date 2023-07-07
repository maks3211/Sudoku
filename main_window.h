#ifndef Main_Window_H
#define Main_Window_H
#include "gra.h"
#include"licznik.h"
#include"dif_level.h"
#include"statistics_window.h"
//#include"mistakes.h"
#include"my_button.h"
#include <QWidget>
#include<QVBoxLayout>
#include <QTimer>
#include <QLabel>
#include<QStackedWidget>
#include<QPropertyAnimation>
#include<QGraphicsAnchorLayout>
#include<memory>
class Main_Window : public QWidget
{
    Q_OBJECT

public:
    Main_Window(std::string user,QWidget *parent = nullptr);
    ~Main_Window();
      void closeEvent(QCloseEvent *event);
  public slots :
    void Start_gry();
    void Wstecz();
    void Show_instruction();
    void Go_menu();
    void Koniec();
    void Wznow();
    void Start_from_file();
    void Game_win();
void Statystyki();
signals:
void loggedOut();
    void buttonClicked();
    void closeApp();
private:
    bool confirm_exit;
    bool continuie;
    int stan = 0 ;
    std::string user;
    QStackedWidget *strony = new QStackedWidget;
    std::shared_ptr<QLabel>plansza;
    QWidget *widget1;
    QPropertyAnimation *nowa;
     std::shared_ptr<my_button>nowa_gra_button;
     std::shared_ptr<my_button>wznow_button;
     std::shared_ptr<my_button>stat_button;
     std::shared_ptr<my_button>instrukcja_button;
     std::shared_ptr<my_button>wstecz_instrukcja;
     std::shared_ptr<my_button>wyjdz_button;
     std::shared_ptr<my_button>wstecz;
     std::shared_ptr<my_button>wyloguj;
     std::shared_ptr<my_button>zapisz_button;
    std::shared_ptr<QLabel>zapis_label;
    std::shared_ptr<QLabel>uzytkownik;
    Licznik *licznik;
    Gra *gra;
    Statistics_Window *statystyki_okno;
    Dif_level *poziomik;
    int level;
    void Label_anim(QLabel *l);
    void make_Bigger(bool bigger);
private slots:
    void lvlchoose(int buttonId);
 void onLogoutButtonClicked();

};
#endif // Main_Window_H
