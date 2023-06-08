#ifndef LICZNIK_H
#define LICZNIK_H
#include <iostream>
#include <QWidget>
#include<QTime>
#include<QTimer>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QPropertyAnimation>

//dwa ponizesze do rozmycia tla
#include<QGraphicsEffect>
#include<QGraphicsBlurEffect>

class Licznik : public QWidget
{
    Q_OBJECT
public:
    explicit Licznik(QWidget *parent = nullptr);
bool is_pause= false;
public slots:
    void update();
    void stop();
    void start();
    void reset();
    void disable();
    QTime getTime();
    void setTime(QTime time);
signals:
    void stopClicked();
private:
   QTimer *licznik;
   QTime czas_rozpoczecia;
   int czas_gry_int;
bool win;
   QLabel *label_czas_gry;
   QPushButton *icon;
   QPropertyAnimation *small;
   QPropertyAnimation *big;
   QPropertyAnimation *change_icon;
public slots:
   void stopButtonClicked();

};

#endif // LICZNIK_H
