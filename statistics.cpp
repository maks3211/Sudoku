#include "statistics.h"

Statistics::Statistics()
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
    docPath /= "Statystyki";
    std::filesystem::create_directories(docPath);

}



int Statistics::Count(int _lvl, int _m, int _h, QTime _time) //Liczenie punktow, pobranie danych
{
//int seconds = QTime(0, 0, 0).secsTo(time);
    lvl = _lvl;
    m=_m;
    h=_h;
    time = _time;
    result = 10000- QTime(0, 0, 0).secsTo(time) + lvl*2000- m*1000-h*500;
return result;
}



void Statistics::Save(int result, std::string user,int user_num,std::vector<std::vector<Result>>&wyniki_vec)
{
    if (user !="gu")
  {
        qDebug() << "Zapisywanie statystyk dla " << QString::fromStdString(user) ;
    std::filesystem::path copy = docPath;
    std::ofstream plik(copy /=user+".txt", std::ios_base::app);

    qDebug() << "Ścieżka do stat : " << QString::fromStdString(copy.string());


    //Pobrac numer usera
Result wynik;
wynik.result = result;
wynik.lvl = lvl;
wynik.hints = h;
wynik.mistakes = m;
wynik.time = time;
wyniki_vec[user_num].push_back(wynik);


if (plik.is_open())
{
    int seconds = QTime(0, 0, 0).secsTo(time);
   // plik <<result <<" " << lvl <<" " << time.toString("HH:mm:ss").toStdString() << " " << m << " " << h;
    plik<<"\n"<<result <<" " << lvl <<" " << seconds << " " << m << " " << h;
}
plik.close();
}
    else
    {
        qDebug()<<"Granie jako gosc";
    }
}

void Statistics::Load(std::vector<std::vector<Result>>&wyniki_vec)
{

    for (auto const& el : std::filesystem::directory_iterator(docPath))
    {
         std::filesystem::path copy = docPath;
         std::fstream plik( copy/=el.path().filename().string());


if (plik.is_open() && !(plik.peek() == std::ifstream::traits_type::eof()))
{
qDebug()<<"Ładowanie ";
std::vector<Result> vec;
    while (!plik.eof())
    {
        Result wyniki;

      int t;
      plik >> result;
      plik >> lvl;
      plik >> t; // odczytany czas w sekundach
      int godziny = t/ 3600;
      int minuty = (t % 3600) / 60;
      int sekundy = (t % 3600) % 60;
      time.setHMS(godziny, minuty, sekundy);
      plik >> m;
      plik >> h;
      wyniki.result = result;
      wyniki.lvl = lvl;
      wyniki.hints = h;
      wyniki.mistakes = m;
      wyniki.time = time;
      qDebug() << "PRZED";
      vec.push_back(wyniki);
       qDebug() << "Po";
    }qDebug() << "przed pushemoopo";
     wyniki_vec.push_back(vec);
      qDebug() << "poopo";
}
else if (plik.is_open() && (plik.peek() == std::ifstream::traits_type::eof()))
{
    qDebug() << "PUSTY";
    std::vector<Result> emptyVec; // Pusty wektor - brak danych
    wyniki_vec.push_back(emptyVec);
}
plik.close();

    }
}


void Statistics::Get_users(QComboBox * box)
{
std::filesystem::path copy = docPath;
for (auto const& el : std::filesystem::directory_iterator(copy))
{
    qDebug()<<"Szukanie userow w statistisc";
    box->addItem(QString::fromStdString(el.path().filename().string()).chopped(4));
}

}

int Statistics::Get_best(int player, std::vector<std::vector<Result>>&wyniki_vec)
{
int best=0;
int tmp=0;
if (!wyniki_vec.empty()){
for (auto i = 0 ; i < wyniki_vec[player].size(); i++)
{
   if (wyniki_vec[player][i].result>tmp)
   {
       tmp = wyniki_vec[player][i].result;
       best=i;
   }

}
qDebug() << "Najlepszy wynik" << best;
}
return best;

}

void Statistics::Change_username(std::string new_name, std::string old_name)
{
    std::filesystem::path copy = docPath;
    std::cout << " PO ZMINAIE : " << copy;
    std::filesystem::path oldFilePath = docPath / (old_name + ".txt");
    std::filesystem::path newFilePath = docPath / (new_name + ".txt");
    if (std::filesystem::exists(oldFilePath)) {
        std::filesystem::rename(oldFilePath, newFilePath);
    }

}

void Statistics::Add_new_user(std::string name)
{
    std::filesystem::path copy = docPath;
    std::ofstream plik(copy /=name+".txt");
    if (plik.is_open())
    {
        plik.close();
    }
}
