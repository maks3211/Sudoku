#ifndef MISTAKES_H
#define MISTAKES_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QMessageBox>
#include<memory>
class Mistakes : public QWidget
{
    Q_OBJECT
public:
    explicit Mistakes(QWidget *parent = nullptr);
    void Add_hint();
    void Add_mistake();
    int return_mis();
private:

   std::shared_ptr<QLabel>mistakes;
   //std::shared_ptr<QLabel>hint_label;
   //std::shared_ptr<QPushButton>hint_button;
   //std::shared_ptr<QLabel>info;
   //std::shared_ptr<QPushButton>reset;
   //std::shared_ptr<QPushButton>newgame;
   int mis=0;
   int hints=0;
public slots:
   void Loss();
signals:
void too_many();
void new_game(int id);
void restart();
};

#endif // MISTAKES_H
