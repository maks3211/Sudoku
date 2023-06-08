#ifndef GRA_H
#define GRA_H

#include<string>
#include<vector>
#include <utility>
#include<QPushButton>
#include<QLabel>
#include <QWidget>
#include<QList>
#include<QLineEdit>
#include<QCheckBox>
#include<QPainter>
#include<QTime>
#include<QIntValidator>
#include<QPropertyAnimation>
#include<QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>
//#include"test2.h"
#include"sudoku.h"
#include"notatki.h"
#include"mistakes.h"
#include"hint.h"
#include"savegame.h"
#include"Result_struct.h"
#include"my_checkbox.h"

class Gra : public QWidget
{
    Q_OBJECT




public:


void Pause();
void Start_game(int level);
void Reset();
void show();
void Load(QTime &time, int &lvl);
void show_resume();
void setEnabled(bool enabled);

std::string user;
bool want_save;
Gra(QWidget *parent = nullptr, std::string user = "-1");
    //~Gra();
std::vector<std::vector<int>>removed_board;
std::vector<std::vector<int>>full_board;
int Get_mistakes();
int Get_hints_used();
    public slots :
void Save(QTime time, int &lvl);


private:
SaveGame savegame;
QLineEdit *m_textFields[9][9];
QPushButton *m_button[9][9];
QLabel *m_labels[9][9];
Notatki *notatki[9][9];
my_checkbox *notatki_on_off;
Mistakes *mistakes;
Hint *hints;
QLabel *notatki_label;
bool is_pasue;
int h=0;
int m=0;
int last_col=0;
int last_row=0;
int filled=0;
void Check(int row, int col,std::vector<std::vector<int>>board,bool file);
void Highlight(int row,int col,std::vector<std::vector<int>>removed_board);
void Offlight(int row,int col,std::vector<std::vector<int>>removed_board);
void Create_Sudoku(int difficulty);
void Fill_Board();
void Change_filled(bool add);
void Clear_Board(); //Usunięcie wartości wpisanych przez uzytkownika- w przypadku powtorzenia
void Set_Buttons(); // Ustawienie wartosci przycsikow z zapisu

private slots:
void loss_game(int option);
void add_hint();
void Win();

signals:
void new_signal(); // emitowany w przypadku nowej gry- po przegranej
void reset_time();
void full_filled();
void was_saved();




};
#endif // GRA_H
