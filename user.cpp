#include "user.h"

User::User()
{
find = false;
pos = 0;
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
    std::filesystem::create_directories(docPath);
}


bool User::findUser(std::string login)
{
    if(login == "")
    {
        return false;

    }

    std::string tmp;
    std::ifstream plik;
    std::filesystem::path copy = docPath;
    plik.open(copy/="users.txt");
    if (plik.is_open())
    {
        while (!plik.eof())
        {
            while (!plik.eof())
                   {
                       plik >> tmp;
                       pos++;
                       if (login == tmp)
                       {
                           pos++;
                           return true;
                           break; //<-//
                       }
                       else {
                           pos++;
                           plik >> tmp;
                           tmp = "";
                       }
                   }
        }
        return false;
    }
    return false;
    plik.close();
}



bool User::checkPassword(std::string password)
{
   // if (password =="")
   // {
   //     std::cout << "puste";
    //    return false;
   // }

    std::ifstream plik;
    std::filesystem::path copy = docPath;
    plik.open(copy/="users.txt");
    std::string tmp;

    if (plik.is_open()){
        for (int i = 0; i < pos; i++)
            {
            plik >> tmp;
            }
    }
    if (tmp == password)
    {
      return true;
    }
    else
    {
      return false;
    }
}


int User::addUser(std::string login,std::string password,std::string password_p) // 0-poprawne dane, 1-zle haslo, 2-nazwa zajeta, 3-zly login
{
  //regex 1 mala,  1 wielka, 1 cyfra, min 8 znakow, max 20 dla hasla
   std::regex hwzor("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?!.*\\s).{8,20}$");

   //login to min 4 znaki, brak spacji max 20
   std::regex lwzor("^(?!.*\\s).{4,20}$");


   if (regex_search(login, lwzor))
       {
        if (!findUser(login))
        {
                 if (regex_search(password, hwzor))
                {
                     if (password == password_p)
                {
                //dobre haslo
                save_to_file(login,password);
                return 0;  //dodanie dodanie konta
                }
                     else
                     {
                         return 4; // dobre haslo- zle powtorzenie
                     }
                }
                else
                {
                //zle haslo
                return 1;
                }
        }
       else
       {
       return 2; //uzytkownik istnieje
       }

   }
   else
   {
       return 3; //zly login
   }
}

void User::save_to_file(std::string login,std::string password)
{
    std::filesystem::path copy = docPath;
    std::ofstream plik(copy/="users.txt", std::ios_base::app);
    plik<<"\n" <<login << " " << password;
}

void User::editLogin(std::string login,std::string password,std::string new_login,std::string new_login_p)
{



}
