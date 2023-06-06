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
#include"warnings.h"

class Login_Window_Reg : public QWidget
{
    Q_OBJECT
//private:
private:
    QLabel *text;
    QLineEdit *login;
    QLineEdit *password;
    QLineEdit *password_p;
    QPushButton *reg;
    QPushButton *back;
    User u;
    QWidget *page1= new QWidget();
    Warnings *warnings;

    void bad_input(int a); //podanie błędnego hasła/ loginu
void Clear(int a);
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
