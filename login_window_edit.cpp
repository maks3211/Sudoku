#include "login_window_edit.h"
#include "qlineedit.h"

Login_Window_Edit::Login_Window_Edit(QWidget *parent)
    : QWidget{parent}
{
    warnings = new Warnings(parent);


    text =std::make_shared<QLabel>(parent);
    text->setText("<center><font color='#0e0b78', size = 9><b>Sudoku</b></font><br><font color= '#092D8C', size = 4>Edytuj konto</font><center>");

    login = std::make_shared<QLineEdit>(parent);
    login->setPlaceholderText("Login");
    login->setFixedSize(165,35);
    login->setStyleSheet("QLineEdit {"
                            "border-radius: 15px;"
                            "background-color:white; "
                            "color:black;font-size:18px; }"
                            );

    password = std::make_shared<QLineEdit>(parent);
    password->setPlaceholderText("Hasło");
    password->setEchoMode(QLineEdit::Password);
    password->setFixedSize(165,35);
    password->setStyleSheet("QLineEdit {"
                            "border-radius: 15px;"
                            "background-color:white; "
                            "color:black;font-size:18px; }"
                            );

    new_thing = std::make_shared<QLineEdit>(parent);
    new_thing->setPlaceholderText("Nowy login");
    new_thing->setFixedSize(165,35);
    new_thing->setStyleSheet("QLineEdit {"
                    "border-radius: 15px;"
                    "background-color:white; "
                    "color:black;font-size:18px; }"
                    );

    new_thing_p = std::make_shared<QLineEdit>(parent);
    new_thing_p->setPlaceholderText("Powtórz login");
    new_thing_p->setFixedSize(165,35);
    new_thing_p->setStyleSheet("QLineEdit {"
                            "border-radius: 15px;"
                            "background-color:white; "
                            "color:black;font-size:18px; }"
                            );


    edit=  std::make_shared<my_button>("Zmień",parent);
    edit->setFixedSize(165,35);


    remove=  std::make_shared<my_button>("Usuń konto",parent);
    remove ->setText("Usuń konto");
    remove->setGeometry(10,10,140,35);
    remove->setColor(217,83,79,205,48,44);

    choice_box =std::make_shared<my_checkbox>(parent);
    choice_box->setLeftText("Login");
    choice_box->setRightText("Hasło");
    choice_box ->setFixedSize(165,35);

    back=  std::make_shared<my_button>("Wstecz",parent);
    back ->setText("Wstecz");
    back->setFixedSize(165,35);






    QVBoxLayout *layout1 = new QVBoxLayout(parent);
    QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout1->addWidget(text.get());
    layout1->addWidget(login.get());
    layout1->addWidget(password.get());
    layout1->addWidget(warnings->get_short_message());
    layout1->addWidget(new_thing.get());
    layout1->addWidget(new_thing_p.get());
    layout1->addWidget(edit.get());
    layout1->addWidget(choice_box.get());
    layout1->addWidget(back.get());
    layout1->addItem(spacer);
    layout1->setAlignment(Qt::AlignCenter);
    this->setLayout(layout1);

    connect(back.get(), &QPushButton::clicked, this, &Login_Window_Edit::go_back_clicked);

    connect(choice_box.get(),&QCheckBox::stateChanged,this,&Login_Window_Edit::What_edit);

    connect(remove.get(),&QPushButton::clicked,this,&Login_Window_Edit::Delete_user);

    connect(edit.get(), &QPushButton::clicked,[this](){
        if (!choice_box->isChecked())
        {
        Edit_login();
        }
        else
        {
        Edit_password();
        }
    });
}


void Login_Window_Edit::go_back_clicked()
{
    emit go_back();
    Clear(0);
    Clear(1);
    Clear(2);
}


void Login_Window_Edit::What_edit()
{
    if (choice_box->isChecked())
    {
        new_thing->setPlaceholderText("Nowe hasło");
        new_thing_p->setPlaceholderText("Powtórz hasło");
        new_thing->setEchoMode(QLineEdit::Password);
        new_thing_p->setEchoMode(QLineEdit::Password);
    }
    else
    {
        new_thing->setPlaceholderText("Nowy login");
        new_thing_p->setPlaceholderText("Powtórz login");
        new_thing->setEchoMode(QLineEdit::Normal);
        new_thing_p->setEchoMode(QLineEdit::Normal);
    }
}



void Login_Window_Edit::Delete_user()
{

    if(u.findUser(login->text().toStdString()))
    {
        if(u.checkPassword(password->text().toStdString()))
        {
        u.removeUser(login->text().toStdString(),password->text().toStdString());
        warnings->User_deleted();
        warnings->Show("short");
        Clear(0);
        Clear(1);
        }
        else
        {
         warnings->Bad_user_password();
         warnings->Show("short");
        }
    }
    else
    {
         warnings->No_user();
         warnings->Show("short");
    }
}


void Login_Window_Edit::Edit_login()
{
int a =-1;
a = u.editLogin(login->text().toStdString(),password->text().toStdString(),new_thing->text().toStdString(),new_thing_p->text().toStdString());

if (a == 0)
{
    warnings->Change_made("login");
    warnings->Show("short");
    Clear(0);
    Clear(1);
    Clear(2);
}
else if (a == 1)
{
    qDebug ()<< "złe hasło-regex";
    warnings->Pass_req();
    warnings->Show("long");
}
else if (a == 2)
{
    qDebug ()<< "zajęty login";
    warnings->Repeated_login();
    warnings->Show("short");   
}
else if (a == 3)
{
    warnings->Login_req();
    warnings->Show("long");
    warnings->Bad_login();
    warnings->Show("short");
    qDebug ()<< "zły login- nie spełnia regex-a";
}
else if (a == 4)
{
    qDebug ()<< "złe hasło";
    warnings->Bad_user_password();
    warnings->Show("short");

}
else if (a == 5)
{
    warnings->No_user();
    warnings->Show("short");
    qDebug ()<< "nie ma takiego użtkownika";

}
else if (a == 6)
{
    qDebug ()<< "loginy się różnią";
    warnings->Diff_logins();
    warnings->Show("short");
}

}


void Login_Window_Edit::Edit_password()
{
int a =-1;
a = u.editPassword(login->text().toStdString(),password->text().toStdString(),new_thing->text().toStdString(),new_thing_p->text().toStdString());

if (a == 0)
{
    warnings->Change_made("password");
    warnings->Show("short");
    Clear(0);
    Clear(1);
    Clear(2);
}
else if (a == 1)
{
    warnings->Pass_req();
    warnings->Show("long");
}
else if (a == 2)
{
    qDebug ()<< "zajęty login";
}
else if (a == 3)
{
    qDebug ()<< "zły login- nie spełnia regex-a";
}
else if (a == 4)
{
    warnings->Bad_password();
    warnings->Show("short");
}
else if (a == 5)
{
    warnings->No_user();
    warnings->Show("short");
}
else if (a == 6)
{
    warnings->Diff_passwords();
    warnings->Show("short");
}

}


void Login_Window_Edit::Clear(int a)
{

   if (a==0)
    {
        login->setText("");

    }
  else if (a==1)
    {

         password->setText("");
    }
    else if (a==2)
    {
        new_thing->setText("");
        new_thing_p->setText("");
    }
}


