#ifndef IN_GAME_H
#define IN_GAME_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
class In_Game : public QWidget
{
    Q_OBJECT
public:
    explicit In_Game(QWidget *parent = nullptr);

private:
   // QWidget *widget = new QWidget();
    QPushButton *notatki;
    QPushButton *podpowiedz;


};

#endif // IN_GAME_H
