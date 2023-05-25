#include"test2.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <thread>
#include<random>
using namespace std;




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
bool isValid(int row, int col, int wartosc,vector<vector <Komorka>> & board  )  //board Vector 2d -- ZAMIENIC NA TABLICE !!
{
    for (int c = 0; c < 9; c++) // sprawdzanie wierszy
    {
        if (board[row][c].wartosc == wartosc)
            return false;
    }

    for (int r = 0; r < 9; r++) // sprawdzanie kolumn
    {
        if (board[r][col].wartosc == wartosc)
            return false;
    }


    int r0 = (row/3) * 3;  //wyszukanie skrajnych pol danego kwadratu
    int c0 = (col/3) * 3;

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++) // sprawdzanie 3x3
        {
            if (board[r0 + r][c0 + c].wartosc == wartosc)
            {
                return false;
            }
        }
    }
    return true;
}


//zwracanie wekotra mozliwych wartosci do danego pola
vector <int> getPossibleVal(int row, int col, vector<vector <Komorka>>& board)
{
    vector <int>PossibleVal;
    for (int i = 1; i <= 9; i++)
    {
        if (isValid(row, col, i, board))
        {
            PossibleVal.push_back(i);
        }
    }
    return PossibleVal;
}


bool FillBoard(int row, int col, vector<vector <Komorka>>& board)
{
    if (col == 9)
    {
        col = 0;
        row++;
    }

    if (row == 9)
    {
        return true;
    }

    if (board[row][col].jest)  //jezeli jest wypelnione do nastepnej
    {
        return FillBoard(row, col+1, board);
    }

    vector<int> possibleValues = getPossibleVal(row, col, board);
    if (possibleValues.size() == 0)
    {
        return false;
    }
   // random_shuffle(possibleValues.begin(), possibleValues.end()); //to nie działa, było chyba do c14
    random_device rd;
    mt19937 g(rd());
    shuffle(possibleValues.begin(),possibleValues.end(),g);
    for (int wartosc : possibleValues)
    {
        board[row][col].wartosc = wartosc;
        if (FillBoard(row, col + 1, board))
        {
            return true;
        }
    }
    board[row][col].wartosc = 0;

    return false;
}

void Remove(vector<vector<Komorka>>& board, int difficulty)
{

    int doUsuniecia = 0;
    int usnieto = 0;
    switch (difficulty)
    {
    case 1:
        doUsuniecia = 35;
        break;
    case 2:
        doUsuniecia = 45;
        break;
    case 3:
        doUsuniecia = 55;
        break;
    case 4:
        doUsuniecia = 65;
        break;
    }

    while (usnieto <  doUsuniecia)
    {
        int row = rand() % 9;
        int col = rand() % 9;
        if (!board[row][col].jest)
        {
            board[row][col].wartosc = 0;
            usnieto++;
        }
    }
}

void Pokaz(vector<vector<Komorka>>& board)
{
    cout << " 1 2 3 4 5 6 7 8 9" << endl;
    cout << "+-------+-------+-------+" << endl;
    for (int r = 0; r < 9; r++) {
        cout << r + 1 << "| ";
        for (int c = 0; c < 9; c++) {

            cout << board[r][c].wartosc << " ";
            if (c % 3 == 2) {
                cout << "| ";
            }
        }
        cout << endl;
        if (r % 3 == 2) {
            cout << "+-------+-------+-------+" << endl;
        }
    }

}


int Solve(vector<vector<Komorka>>& board)
{
    // Szukaj pierwszej pustej komórki na planszy
    int row = -1;
    int col = -1;
    bool isFinished = true;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].wartosc == 0) {
                row = i;
                col = j;
                isFinished = false;
                break;
            }
        }
        if (!isFinished) {
            break;
        }
    }

    // Jeśli plansza jest w pełni wypełniona, to jest już rozwiązana
    if (isFinished) {
        return 1;
    }

    // Sprawdź, jakie wartości mogą być wpisane do pustej komórki
    vector<int> possibleVals = getPossibleVal(row, col, board);

    // Przetestuj każdą możliwą wartość dla danej komórki
    int count = 0;
    for (int i = 0; i < possibleVals.size(); ++i) {
        board[row][col].wartosc = possibleVals[i];

        // Rekurencyjnie rozwiąż planszę z nową wartością
        count += Solve(board);

        // Jeśli znaleziono więcej niż jedno rozwiązanie, to można przerwać dalsze poszukiwania
        if (count > 1) {
            return count;
        }

        // Przywróć poprzednią wartość
        board[row][col].wartosc = 0;
    }

    return count;
}


void Usuwanie(vector<vector<Komorka>>& board, int difficulty)
{
    int oczekiwana = 0;
    int usnieto = 0;
    int wypelniona = 81;
    int row;   //pkt 2.
    int col;
    int val;
    int doUsuniecia=0;




    switch (difficulty)
    {
    case 1:
        doUsuniecia = 35;
        break;
    case 2:
        doUsuniecia = 45;
        break;
    case 3:
        doUsuniecia = 52;
        break;
    }




    while (usnieto < doUsuniecia) //pkt 1
       {

        int row = rand() % 9;
        int col = rand() % 9;


        if (board[row][col].wartosc != 0)  //nie trzeba juz sprawdzac bo brane sa kolejne wartosci z tej tablicy
        {
            val = board[row][col].wartosc; // kopiuje
            board[row][col].wartosc = 0;  //zeruje

            vector<vector<Komorka>> tmpBoard = board;
            int sol = Solve(tmpBoard);

            if (sol == 1)  //  jest jedno rozwiazanie to ok.  pkt 4a  sprawdzanie ile jest mozliwosci w danym polu
            {
              //  board[row][col].wartosc = 0;
                usnieto++;
                oczekiwana++;
                cout << "OCZEKIWANA == " << oczekiwana;
                  }
            else
            {
                board[row][col].wartosc = val;
               // cout << "\nBRAK";
            }
        }
    }




}
