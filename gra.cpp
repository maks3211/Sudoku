#include "gra.h"

#include <QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QLineEdit>
#include<QIntValidator>
#include<QWidget>
#include<QPropertyAnimation>
#include<QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>
#include<vector>
#include<string>

// LABEL SA NIEPOTRZEBNE WYWALIĆ§



//Klasa na cutmowoy validator
class CustomValidator : public QValidator {
public:
    QValidator::State validate(QString &input, int &pos) const override {
        if (input.isEmpty() || input == "0" || input.toInt() > 9 || input.toInt() < 1)
            return QValidator::Invalid;
        return QValidator::Acceptable;
    }
};



Gra::Gra(QWidget *parent, std::string user)
    : QWidget(parent), user(user)
{

want_save=false;

if (user != "gu")
{
    want_save=true;
}

mistakes = new Mistakes(this);
hints=new Hint(this);




connect(hints, &Hint::add_hint,this,&Gra::add_hint);

connect(this,&Gra::full_filled,this,&Gra::Win);
//hints->lower();
//connect(hints,&Hint::too_many,this,&Gra::Pause);
notatki_on_off = new QCheckBox(this);
notatki_on_off-> setText("Notatki");
notatki_on_off->move(680,125);
is_pasue=true;
full_board=std::vector<std::vector<int>>(9,std::vector<int>(9, {0})); //full_board=vector<vector<Komorka>>(9,vector<Komorka>(9, {0, false}));
removed_board =std::vector<std::vector<int>>(9,std::vector<int>(9, {0})); //removed_board =vector<vector<Komorka>>(9,vector<Komorka>(9, {0, false}));
notatki_on_off->raise();

savegame = SaveGame();
connect(mistakes, &Mistakes::new_game,this,&Gra::loss_game);


this->hide();

}
//Gra::~Gra()
//{

//}


void Gra::Check(int row, int col,std::vector<std::vector<int>>full_board,bool file)

{

  if (m_button[row][col]->text() == QString::number(full_board[row][col]))
  {
     // filled -=1;
      Change_filled(true);
      hints->delete_cord(row,col);
      m_button[row][col]->setStyleSheet("QPushButton{background: transparent;color : #3f73dd}");
  }
  else
  {
        m_button[row][col]->setStyleSheet("QPushButton{background: transparent;color : red}");
        if (!file){
        mistakes->Add_mistake();
}
  }
}

//KOPIA MEOTDY CHECK
/*void Gra::Check(int row, int col,std::vector<std::vector<int>>full_board)

{
  if (m_button[row][col]->text() != QString::number(full_board[row][col]))
  {
        m_button[row][col]->setStyleSheet("QPushButton{background: transparent;color : red}");
        mistakes->Add_mistake();

  }
  else
  {
     // filled -=1;
      Change_filled(true);
      hints->delete_cord(row,col);
      m_button[row][col]->setStyleSheet("QPushButton{background: transparent;color : #3f73dd}");
  }
}
*/




void Gra::Start_game(int level) //Pokazuje gra- animacja jest do cyferek
{
    Create_Sudoku(level);
    Fill_Board();
    this->show();
    qDebug() << "\n==========================TOOOOOOOOOOOOOO" ;

    qDebug() << "\n==========================TOOOOOOOOOOOOOO" ;
}

void Gra::Highlight(int row,int col,std::vector<std::vector<int>>removed_board) //removed_board[row][col].wartosc != 0
{

    for (int c = 0; c < 9; c++) // sprawdzanie wierszy
    {
        if (removed_board[row][c] == 0) // jeżeli rowna 0- przycisk
            {

     //  !!!!! m_button[row][c]->setStyleSheet("background-color: #e5ebf2");// //("color: currentColor; background-color: #e5ebf2")
m_textFields[row][c]->setStyleSheet("background-color: #e5ebf2;border: 0px solid red");
            }
        else
           {
          m_labels[row][c]->setStyleSheet("background-color: #e5ebf2;" );
          }
    }
   for (int r = 0; r < 9; r++) // sprawdzanie kolumn
    {
       // m_textFields[r][col];
       // m_button[r][col];
      //m_labels[r][col];
        if (removed_board[r][col] == 0) // jeżeli jest rózna od zera- przycisk
            {         
        // !!!! m_button[r][col]->setStyleSheet("background-color: #e5ebf2");
            m_textFields[r][col]->setStyleSheet("background-color: #e5ebf2;border: 0px solid red");
            }
        else
            {
            m_labels[r][col]->setStyleSheet("background-color: #e5ebf2" );
            }
    }
 // !!!!!m_button[row][col]->setStyleSheet("background-color: #c6ddf9 ");//"background-color: #c6ddf9 "+
 m_textFields[row][col]->setStyleSheet("background-color: #c6ddf9;border: 0px solid red" ); //"background-color: #c6ddf9 "+
 //notatki[row][col];
}
void Gra::Offlight(int row,int col,std::vector<std::vector<int>>removed_board)
{
    for (int c = 0; c < 9; c++) // sprawdzanie wierszy
    {
        if (removed_board[row][c] == 0) // jeżeli rowna 0- przycisk
            {
        // !!!! m_button[row][c]->setStyleSheet("QPushButton{background: white; color: currentColor;}" );
          m_textFields[row][c]->setStyleSheet("background-color: transparent;border: 0px solid red");
            }
        else
           {
          m_labels[row][c]->setStyleSheet("color: currentColor; background-color: white" );
          }
    }
   for (int r = 0; r < 9; r++) // sprawdzanie kolumn
    {
       // m_textFields[r][col];
       // m_button[r][col];
      //m_labels[r][col];
        if (removed_board[r][col] == 0) // jeżeli jest rózna od zera- przycisk
            {
       // !!!! m_button[r][col]->setStyleSheet("QPushButton{background: white; color: currentColor;}" );
         m_textFields[r][col]->setStyleSheet("background-color: transparent;border: 0px solid red");
            }
        else
            {
            m_labels[r][col]->setStyleSheet("color: currentColor; background-color: white" );
            }

    }
//Check(row,col,full_board);
}


void Gra::Pause()
{
if (is_pasue)
     {  QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
       blurEffect->setBlurRadius(36);   
       this->setGraphicsEffect(blurEffect);
this ->setEnabled(false);

       /*
       for(int i = 0; i < 9; i++) {
           for(int j = 0; j < 9; j++) {
              if (removed_board[i][j] == 0 )
                  m_button[i][j]->setEnabled(false);
           }
      }
      */
       is_pasue=false;


}
else
{
    this ->setEnabled(true);
        this->setGraphicsEffect(nullptr);
   /* for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
           if (removed_board[i][j] == 0 )
            m_button[i][j]->setEnabled(true);
        }
   }
   */
    is_pasue=true;
}

}



void Gra::Create_Sudoku(int difficulty)
{
    int dif=difficulty;
    qDebug() <<"przed stworzeniuem obiektu sudoku: ";


        Sudoku wartoscii(removed_board,full_board,dif);

    qDebug() <<"po stworzeniu obiektu sudoku: ";
   //delete wartosci;
   qDebug()<<"  create sudoku";

}


void Gra::Fill_Board()
{
    for(int row = 0; row < 9; row++) {
               for(int col = 0; col < 9; col++){
                   qDebug() << removed_board[row][col];
    }
    }


    int j = 0;
      for(int row = 0; row < 9; row++) {
          int i =0;
                 for(int col = 0; col < 9; col++)
                 {




                     // Jeżeli jest wpisana
                    if (removed_board[row][col] != 0 )
                     {
        QLabel *cyferka =new QLabel(this);
        cyferka->setText(QString::number(removed_board[row][col]));
        cyferka->setFixedSize(50, 50); //55
        cyferka->setFont(QFont("Arial", 40));
       cyferka->setAlignment(Qt::AlignCenter);
       cyferka->setStyleSheet("QLabel { border: none;}");
       // cyferka->setText("5");
        m_labels[row][col]=cyferka;
        m_labels[row][col]->move(56+i,56+j);

                     }


    else {


                     QLineEdit *textField = new QLineEdit(this);
                     textField->setFixedSize(51, 51); //55
                     textField->setAlignment(Qt::AlignCenter);

                     textField->setValidator(new CustomValidator());  //validator
                     m_textFields[row][col] = textField;
                     textField->setFont(QFont("Times", 1));



                   //  textField->setStyleSheet("QLineEdit:hover { border: none; }");  //NIE MA TAKIEGO LAGA JAK SIE JE ZAZNACZA
                     QPushButton *button = new QPushButton(this);

                     //m_textFields[row][col]->move(53+i,53+j); //50
                     //m_button[row][col]->move(53+i,53+j);
                    hints->add_cord(row,col);
                    Change_filled(false);
                     button->setFixedSize(50, 50);//55 //50
                     button->setText(" ");
                   // button->setStyleSheet("QPushButton{background: transparent}");
                    button->setFont(QFont("Times", 40));
                    button->setStyleSheet("QPushButton { border: none;background: transparent}");
                     m_button[row][col] = button;
     //button->setStyleSheet("QPushButton { border: 3px solid green}");


                    // m_textFields[row][col]->hide();
                    m_textFields[row][col]->setStyleSheet("background-color: transparent;border: 0px solid red");
                     m_textFields[row][col]->move(56+i,56+j); //50 //53
                     m_button[row][col]->move(56+i,56+j);

                     notatki[row][col] = new Notatki(this);

                     notatki[row][col]->move(i,j);  //580 350
                     notatki[row][col]->lower();

                  //   notatki[row][col]->set_notes(0);

                 //     notatki[row][col]->hide();
                     // notatki[row][col]->lower();
     /*                connect(notatki_button, &QPushButton::clicked, [=](){
                     //  notatki_button->raise();  !!!!
                          notatki[row][col]->show();
                            //  notatki[row][col]->raise();
               });
                */
    //  notatki[row][col]->hide();

                    connect(m_button[row][col], &QPushButton::clicked, [=]() {
                      Offlight(last_row,last_col,removed_board);
                            m_textFields[row][col]->show();
                            m_textFields[row][col]->setFocus();
                            m_textFields[row][col]->selectAll();

                         Highlight(row,col,removed_board);

                            last_row = row;
                            last_col =col;

                            });

     connect(m_textFields[row][col], &QLineEdit::textChanged, this, [=]() {
         // Pobranie tekstu z QLineEdit
         QString text = m_textFields[row][col]->text();
         // Konwersja tekstu na liczbę całkowitą
         int value = text.toInt();

         if (m_button[row][col]->text() == m_textFields[row][col]->text() and !notatki_on_off->isChecked())
        {
            if (m_button[row][col]->text() == QString::number(full_board[row][col]))
            { Change_filled(false);
             }

             m_button[row][col]->setText(" ");
             m_textFields[row][col]->show();
             m_textFields[row][col]->setFocus();
             m_textFields[row][col]->selectAll();
             hints->add_cord(row,col);

         }



         // Sprawdzenie czy wartość znajduje się w przedziale od 1 do 9
        else if (value >= 1 && value <= 9) {


             m_textFields[row][col]->show();
             m_textFields[row][col]->setFocus();
             m_textFields[row][col]->selectAll();

                    if (notatki_on_off->isChecked())
                 {
                    notatki[row][col]->set_notes(value);
                      m_textFields[row][col]->lower();
                    if( m_button[row][col]->text() != " ")
                    {
                        m_button[row][col]->setText(" ");

                    }
                 }
                    else
                    {
                    m_button[row][col]->setText(text);
                    Check(row,col,full_board,false);
                    notatki[row][col]->clear_notes();
                    }




         }
     });
                 }i+=56;}
      j +=56;
      }
  qDebug()<<"  fill board";
 // want_save =  true;
}


void Gra::loss_game(int option)
{
if (option ==1) // restart
{
    emit reset_time();
    hints->reset();    //resetowanie podpowiedzi
    Reset();

}
else if (option ==2 ) // nowa gra
{
    qDebug() << "nowa";
    this->setEnabled(false);
    emit new_signal();
}
}







// ??Czy nie użyć tego gdy rozpoczynana jest nowa gra zeby zwolnic pamiec- wtedy dac do destruktora albo Widget::start_gry else if=1
void Gra::Reset()
{
qDebug()<<"Resetowanie";
  for(int i=0; i<9;i++)
  {
     for(int j=0; j<9;j++)
      {
      if (removed_board[i][j] == 0 )
       {
          qDebug()<<i<<" " <<j;
      notatki[i][j]->clear_notes();
      m_button[i][j]->setText(" ");
      qDebug() <<"-"<<  m_button[i][j]->text() << "-";
      }

     }

  }
m = 0;
h=0;

}

void Gra::add_hint()
{
    std::pair <int,int> cords = hints->show_hint();
    m_button[cords.first][cords.second]->setText(QString::number(full_board[cords.first][cords.second]));
    m_button[cords.first][cords.second]->setStyleSheet("QPushButton{background: transparent;color : purple}");
    Change_filled(true);

}

void Gra::Change_filled(bool add)
{
 if (add)
 {
     filled -=1; //wpisano poprawną wartość

     if (filled == 0 )
     {
         emit full_filled();
         qDebug() << "pelna";
     }
 }
 else if (!add)
 {

     filled +=1;
 }
}

void Gra::Win()
{
    this->setEnabled(false);

    qDebug()<<"WYGRAŁES";
}

void Gra::show()
{
    this->QWidget::show();
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(550); // czas trwania animacji w ms
    animation->setStartValue(0); // wartość początkowa przezroczystości
    animation->setEndValue(1); // wartość końcowa przezroczystości
    animation->start();

}



void Gra::Save()
{

    if (want_save)
       {
        qDebug()<<"ZAPIS";
        savegame.make_save(full_board,removed_board ,m_button,hints->return_hint(),mistakes->return_mis(),user);
       }
}

void Gra::Load()
{
    qDebug() << "dostpeny";
    savegame.load_save(full_board,removed_board,m_button,h,m,user); // jezeli jest save to po wznow to zrob
    Fill_Board();
    Set_Buttons();
qDebug() << "odczytane bledy" << m;
for (int i =0; i < m ; i++)
{

    mistakes->Add_mistake();
}

}


void Gra::show_resume()
{
    if (savegame.is_file(user))
    {
        qDebug() << "Odczytano save";
        emit was_saved();

    }

}




void Gra::Set_Buttons()
{
   for (unsigned int i = 0; i<savegame.get_buttons().size() ; i++ )
    {
    /*    qDebug() <<"ROW" <<  std::get<0>(savegame.get_buttons()[i]);           //row
          qDebug() <<"COL" << std::get<1>(savegame.get_buttons()[i]);            //col
          qDebug() <<"NUM" <<  std::get<2>(savegame.get_buttons()[i]);           //num
    */

      m_button[ std::get<0>(savegame.get_buttons()[i])][ std::get<1>(savegame.get_buttons()[i])]->setText(QString::number(std::get<2>(savegame.get_buttons()[i])));
      Check(std::get<0>(savegame.get_buttons()[i]),std::get<1>(savegame.get_buttons()[i]),full_board,true);
    }
}
