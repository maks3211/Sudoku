#ifndef STATISTICS_H
#define STATISTICS_H


#include <string>
#include<QTime>
#include<QComboBox>
#include<filesystem>
#include <shlobj.h>
#include<iostream>
#include<fstream>
#include<vector>
#include"Result_struct.h"





class Statistics
{
public:
int Count(int _lvl, int _m, int _h, QTime _time);
void Save(int result,std::string user,int user_num,std::vector<std::vector<Result>>&wyniki_vec);
void Load(std::vector<std::vector<Result>>&wyniki_vec); //Wczytuje statystyki wszystkich użytkowników
void Get_users(QComboBox *box);
int Get_best (int player,std::vector<std::vector<Result>>&wyniki_vec);
    Statistics();
    void Change_username(std::string new_name, std::string old_name);
    void Add_new_user(std::string name);
private:
    int lvl;
    int m;
    int h;
    int result;
    QTime time;
    std::filesystem::path docPath;

};

#endif // STATISTICS_H


//Kto -- Wynik -- Czas -- poziom -- błedy -- podpowiedzi
// Liczba pkt wejściowych 10 000
//-liczba sekund
//+poziom* 2000->
//-bledy * 1000
//-podpowiedzi* 500
