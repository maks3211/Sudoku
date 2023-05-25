#include "login_window_reg.h"

Login_Window_Reg::Login_Window_Reg(QWidget *parent)
    : QWidget{parent}
{
//layout1 = new QVBoxLayout(parent);
qDebug() << "Klasa rejestracji";

message = new QLabel(parent);
message->setText("");
message ->setFixedSize(185,180);
message->move(450,15);
message->setStyleSheet("QLabel{font-size:14px;}"  );



text = new QLabel (parent);
text->setText("<center><font color='#0e0b78', size = 9><b>Sudoku</b></font><br><font color= '#092D8C', size = 4>Zarejsetruj się</font><center>");









login = new QLineEdit(parent);
login->setPlaceholderText("Login");
login->setFixedSize(165,35);
login->setStyleSheet("QLineEdit {"
                        "border-radius: 15px;"
                        "background-color:white; "
                        "color:black;font-size:18px; }"
                        );

warrning = new QLabel(parent);
warrning ->setFixedSize(180,38); //180,40
warrning->setText("");
warrning->setWordWrap(true);
warrning->setAlignment(Qt::AlignCenter);
warrning->setStyleSheet("QLabel{font-size:14px;}"  );
//warrning->move(200,225);

password = new QLineEdit(parent);
password->setPlaceholderText("Hasło");
password->setEchoMode(QLineEdit::Password);
password->setFixedSize(165,35);
password->setStyleSheet("QLineEdit {"
                        "border-radius: 15px;"
                        "background-color:white; "
                        "color:black;font-size:18px; }"
                        );



password_p = new QLineEdit(parent);
password_p->setPlaceholderText("Powtórz hasło");
password_p->setEchoMode(QLineEdit::Password);
password_p->setFixedSize(165,35);
password_p->setStyleSheet("QLineEdit {"
                        "border-radius: 15px;"
                        "background-color:white; "
                        "color:black;font-size:18px; }"
                        );

reg = new QPushButton(parent);
reg ->setText("Zarejestruj się");
reg->setFixedSize(165,35);


back= new QPushButton(parent);
back ->setText("Wstecz");
back->setFixedSize(165,35);


QVBoxLayout *layout1 = new QVBoxLayout(parent);
QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);



layout1->addWidget(text);
layout1->addWidget(login);
layout1->addWidget(password);
layout1->addWidget(password_p);
layout1->addWidget(warrning);

layout1->addWidget(reg);
layout1->addWidget(back);
layout1->addItem(spacer);
layout1->setAlignment(Qt::AlignCenter);
this->setLayout(layout1);

connect(back, &QPushButton::clicked, this, &Login_Window_Reg::go_back_clicked);
connect(reg, &QPushButton::clicked, this, &Login_Window_Reg::add_account);
//page1->setLayout(layout1);
}


void Login_Window_Reg::go_back_clicked()
{
    emit go_back();
}



void Login_Window_Reg::add_account()
{

int a = u.addUser(login->text().toStdString(), password->text().toStdString(),password_p->text().toStdString());

       if (a == 0)
       {
          qDebug() << "DODANO LUDZIKA";
          show_warrning(a);

       }
       else if( a == 1)
       {
           qDebug() << "Zle haslo";
           show_warrning(a);
       }
       else if( a == 2)
       {
             qDebug() << "Uzytkownik istnieje";
             show_warrning(a);

       }
       else if( a == 3)
       {

             qDebug() << "Zly login";
             show_warrning(a);
       }

       else if( a == 4)
       {

             qDebug() << "Błednie powtórz haslo";
             show_warrning(a);
       }

}




void Login_Window_Reg::show_warrning(int a)
{
    if (a == 0)
    {
        warrning ->setText("Dodano nowego użytkownika");
    }
    else if (a == 1)
    {
       warrning ->setText("Podano złe hasło"); // 1 mala,  1 wielka, 1 cyfra, min 8 znakow, max 20 dla hasla
       bad_input(a);
      //  warrning ->setText("Hasło musi składać się z: \n -1 małej litery \n-1 wielkiej litery \n-1jednej cyfry \n -z 4 do 20 znaków");
    }
    else if (a == 2)
    {
       warrning ->setText("Użytkownik o takiej nazwie istnieje");
    }
    else if (a == 3)
    {
       bad_input(a);
       warrning ->setText("Podano zły login");
        //warrning ->setText("Twój login musi składać sie z 4 do 20 znaków");

    }
    else if (a == 4)
    {
       warrning ->setText("Podane hasła różnią się od siebie");
    }
        warrning->show();

        QGraphicsOpacityEffect *e = new QGraphicsOpacityEffect(warrning);
        warrning->setGraphicsEffect(e);
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

void Login_Window_Reg::bad_input(int a)
{
    if (a == 1)
    {
   message->setText("\n\nHasło musi składać się z:\n1 małej litery\n1 wielkiej litery\n1 jednej cyfry\nz 4 do 20 znaków");
    }
    else if (a == 3)
    {
   message ->setText("Twój login musi składać sie z:\n4 do 20 znaków");
    }
    QGraphicsOpacityEffect *e = new QGraphicsOpacityEffect(message);
    message->setGraphicsEffect(e);
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
