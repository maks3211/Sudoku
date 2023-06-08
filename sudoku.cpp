#include "sudoku.h"

Sudoku::Sudoku(std::vector<std::vector<int>>& removed_board,std::vector<std::vector<int>>& full_board, int difficulty)
{
    FillBoard(0, 0, full_board);
    removed_board = full_board;
    Usuwanie(removed_board, difficulty);
    Pokaz(full_board);
}



bool Sudoku::isValid(int row, int col, int wartosc,std::vector<std::vector <int>> & board )
{
    for (int c = 0; c < 9; c++) // sprawdzanie wierszy
    {
        if (board[row][c] == wartosc)
            return false;
    }

    for (int r = 0; r < 9; r++) // sprawdzanie kolumn
    {
        if (board[r][col] == wartosc)
            return false;
    }


    int r0 = (row/3) * 3;  //wyszukanie skrajnych pol danego kwadratu
    int c0 = (col/3) * 3;

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++) // sprawdzanie 3x3
        {
            if (board[r0 + r][c0 + c] == wartosc)
            {
                return false;
            }
        }
    }
    return true;

}


std::vector<int> Sudoku::getPossibleVal(int row, int col, std::vector<std::vector <int>>& board)
{
    std::vector <int>PossibleVal;
    for (int i = 1; i <= 9; i++)
    {
        if (isValid(row, col, i, board))
        {
            PossibleVal.push_back(i);
        }
    }
    return PossibleVal;

}


bool Sudoku::FillBoard(int row, int col, std::vector<std::vector <int>>& board)
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

   std::vector<int> possibleValues = getPossibleVal(row, col, board);
    if (possibleValues.size() == 0)
    {
        return false;
    } 
    std::random_device rd;
    std:: mt19937 g(rd());
    shuffle(possibleValues.begin(),possibleValues.end(),g);
    for (int wartosc : possibleValues)
    {
        board[row][col] = wartosc;
        if (FillBoard(row, col + 1, board))
        {
            return true;
        }
    }
    board[row][col] = 0;

    return false;

}


void Sudoku::Pokaz(std::vector<std::vector<int>>& board)
{
    std::cout << " 1 2 3 4 5 6 7 8 9" << std::endl;
   std:: cout << "+-------+-------+-------+" << std::endl;
    for (int r = 0; r < 9; r++) {
        std::cout << r + 1 << "| ";
        for (int c = 0; c < 9; c++) {

            std::cout << board[r][c] << " ";
            if (c % 3 == 2) {
                std::cout << "| ";
            }
        }
       std:: cout <<std:: endl;
        if (r % 3 == 2) {
            std::cout << "+-------+-------+-------+" << std::endl;
        }
    }
}
 int Sudoku::Solve (std::vector<std::vector<int>>& board)
 {
     // Szukaj pierwszej pustej komórki na planszy
     int row = -1;
     int col = -1;
     bool isFinished = true;
     for (int i = 0; i < 9; ++i) {
         for (int j = 0; j < 9; ++j) {
             if (board[i][j] == 0) {
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
    std::vector<int> possibleVals = getPossibleVal(row, col, board);

     // Przetestuj każdą możliwą wartość dla danej komórki
     int count = 0;
     for (int i = 0; i < possibleVals.size(); ++i) {
         board[row][col] = possibleVals[i];

         // Rekurencyjnie rozwiąż planszę z nową wartością
         count += Solve(board);

         // Jeśli znaleziono więcej niż jedno rozwiązanie, to można przerwać dalsze poszukiwania
         if (count > 1) {
             return count;
         }

         // Przywróć poprzednią wartość
         board[row][col] = 0;
     }

     return count;
 }

 void Sudoku::Usuwanie(std::vector<std::vector<int>>& board, int difficulty)
 {
     int usnieto = 0;
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
         doUsuniecia =53;
         break;
     }


     while (usnieto < doUsuniecia) //pkt 1
        {

         int row = rand() % 9;
         int col = rand() % 9;

             val = board[row][col]; // kopiuje
             board[row][col] = 0;  //zeruje

             std::vector<std::vector<int>> tmpBoard = board;
             int sol = Solve(tmpBoard);

             if (sol == 1)  //  jest jedno rozwiazanie to ok.  pkt 4a  sprawdzanie ile jest mozliwosci w danym polu
             {
                 usnieto++;
                   }
             else
             {
                 board[row][col] = val;
             }
     }
 }


