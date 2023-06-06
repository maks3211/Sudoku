#include "warnings.h"

Warnings::Warnings(QWidget *parent)
    : QWidget{parent}
{
    short_message = new QLabel(parent);
    short_message ->setFixedSize(180,38); //180,40
    short_message->setText("");
    short_message->setWordWrap(true);
    short_message->setAlignment(Qt::AlignCenter);
    short_message->setStyleSheet("QLabel{font-size:14px;}"  );

    long_message = new QLabel(parent);
    long_message->setText("");
    long_message ->setFixedSize(185,180);
    long_message->move(450,15);
    long_message->setStyleSheet("QLabel{font-size:14px;}"  );






}


void Warnings::Show(std::string which)
{
    if (which == "short")
    {
        short_message->show();
        QGraphicsOpacityEffect *e = new QGraphicsOpacityEffect(short_message);
        short_message->setGraphicsEffect(e);
        QPropertyAnimation *anim = new QPropertyAnimation(e, "opacity");
        anim->setDuration(250); // czas trwania animacji w ms
        anim->setStartValue(0); // wartość początkowa przezroczystości
        anim->setEndValue(1); // wartość końcowa przezroczystości
        anim->start();
    //opoznienie animacji wygasania
        QTimer::singleShot(2500, [=]() { //1500
            anim->setStartValue(1.0);
            anim->setEndValue(0.0);
            anim->start(QPropertyAnimation::DeleteWhenStopped);
        });
    }
    else if (which == "long")
    {
        QGraphicsOpacityEffect *e = new QGraphicsOpacityEffect(long_message);
        long_message->setGraphicsEffect(e);
        QPropertyAnimation *anim = new QPropertyAnimation(e, "opacity");
        anim->setDuration(250); // czas trwania animacji w ms
        anim->setStartValue(0); // wartość początkowa przezroczystości
        anim->setEndValue(1); // wartość końcowa przezroczystości
        anim->start();
    //opoznienie animacji wygasania
        QTimer::singleShot(3500, [=]() { //1500
            anim->setStartValue(1.0);
            anim->setEndValue(0.0);
            anim->start(QPropertyAnimation::DeleteWhenStopped);
        });


    }


}



void Warnings::Added_new_user()
{
     short_message ->setText("Dodano nowego użytkownika");
}

void Warnings::Bad_password()
{short_message->setStyleSheet("color:black");
     short_message ->setText("Hasło nie spełnia wymagań");
}

void Warnings::Bad_user_password()
{short_message->setStyleSheet("color:black");
     short_message ->setText("Złe hasło");
}

void Warnings::Repeated_login()
{short_message->setStyleSheet("color:black");
     short_message ->setText("Użytkownik o takiej nazwie istnieje");
}

void Warnings::No_user()
{short_message->setStyleSheet("color:black");
     short_message ->setText("Użytkownik o takiej nazwie nie istnieje");
}

void Warnings::Bad_login()
{short_message->setStyleSheet("color:black");
     short_message ->setText("Login nie spełnia wymagań");
}
void Warnings::Diff_passwords()
{short_message->setStyleSheet("color:black");
     short_message ->setText("Podane hasła różnią się od siebie");
}

void Warnings::Diff_logins()
{short_message->setStyleSheet("color:black");
     short_message ->setText("Podane loginy różnią się od siebie");
}

void Warnings::User_deleted()
{
    short_message->setStyleSheet("color:red");
    short_message ->setText("Konto zostało usunięte");

}


void Warnings::Change_made(std::string what)
{
    if (what =="login")
       { short_message->setStyleSheet("color:black");
      short_message ->setText("Login został zmieniony");}
    else if (what == "password")
      {    short_message->setStyleSheet("color:black");
       short_message ->setText("Hasło zostało zmienione");}
}




void Warnings::Pass_req()
{
    long_message->setText("\n\nHasło musi składać się z:\n1 małej litery\n1 wielkiej litery\n1 jednej cyfry\nz 4 do 20 znaków");
}
void Warnings::Login_req()
{
     long_message ->setText("Twój login musi składać sie z:\n4 do 20 znaków");
}

QLabel* Warnings::get_short_message()
{
    return short_message;
}
