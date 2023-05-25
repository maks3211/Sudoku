#ifndef Main_Window_H
#define Main_Window_H
#include "gra.h"
#include"licznik.h"
#include"dif_level.h"
//#include"mistakes.h"
#include"my_button.h"
#include <QWidget>
#include<QVBoxLayout>
#include <QTimer>
#include <QLabel>
#include<QStackedWidget>
#include<QPropertyAnimation>
#include<QGraphicsAnchorLayout>
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
    void Nowe_okno();
    void Koniec();
    void Wznow();
    void Start_from_file();
void Statystyki();
signals:
    void buttonClicked();
    void closeApp();
private:
    bool confirm_exit;
    bool continuie;
    int stan = 0 ;
    std::string user;
    QStackedWidget *strony = new QStackedWidget;


   // QPixmap scaledImage;
   // QLabel zdjlabel;
    QLabel *plansza;
    QWidget *widget1;
    QPropertyAnimation *nowa;
  //  QPushButton *nowa_gra_button;
    my_button *nowa_gra_button;
    QPushButton *wznow_button;
    QPushButton *stat_button;
    QPushButton *wyjdz_button;
    QPushButton *wstecz;
    Licznik *licznik;
    Gra *gra;
    //
     Dif_level *poziomik;
    int level;
    void make_Bigger(bool bigger);
private slots:
    void lvlchoose(int buttonId);


};
#endif // Main_Window_H
