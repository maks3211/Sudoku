#include "hint.h"

    Hint::Hint(QWidget *parent)
        : QWidget{parent}
    {
        count =0;
        button = std::make_shared<my_button>("",this);
        button ->setText("Podpowiedzi: 0/3");
        //button->setFixedSize(130,45);
        button->setStyleSheet("QPushButton {"
                                    "border-radius: 10px;"
                                    "background-color:rgb(52,94,229); "
                                    "color:white;font-size:14px; }"
                                    "QPushButton:hover:!pressed{background-color:rgb(28,72,225)}");
        button->setGeometry(670,220,110,45);
    connect(button.get(), &QPushButton::clicked, this, &Hint::changetext);
    }

    void Hint::changetext()
    {
        count +=1;        
        button->setText("Podpowiedzi: " + QString::number(count)+ "/3");
        emit add_hint();
        if (count ==3)
        {           
          button->setDisabled(true);
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
button ->setText("Podpowiedzi: 0/3");
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
 button ->setText("Podpowiedzi: "+ QString::number(num)+ "/3");
 if (count ==3)
 {
     button->setDisabled(true);
 }
}
