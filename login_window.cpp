#include "login_window.h"

Login_Window::Login_Window(QWidget *parent)
    : QWidget{parent}
{

    setWindowTitle("Zaloguj się");
    resize(700,500);  //prawo gora
    this->setMinimumSize(233,166);
    this->setMaximumSize(700,500);

layout1 = new QVBoxLayout(page1);


text = new QLabel (page1);
text->setText("<center><font color='#0e0b78', size = 9><b>Sudoku</b></font><br><font color= '#092D8C', size = 4>Zaloguj się, aby kontynuować</font><center>");

warrning = new QLabel(page1);
warrning ->setFixedSize(175,25);
warrning->setText("");
warrning->setAlignment(Qt::AlignCenter);
warrning->setStyleSheet("QLabel{font-size:14px;}"  );



//warrning ->hide();
    //login = new QLineEdit(page1);
    login = new QLineEdit(this);
    login->setPlaceholderText("Login");
    login->setFixedSize(165,35);
    login->setStyleSheet("QLineEdit {"
                        "border-radius: 15px;"
                        "background-color:white; "
                        "color:black;font-size:18px; }"
                        );



    password = new QLineEdit(page1);
    password->setPlaceholderText("Hasło");
    password->setEchoMode(QLineEdit::Password);
   // password ->move(350,75);
    password->setFixedSize(165,35);
    password->setStyleSheet("QLineEdit {"
                        "border-radius: 15px;"
                        "background-color:white; "
                        "color:black;font-size:18px; }"
                        );



login_button = new QPushButton(page1);
login_button ->setText("Zaloguj się");
login_button->setFixedSize(165,35);




guest_button = new QPushButton(page1);
guest_button ->setText("Graj jako Gość");
guest_button->setFixedSize(165,35);

new_account=new QPushButton(page1);
new_account ->setText("Zarejestruj się");
new_account->setFixedSize(165,35);

edit = new QPushButton(page1);
edit ->setText("Edytuj konto");
edit->setFixedSize(165,35);







quit_button = new QPushButton(page1);
quit_button ->setText("Wyjdź");
quit_button->setFixedSize(165,35);


QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
layout1->addWidget(text);
layout1->addWidget(login);
layout1->addWidget(password);
layout1->addWidget(warrning);
layout1->addWidget(login_button);
layout1->addWidget(guest_button);
layout1->addWidget(new_account);
layout1->addWidget(edit);
layout1->addItem(spacer);
layout1->addWidget(quit_button);
layout1->setAlignment(Qt::AlignCenter);

page1->setLayout(layout1);
//setLayout(layout1);

//back = new QPushButton(page2);

//back->setText("Wstecz");
QVBoxLayout *mainLayout = new QVBoxLayout();
mainLayout->addWidget(strony);
setLayout(mainLayout);

QVBoxLayout *layout3 = new QVBoxLayout();
//layout3->addWidget(back);
//page2->setLayout(layout3);




strony->addWidget(page1);
strony->addWidget(page2);
strony->addWidget(page3);
strony->setCurrentWidget(0);
//setLayout(layout3);






connect(new_account, &QPushButton::clicked, [this]() {
   // QWidget *par = new QWidget();
   //register_page();

           strony->setCurrentIndex(1); // Wykonanie akcji setCurrentIndex(1)


});


connect(login_button, &QPushButton::clicked, [this]() {
    Login_success(0);
});

connect(guest_button, &QPushButton::clicked, [this]() {
    Login_success(1);

});



connect(quit_button, SIGNAL(clicked()), this, SLOT(close()));

//Okno rejestracji
Login_Window_Reg *reg = new Login_Window_Reg(page2);
connect (reg,&Login_Window_Reg::go_back,this,&Login_Window::Change_Page);
page2->setLayout(reg->layout());
login->setFocus();

//logowanie za pomocą entera
connect(login, &QLineEdit::returnPressed, login_button, &QPushButton::click);
connect(password, &QLineEdit::returnPressed, login_button, &QPushButton::click);


Login_Window_Edit *edit_w = new Login_Window_Edit(page3);
page3->setLayout(edit_w->layout());
connect(edit, SIGNAL(clicked()), this,  SLOT(Change_Page()));

connect(edit_w,&Login_Window_Edit::go_back,this,&Login_Window::Change_Page);

}


void Login_Window::Login_success(bool guest)
{
    if (guest)
    {
    qDebug ()<< "Zalogowanio sie jako gosc";
    log = "gu";
    emit logged(1);
    this->close();
    //qApp->exit();
    }
else
    {   
        User user;
        if(user.findUser(login->text().toStdString()))
     {   qDebug ()<< "Poprawny login";
            qDebug ()<< password->text();
        if(user.checkPassword(password->text().toStdString()))
        {
             qDebug ()<< "Zalogowanio sie";
             emit logged(2);
             this->close();
           //qApp->exit();
        }
        else
        {
         show_warrning(1);
        }
    }
    else {
        show_warrning(0);
         }

    }

}

void Login_Window::Change_Page()
{

    if ( strony->currentIndex() == 0) // jesli na menu glownym
    {
        qDebug() <<" zmiana strony ==0";
        qDebug() << strony->currentIndex();
        strony->setCurrentIndex(2);  //
    }
    else if ( strony->currentIndex() ==1 or strony->currentIndex() == 2 ) // jesli statystyki
    {
        qDebug() <<" zmiana strony ";
        qDebug() << strony->currentIndex();
        strony->setCurrentIndex(0);  // idz to menu glowne
    }
}


void Login_Window::show_warrning(int a)
{
    if (a == 0)
    {
        warrning ->setText("Nie znaleziono użytkownika");
    }
    else if (a == 1)
    {
       warrning ->setText("Podano złe hasło");
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
    QTimer::singleShot(1500, [=]() {
        anim->setStartValue(1.0);
        anim->setEndValue(0.0);
        anim->start(QPropertyAnimation::DeleteWhenStopped);
    });
}




void Login_Window::register_page()
{
    qDebug() << "sas";
//Login_Window_Reg *reg = new Login_Window_Reg(page2);
//connect (reg,&Login_Window_Reg::go_back,this,&Login_Window::Change_Page);
//page2->setLayout(reg->layout());
strony ->setCurrentIndex(1);

}

std::string Login_Window::get_user()
{
if (log == "gu")
{
 return log;
}
 log= login->text().toStdString();
 return log;

}
