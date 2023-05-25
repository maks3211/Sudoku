#ifndef TEST2_H
#define TEST2_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <thread>
#include<random>


using namespace std;

struct Komorka
{
    int wartosc;
    bool jest;  //informuje czy dana komorka jest wypenlniona
};


/*class Sudoku {
public:
    Sudoku(vector<vector<Komorka>>& removed_board, vector<vector<Komorka>>& full_board, int difficulty)
    {
        FillBoard(0, 0, full_board);
        removed_board = full_board;
        Usuwanie(removed_board, difficulty);
        Pokaz(full_board);
    }

*/
// Czy 'wartosc' moze zostac wpisana do row, col
bool isValid(int row, int col, int wartosc,vector<vector <Komorka>> & board  );  //board Vector 2d -- ZAMIENIC NA TABLICE !!


//zwracanie wekotra mozliwych wartosci do danego pola
vector <int> getPossibleVal(int row, int col, vector<vector <Komorka>>& board);

bool FillBoard(int row, int col, vector<vector <Komorka>>& board);


void Remove(vector<vector<Komorka>>& board, int difficulty);


void Pokaz(vector<vector<Komorka>>& board);



int Solve(vector<vector<Komorka>>& board);


void Usuwanie(vector<vector<Komorka>>& board, int difficulty);


#endif // TEST2_H
