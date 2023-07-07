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
#include"warnings.h"
#include"my_button.h"
#include"my_checkbox.h"
#include<memory>
class Login_Window_Edit : public QWidget
{
    Q_OBJECT
public:
    explicit Login_Window_Edit(QWidget *parent = nullptr);
private:
    std::shared_ptr<QLabel>text;  //opis
    std::shared_ptr<QLineEdit>login;
    std::shared_ptr<QLineEdit>password;
    std::shared_ptr<QLineEdit>new_thing;   // nowe hasło lub login
    std::shared_ptr<QLineEdit>new_thing_p;
    std::shared_ptr<my_button>edit;
    std::shared_ptr<my_button>back;
    std::shared_ptr<my_button>remove;
    std::shared_ptr<my_checkbox>choice_box;
    User u;
    Warnings *warnings;


void Edit_login();
void Edit_password();
public slots:
    void go_back_clicked();
private slots:
    void What_edit();
    void Delete_user();
    void Clear(int a); //czyszczenie pól tekstowych 0-login 1-haslo 2-nowe
signals:
void go_back();
};

#endif // LOGIN_WINDOW_EDIT_H
