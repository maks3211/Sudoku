#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include"user.h"
#include"my_button.h"
#include"login_window_reg.h"
#include"login_window_edit.h"
#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QVBoxLayout>
#include<QStackedWidget>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QTimer>
#include<QApplication>
class Login_Window : public QWidget
{
    Q_OBJECT
public:
    explicit Login_Window(QWidget *parent = nullptr);
std::string get_user();
private:
QStackedWidget *strony = new QStackedWidget;
QLabel *text;
QLabel *warrning;
my_button *quit_button;
my_button *login_button;
my_button *guest_button;
my_button *new_account;
my_button *edit;
QPushButton *back;
QLineEdit *login;
QLineEdit *password;
QVBoxLayout *layout1;
QWidget *page1= new QWidget(); // menu glowne
QWidget *page2= new QWidget(); // rejestracja
QWidget *page3= new QWidget(); // edycja
std::string log;
void show_warrning(int a); // a == 0 -> zly login a == 1 zle haslo
void register_page();
void clear_inputs();
private slots:
void Login_success(bool guest);
void Change_Page();

signals:
void logged(int user);
};

#endif // LOGIN_WINDOW_H
