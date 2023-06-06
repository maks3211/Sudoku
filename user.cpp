#include "user.h"

User::User()
{
find = false;
//"pozycja" hasła
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

    pos =0;
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
                           std::cout << "Pozycja w find" << pos << "----" << std::endl;
                           //plik.close(); //???!!!
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


int User::addUser(std::string login,std::string password,std::string password_p,bool new_line) // 0-poprawne dane, 1-zle haslo, 2-nazwa zajeta, 3-zly login
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
                save_to_file(login,password,new_line);
                Statistics staty;
                staty.Add_new_user(login);
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
 // !! Ten bool new_line chyba nie potrzebny- w if(new_line) jest to samo. !!
void User::save_to_file(std::string login,std::string password,bool new_line)
{
    std::filesystem::path copy = docPath;
    std::ofstream plik(copy/="users.txt", std::ios_base::app);
    if (new_line)
    {
        plik<<"\n" <<login << " " << password;
        // plik << login << " " << password << '\n';
    }
    else
    {
        plik << login << " " << password << '\n';
       //plik<<login << " " << password;
    }
    plik.close();
   // plik<<login << " " << password;
}


int User::removeUser(std::string login,std::string password)
{
  if(findUser(login))
  {
   if (checkPassword(password))
     {
      std::filesystem::path copy = docPath;
      std::ifstream plik(copy/="users.txt");
         if (plik.is_open())
            {
             std::vector<std::string> lines;
             std::string line;
             while (std::getline(plik, line))
                {
                lines.push_back(line);
                }
             plik.close();
             lines.erase(lines.begin() + (pos/2)-1);
             std::ofstream plik_2(copy);
                if(plik_2.is_open())
                    {
                    for (const auto& line : lines)
                    {
                    plik_2 << line << std::endl;
                    }
                    plik_2.close();
                    return 0; //usunieto
                    }
            }
      }
      else
      {
          return 1; //zle haslo

      }
  }

  else
  {
      return 5; //nie znaleziono uzytkownika;
  }

}


int User::editLogin(std::string login,std::string password,std::string new_login,std::string new_login_p)
{

    std::cout << "edycja loginu";
    int a =-1;
   // a=removeUser(login,password);
    if (findUser(login)) // jezeli znalezniono
    {
        if (new_login == new_login_p)
      {
      std::cout << "login: " << login << " ";
      std::cout << "haslo: " << password<< " ";
      std::cout << "new_login: " << new_login<< " ";
      if(checkPassword(password)) // jeżeli poprawne hasło
     { a = addUser(new_login,password,password,false);
      if (a == 0) // udało sie dodać to usuń
        {
        a = removeUser(login,password);
        SaveGame s;
        s.Change_username(new_login,login);
        Statistics stat;
        stat.Change_username(new_login,login);

        qDebug() << "Zmieniono";
        }
      //save_to_file(new_login,password,false);
      return a;
        }
      return 4;
        }
        else // złe powtórzenie
        {
            return 6;
        }
    }
    else // brak użytkownika
    {
        return 5;
    }

// a = 0 udało się
// a = 1 złe hasło-regex
// a = 2 zajęty login
// a = 3 zły login- nie spełnia regex-a
// a = 4 złe hasło
// a = 5 nie ma takiego użtkownika- z find user
// 6 - loginy się różnią
}




int User::editPassword(std::string login,std::string password,std::string new_password,std::string new_password_p)
{

    std::cout << "edycja loginu";
    int a =-1;
   // a=removeUser(login,password);
    if (findUser(login)) // jezeli znalezniono
    {
        if (new_password == new_password_p)
      {
      std::cout << "login: " << login << " ";
      std::cout << "haslo: " << password<< " ";
      std::cout << "new_haslo: " << new_password<< " ";
      if(checkPassword(password)) // jeżeli poprawne hasło
     {
      a = removeUser(login,password);
      if (a == 0) // udało sie usunąc to dodaj
        {
        a = addUser(login,new_password,new_password,false);
        }
      if (a != 0)
      {
          addUser(login,password,password,false);
      }
      return a;
        }
      return 4;
        }
        else // złe powtórzenie
        {
            return 6;
        }
    }
    else // brak użytkownika
    {
        return 5;
    }

// a = 0 udało się
// a = 1 złe hasło-regex
// a = 2 zajęty login
// a = 3 zły login- nie spełnia regex-a
// a = 4 złe hasło
// a = 5 nie ma takiego użtkownika- z find user
// 6 - hasla się różnią
}
