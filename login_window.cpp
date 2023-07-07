#include "login_window.h"

Login_Window::Login_Window(QWidget *parent)
    : QWidget{parent}
{

    setWindowTitle("Zaloguj się");
    resize(700,500);  //prawo gora
    this->setMinimumSize(233,166);
    this->setMaximumSize(700,500);

layout1 = new QVBoxLayout(page1);


text = std::make_shared<QLabel> (page1);
text->setText("<center><font color='#0e0b78', size = 9><b>Sudoku</b></font><br><font color= '#092D8C', size = 4>Zaloguj się, aby kontynuować</font><center>");

warrning = std::make_shared<QLabel>(page1);
warrning ->setFixedSize(175,25);
warrning->setText("");
warrning->setAlignment(Qt::AlignCenter);
warrning->setStyleSheet("QLabel{font-size:14px;}"  );




    login = std::make_shared<QLineEdit> (this);
    login->setPlaceholderText("Login");
    login->setFixedSize(165,35);
    login->setStyleSheet("QLineEdit {"
                        "border-radius: 15px;"
                        "background-color:white; "
                        "color:black;font-size:18px; }"
                        );



    password = std::make_shared<QLineEdit>(page1);
    password->setPlaceholderText("Hasło");
    password->setEchoMode(QLineEdit::Password);
    password->setFixedSize(165,35);
    password->setStyleSheet("QLineEdit {"
                        "border-radius: 15px;"
                        "background-color:white; "
                        "color:black;font-size:18px; }"
                        );



login_button = std::make_shared<my_button>("Zaloguj się",page1);

login_button->setFixedSize(165,35);




guest_button = std::make_shared<my_button>("Graj jako Gość",page1);

guest_button->setFixedSize(165,35);

new_account=std::make_shared<my_button>("Zarejestruj się",page1);

new_account->setFixedSize(165,35);

edit = std::make_shared<my_button>("Edytuj konto",page1);


edit->setFixedSize(165,35);








quit_button = std::make_shared<my_button>("Wyjdź",page1);
quit_button->setFixedSize(165,35);


QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
layout1->addWidget(text.get());
layout1->addWidget(login.get());
layout1->addWidget(password.get());
layout1->addWidget(warrning.get());
layout1->addWidget(login_button.get());
layout1->addWidget(guest_button.get());
layout1->addWidget(new_account.get());
layout1->addWidget(edit.get());
layout1->addItem(spacer);
layout1->addWidget(quit_button.get());
layout1->setAlignment(Qt::AlignCenter);

page1->setLayout(layout1);

QVBoxLayout *mainLayout = new QVBoxLayout();
mainLayout->addWidget(strony);
setLayout(mainLayout);


strony->addWidget(page1);
strony->addWidget(page2);
strony->addWidget(page3);
strony->setCurrentWidget(0);







connect(new_account.get(), &QPushButton::clicked, [this]() {
           strony->setCurrentIndex(1);
});


connect(login_button.get(), &QPushButton::clicked, [this]() {
    Login_success(0);
});

connect(guest_button.get(), &QPushButton::clicked, [this]() {
    Login_success(1);

});



connect(quit_button.get(), SIGNAL(clicked()), this, SLOT(close()));

//Okno rejestracji
Login_Window_Reg *reg = new Login_Window_Reg(page2);
connect (reg,&Login_Window_Reg::go_back,this,&Login_Window::Change_Page);
page2->setLayout(reg->layout());
login->setFocus();

//logowanie za pomocą entera
connect(login.get(), &QLineEdit::returnPressed, login_button.get(), &QPushButton::click);
connect(password.get(), &QLineEdit::returnPressed, login_button.get(), &QPushButton::click);


Login_Window_Edit *edit_w = new Login_Window_Edit(page3);
page3->setLayout(edit_w->layout());
connect(edit.get(), SIGNAL(clicked()), this,  SLOT(Change_Page()));

connect(edit_w,&Login_Window_Edit::go_back,this,&Login_Window::Change_Page);

}


void Login_Window::Login_success(bool guest)
{
    if (guest)
    {
    log = "gu";
    emit logged(1);
    this->close();
    guest=false;
    clear_inputs();
    }
else
    {   
        User user;
        if(user.findUser(login->text().toStdString()))
     {
        if(user.checkPassword(password->text().toStdString()))
        {
             log= login->text().toStdString();
             qDebug ()<< "Zalogowanio sie jako: " << QString::fromStdString(log);
             emit logged(2);
             this->close();
             clear_inputs();
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

    if ( strony->currentIndex() == 0)
    {
        strony->setCurrentIndex(2);  //idz do edycji
    }
    else if ( strony->currentIndex() ==1 or strony->currentIndex() == 2 )
    {
        strony->setCurrentIndex(0);
        clear_inputs();
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

    QGraphicsOpacityEffect *e = new QGraphicsOpacityEffect(warrning.get());
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
strony ->setCurrentIndex(1);
}

std::string Login_Window::get_user()
{
if (log == "gu")
{
 return log;
}
 return log;
}


void Login_Window::clear_inputs()
{
    login->setText("");
    password->setText("");
}
