#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <thread>
#include<random>

//using namespace std;

struct Losowanie
{
    int a;
    int b;
};



//struct Komorka
//{
//    int wartosc;
   // bool jest;  //informuje czy dana komorka jest wypenlniona
//};



class Sudoku
{
public:
    Sudoku();
    Sudoku (std::vector<std::vector<int>>& removed_board,std::vector<std::vector<int>>& full_board, int difficulty);
    bool isValid(int row, int col, int wartosc,std::vector<std::vector <int>> & board);
   std::vector <int> getPossibleVal(int row, int col, std::vector<std::vector <int>>& board);
    bool FillBoard(int row, int col, std::vector<std::vector <int>>& board);
    //void Remove(vector<vector<int>>& board, int difficulty);
    void Pokaz(std::vector<std::vector<int>>& board);
    int Solve(std::vector<std::vector<int>>& board);
    void Usuwanie(std::vector<std::vector<int>>& board, int difficulty);

};

#endif // SUDOKU_H
