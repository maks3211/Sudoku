
#include "savegame.h"



SaveGame::SaveGame()
{


TCHAR szPath[MAX_PATH];
SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, szPath);
std::string strPath;
int len = WideCharToMultiByte(CP_UTF8, 0, szPath, -1, NULL, 0, NULL, NULL);

if (len > 0) {
     strPath.resize(len);
     WideCharToMultiByte(CP_UTF8, 0, szPath, -1, &strPath[0], len, NULL, NULL);
 }
std::replace(strPath.begin(), strPath.end(), '\\', '/');
strPath.pop_back();


docPath = std::filesystem::path(strPath);
docPath /= "aaSudokuSave";
docPath /= "Plansze";
std::filesystem::create_directories(docPath);



}

void SaveGame::make_save(std::vector<std::vector<int>>&full_board,std::vector<std::vector<int>>&removed_board ,QPushButton *m_button[9][9],int hint,int mis, std::string user,std::string time, int lvl) //vector<vector<int>>full_board,vector<vector<int>>removed_board ,QPushButton *m_button[9][9]
{
std::filesystem::path copy = docPath;
std::ofstream plik(copy /=user+".txt");
if (plik.is_open())
{

   for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++)  {
                if (removed_board[r][c] == 0)
                {
                    plik << "-"<< full_board[r][c];
                    if (m_button[r][c]->text().toStdString() !=" "){
                    plik <<";"<< m_button[r][c]->text().toStdString();
                   }
                }
                else
                {
                    plik << removed_board[r][c];
                }
           }
           plik << std::endl;
    }
plik <<"p" <<hint << mis<<lvl<<time;

plik.close();
}

}

std::string SaveGame::load_save(std::vector<std::vector<int>>&full_board,std::vector<std::vector<int>>&removed_board,QPushButton *m_button[9][9],int &hint,int &mis, std::string user, int &lvl)
{
    std::filesystem::path copy = docPath;
    std:: fstream plik(copy /=user+".txt");

    int num; //zmienna do przechowywanie kolejnych odczytanych danych
    char z;
    int row =0;
    int col =0;
    int last_row=0;
    int last_col=0;
    std::string time;
    if (plik.is_open() && !(plik.peek() == std::ifstream::traits_type::eof())){ //plik.is_open() and !(plik.peek() == std::ifstream::traits_type::eof())
    while (!plik.eof()){

        plik >> z;
        if (z != '-' and z != ';' and z!='p')
        {
         num = std::stoi(std::string(1, z));
         full_board[row][col]=num;
         removed_board[row][col]=num;
         set_index(row,col);

        }
        else if (z == '-')
        {
             plik >> z;
             num = std::stoi(std::string(1, z));
             full_board[row][col]=num;
             removed_board[row][col]=0;
             last_row=row;
             last_col=col;
             set_index(row,col);


        }
        else if (z == ';')
        {
         plik >> z;
         num =  std::stoi(std::string(1, z));
        for_buttons.emplace_back(last_row,last_col,num);
        }


        if (z == 'p')
        {
          plik >> z;
          num =  std::stoi(std::string(1, z));
          hint = num;
          plik >> z;
          num =  std::stoi(std::string(1, z));
          mis = num;
          plik >>z;
          num =  std::stoi(std::string(1, z));
          lvl = num;
          plik >>z;

for (int i = 0 ; i <8;i++ )
{
    time +=z;
    plik>>z;
}
        }
    }
return time;

}

    else
    {
        time = "00:00:00";
        return time;
    }

}
void SaveGame::set_index(int &row, int &col)
{
    col++;
    if (col ==9)
        {
        col =0;
        row ++;    
        }


}

 std::vector<std::tuple<int,int,int>> SaveGame::get_buttons()
 {
     return for_buttons;
 }

 bool SaveGame::is_file(std::string user) // czy istnieje plik od odczytu, czy nie jest pusty
 {
     std::filesystem::path copy = docPath;
     std:: fstream plik(copy /=user+".txt");
      if (plik.is_open() and !(plik.peek() == std::ifstream::traits_type::eof())){
          return true;
      }
      else {
          return false;
      }
 }


 void SaveGame::Change_username(std::string new_name, std::string old_name)
 {
     std::filesystem::path copy = docPath;
     std::filesystem::path oldFilePath = docPath / (old_name + ".txt");
     std::filesystem::path newFilePath = docPath / (new_name + ".txt");
     if (std::filesystem::exists(oldFilePath)) {
         std::filesystem::rename(oldFilePath, newFilePath);
     }

 }


 void SaveGame::remove_file(std::string user)
 {
        std::filesystem::path copy = docPath/= user+ ".txt";
        if (std::filesystem::exists(copy))
            {
            std::filesystem::remove(copy);
            }
 }
