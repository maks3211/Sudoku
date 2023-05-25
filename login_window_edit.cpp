#include "login_window_edit.h"
#include "qlineedit.h"

Login_Window_Edit::Login_Window_Edit(QWidget *parent)
    : QWidget{parent}
{
    text = new QLabel (parent);
    text->setText("<center><font color='#0e0b78', size = 9><b>Sudoku</b></font><br><font color= '#092D8C', size = 4>Edytuj konto</font><center>");

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
//USTAWIANIE TEKSTU DO METODY !!!!! !!ustawianie tekstu w metodzie!!
    new_thing = new QLineEdit(parent);
    new_thing->setPlaceholderText("Nowy login");
    //new_thing->setEchoMode(QLineEdit::Password);
    new_thing->setFixedSize(165,35);
    new_thing->setStyleSheet("QLineEdit {"
                    "border-radius: 15px;"
                    "background-color:white; "
                    "color:black;font-size:18px; }"
                    );

    new_thing_p = new QLineEdit(parent);
    new_thing_p->setPlaceholderText("Powtórz login");
    //new_thing_p->setEchoMode(QLineEdit::Password);
    new_thing_p->setFixedSize(165,35);
    new_thing_p->setStyleSheet("QLineEdit {"
                            "border-radius: 15px;"
                            "background-color:white; "
                            "color:black;font-size:18px; }"
                            );

//USTAWIANE TEKSTU W METODZIE
    edit= new QPushButton(parent);
    edit ->setText("Zmień");
    edit->setFixedSize(165,35);

    choice_box = new QCheckBox(parent);
    choice_box->setText("Haslo/login");
    choice_box ->setFixedSize(165,35);

    back= new QPushButton(parent);
    back ->setText("Wstecz");
    back->setFixedSize(165,35);



    warrning = new QLabel(parent);
    warrning ->setFixedSize(180,38); //180,40
    warrning->setText("");
    warrning->setWordWrap(true);
    warrning->setAlignment(Qt::AlignCenter);
    warrning->setStyleSheet("QLabel{font-size:14px;}"  );


    QVBoxLayout *layout1 = new QVBoxLayout(parent);
    QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout1->addWidget(text);
    layout1->addWidget(login);
    layout1->addWidget(password);
    layout1->addWidget(warrning);
    layout1->addWidget(new_thing);
    layout1->addWidget(new_thing_p);
    layout1->addWidget(edit);
    layout1->addWidget(choice_box);
    layout1->addWidget(back);
    layout1->addItem(spacer);
    layout1->setAlignment(Qt::AlignCenter);
    this->setLayout(layout1);

    connect(back, &QPushButton::clicked, this, &Login_Window_Edit::go_back_clicked);

    connect(choice_box,&QCheckBox::stateChanged,this,&Login_Window_Edit::What_edit);

}


void Login_Window_Edit::go_back_clicked()
{
    emit go_back();
}


void Login_Window_Edit::What_edit()
{
    if (choice_box->isChecked())
    {
        qDebug() << "Zmiana hasła";
        new_thing->setPlaceholderText("Nowe hasło");
        new_thing_p->setPlaceholderText("Powtórz hasło");

        new_thing->setEchoMode(QLineEdit::Password);
        new_thing_p->setEchoMode(QLineEdit::Password);
    }
    else
    {
        new_thing->setPlaceholderText("Nowy login");
        new_thing_p->setPlaceholderText("Powtórz login");
        qDebug()<< "Zmiana loginu";
        new_thing->setEchoMode(QLineEdit::Normal);
        new_thing_p->setEchoMode(QLineEdit::Normal);
    }
}



