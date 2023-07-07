#ifndef WARNINGS_H
#define WARNINGS_H

#include <QWidget>
#include<QLabel>
#include<QTimer>
#include<QPropertyAnimation>
#include<QGraphicsOpacityEffect>
#include<memory>
class Warnings : public QWidget
{
    Q_OBJECT
public:
    explicit Warnings(QWidget *parent = nullptr);
   //Metody wyświetlajace krótkie komunikaty
    void Added_new_user();
    void Bad_password(); // złe hasło- nie spełnia wymagań
    void Bad_user_password(); //złe hasło- użytkownik podaje błędne hasło podczas logowania
    void Repeated_login();
    void No_user();
    void Bad_login();
    void Diff_passwords();
    void Diff_logins();
    void Change_made(std::string what);
    void User_deleted();
    //Metody wyświetlające pełne komunikaty
    void Pass_req();
    void Login_req();

    void Show(std::string which);

    QLabel* get_short_message();



private:
   std::shared_ptr<QLabel>short_message;
   std::shared_ptr<QLabel>long_message;




signals:

};

#endif // WARNINGS_H
