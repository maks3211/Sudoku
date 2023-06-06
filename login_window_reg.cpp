#include "login_window_reg.h"

Login_Window_Reg::Login_Window_Reg(QWidget *parent)
    : QWidget{parent}
{
//layout1 = new QVBoxLayout(parent);
qDebug() << "Klasa rejestracji";

warnings = new Warnings(parent);


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
layout1->addWidget(warnings->get_short_message());
layout1->addWidget(reg);
layout1->addWidget(back);
layout1->addItem(spacer);
layout1->setAlignment(Qt::AlignCenter);
this->setLayout(layout1);

connect(back, &QPushButton::clicked, this, &Login_Window_Reg::go_back_clicked);
connect(reg, &QPushButton::clicked, this, &Login_Window_Reg::add_account);

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
    warnings->Added_new_user();
    warnings->Show("short");
}
else if (a == 1)
{
   bad_input(a);
   warnings->Bad_password();
   warnings->Show("short");
}
else if (a == 2)
{
   warnings->Repeated_login();
   warnings->Show("short");
}
else if (a == 3)
{
   bad_input(a);
   warnings->Bad_login();
   warnings->Show("short");
}
else if (a == 4)
{
    warnings->Diff_passwords();
    warnings->Show("short");
}


}


void Login_Window_Reg::bad_input(int a)
{
    if (a == 1)
    {
        warnings->Pass_req();
        warnings->Show("long");
    }
    else if (a == 3)
    {
        warnings->Login_req();
        warnings->Show("long");
    }
}




void Login_Window_Reg::Clear(int a)
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
       password_p->setText("");
    }
}
