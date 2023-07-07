#ifndef HINT_H
#define HINT_H
#include<vector>
#include<random>
#include <utility>
#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include"my_button.h"
#include<memory>
class Hint : public QWidget
{
    Q_OBJECT
public:
    explicit Hint(QWidget *parent = nullptr);
void add_cord(int row, int col);
void delete_cord(int row, int col);
void reset();
void set_hint(int num);
int return_hint();
    std::pair<int,int> show_hint();
private:
    std::shared_ptr<my_button>button;
     int count;
     std::vector<std::pair<int,int>>pola;
private slots:
    void changetext();

signals:
    void add_hint();
    void enough();
};

#endif // HINT_H

