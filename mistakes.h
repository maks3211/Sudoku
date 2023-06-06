#ifndef MISTAKES_H
#define MISTAKES_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QMessageBox>
class Mistakes : public QWidget
{
    Q_OBJECT
public:
    explicit Mistakes(QWidget *parent = nullptr);
    void Add_hint();
    void Add_mistake();
    int return_mis();
private:
    QMessageBox * box; //chyba nie uzywane
   QLabel *mistakes;
   QLabel *hint_label;
   QPushButton *hint_button;
   QLabel *info;
   QPushButton *reset;
   QPushButton *newgame;
   int mis=0;
   int hints=0;
public slots:
   void Loss();
signals:
void too_many();
void new_game(int id);
void restart();
//void add_mistake_signal();
};

#endif // MISTAKES_H
