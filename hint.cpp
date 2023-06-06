#include "hint.h"

    Hint::Hint(QWidget *parent)
        : QWidget{parent}
    {
        count =0;
        button = new QPushButton(this);
        button ->setText("Podpowiedź: 0/3");
        this->move(700,250);

    connect(button, &QPushButton::clicked, this, &Hint::changetext);
    }

    void Hint::changetext()
    {
        count +=1;        
        button->setText("Podpowiedź " + QString::number(count)+ "/3");
        emit add_hint();
        if (count ==80) // ZMIENIC NA 3
        {           
            button->setDisabled(true);
            button->setStyleSheet("color:red");
        }

    }
std::pair<int,int> Hint::show_hint()
{

      int pos = rand() % pola.size();
      int r =pola[pos].first;
      int c= pola[pos].second;
      delete_cord(pola[pos].first,pola[pos].second);
      return std::make_pair(r,c);
}

void Hint::add_cord(int row,int col)
{
    pola.push_back(std::make_pair(row,col));
}

void Hint::delete_cord(int row, int col)
{
    pola.erase(std::remove_if(pola.begin(), pola.end(),
        [=](std::pair<int,int> p){ return p.first == row && p.second == col; }),
        pola.end());
    if (pola.size()==0)
    {
        this->setEnabled(false);
    }
}
void Hint::reset()
{
count = 0;
button ->setText("Podpowiedź: 0/3");
button->setStyleSheet("color:black");
button->setDisabled(false);
}

int Hint::return_hint()
{
    return count;

}

void Hint::set_hint(int num)
{
    count = num ;
    qDebug() << "USTAWIANIE Z GORY";
 button ->setText("Podpowiedź: "+ QString::number(num)+ "/3");
 if (count ==3) // ZMIENIC NA 3
 {
     button->setDisabled(true);
     button->setStyleSheet("color:red");
 }
//count = num;
}
