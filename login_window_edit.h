#ifndef LOGIN_WINDOW_EDIT_H
#define LOGIN_WINDOW_EDIT_H

#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QVBoxLayout>
#include<QStackedWidget>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QTimer>
#include<QCheckBox>
#include<QPoint>
#include"user.h"


class Login_Window_Edit : public QWidget
{
    Q_OBJECT
public:
    explicit Login_Window_Edit(QWidget *parent = nullptr);
private:
   QLabel *text;  //opis
    QLineEdit *login;
    QLineEdit *password;
    QLineEdit *new_thing;   // nowe hasło lub login
    QLineEdit *new_thing_p;
    QLabel *warrning;  //Jeżeli użytkownik nie istnieje lub złe stare hasło
   // QLabel *message; //warunki loginu hasla
    QPushButton *edit;
    QPushButton *back;
    QCheckBox *choice_box;
    User u;


public slots:
    void go_back_clicked();
private slots:
    void What_edit();
signals:
void go_back();
};

#endif // LOGIN_WINDOW_EDIT_H
