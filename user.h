#ifndef USER_H
#define USER_H




#include <shlobj.h>
#include <iostream>
#include<filesystem>
#include<string>
#include<vector>
#include<fstream>
#include <regex>
#include"savegame.h"
#include"statistics.h"

class User
{
 private:
    std::filesystem::path docPath;
    bool isCorrect();
bool find;
int pos;
public:
    User();
bool findUser(std::string login);
bool checkPassword(std::string password);
int addUser(std::string login,std::string password,std::string password_p,bool new_line=true);
void save_to_file(std::string login,std::string password,bool new_line=true);
int removeUser(std::string login,std::string password);
int editLogin(std::string login,std::string password,std::string new_login,std::string new_login_p);
int editPassword(std::string login,std::string password,std::string new_password,std::string new_password_p);
};

#endif // USER_H
