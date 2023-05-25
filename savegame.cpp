
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

void SaveGame::make_save(std::vector<std::vector<int>>&full_board,std::vector<std::vector<int>>&removed_board ,QPushButton *m_button[9][9],int hint,int mis, std::string user) //vector<vector<int>>full_board,vector<vector<int>>removed_board ,QPushButton *m_button[9][9]
{
std::cout<<"zapisywanie";

std::filesystem::path copy = docPath;


//std::ofstream plik(docPath /="Test2.txt");


//std::ofstream plik(copy /="Test2.txt");
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
           //plik.seekp(-1, std::ios_base::cur);
           plik << std::endl;
    }
plik <<"p" <<hint << mis;

plik.close();
}

}

void SaveGame::load_save(std::vector<std::vector<int>>&full_board,std::vector<std::vector<int>>&removed_board,QPushButton *m_button[9][9],int &hint,int &mis, std::string user)
{
    std::filesystem::path copy = docPath;
    std:: fstream plik(copy /=user+".txt");
    //int a;
    //std::string napis; 
    int num;
    char z;
    int row =0;
    int col =0;
    int last_row=0;
    int last_col=0;
    if (plik.is_open()){
    while (!plik.eof()){

        plik >> z;
        if (z != '-' and z != ';' and z!='p')
        {
         num = std::stoi(std::string(1, z));
         full_board[row][col]=num;
         removed_board[row][col]=num;
         qDebug () << "kratka: (row, col)" << row<<col;
         set_index(row,col);

        }
        else if (z == '-')
        {
             plik >> z;
             num = std::stoi(std::string(1, z));
             full_board[row][col]=num;
             removed_board[row][col]=0;
             qDebug () << "kratka: (row, col)" << row<<col;
             //qDebug () << "Usuniete: " << num;


              last_row=row;
              last_col=col;
              set_index(row,col);


        }
        else if (z == ';')
        {
         plik >> z;
         // m_button[row][col]->setText(QString(QChar::fromLatin1(z)));
         num =  std::stoi(std::string(1, z));
        // qDebug () << "Guzik: " << num;
        for_buttons.emplace_back(last_row,last_col,num);
        qDebug() << "Powinno byc zero:  " <<removed_board[row][col];
        qDebug () << "kratka: guzik (row, col)" << row<<col;

        }


        if (z == 'p')
        {
           plik >> z;
           num =  std::stoi(std::string(1, z));
           qDebug () << "podpowiedzi : " << num;
           hint = num;
           plik >> z;
           num =  std::stoi(std::string(1, z));
           mis = num;
          qDebug () << "bledy : " << mis;
          plik >>z;
        }
    }
    qDebug ()<<"KONIEC WHILE";
   // return true;
}

    else
    {

        qDebug() << "Brak pliku";
        //return false;
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

 bool SaveGame::is_file(std::string user)
 {
     std::filesystem::path copy = docPath;
     std:: fstream plik(copy /=user+".txt");
      if (plik.is_open()){
          return true;
      }
      else {
          return false;
      }
 }
