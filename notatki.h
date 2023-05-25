#ifndef NOTATKI_H
#define NOTATKI_H

#include <QWidget>
#include<QPushButton>
#include<QList>
#include<QLabel>
#include<QLineEdit>
#include <iostream>





class Notatki : public QWidget
{
    Q_OBJECT
public:
    explicit Notatki(QWidget *parent = nullptr);
void set_notes(int val);
void clear_notes();

private:
    QList <QLabel*>cyfry;
    void set_pos(QList <QLabel*>&c);



};



#endif // NOTATKI_H
