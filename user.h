#ifndef USER_H
#define USER_H




#include <shlobj.h>
#include <iostream>
#include<filesystem>
#include<string>
#include<vector>
#include<fstream>
#include <regex>

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
int addUser(std::string login,std::string password,std::string password_p);
void save_to_file(std::string login,std::string password);
void removeUser(std::string login,std::string password);
void editLogin(std::string login,std::string password,std::string new_login,std::string new_login_p);
void editPassword(std::string login,std::string password,std::string new_password,std::string new_password_p);
};

#endif // USER_H
