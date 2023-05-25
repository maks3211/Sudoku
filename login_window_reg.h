#ifndef LOGIN_WINDOW_REG_H
#define LOGIN_WINDOW_REG_H

#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QVBoxLayout>
#include<QStackedWidget>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QTimer>
#include<QPoint>
#include"user.h"

class Login_Window_Reg : public QWidget
{
    Q_OBJECT
//private:
private:
    QLabel *text;
    QLineEdit *login;
    QLineEdit *password;
    QLineEdit *password_p;
    QLabel *warrning;
    QLabel *message; //warunki loginu hasla
    QPushButton *reg;
    QPushButton *back;
    User u;
    void show_warrning(int a); // a == 0 -> zly login a == 1 zle haslo
    void bad_input(int a); //podanie błędnego hasła/ loginu
    QWidget *page1= new QWidget();
public:
    explicit Login_Window_Reg(QWidget *parent = nullptr);
public slots:
    void go_back_clicked();
private slots:
    void add_account();
signals:
void go_back();
};

#endif // LOGIN_WINDOW_REG_H
