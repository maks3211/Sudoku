#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <shlobj.h>
#include <iostream>
#include<filesystem>
//#include <codecvt>
#include<string>
#include<vector>
#include<fstream>
//#include<locale>
//#include <Windows.h>
//#include<algorithm>

#include<QPushButton>


class SaveGame
{
private:
     std::filesystem::path docPath;
     void set_index(int &row,int &col);
     std::vector<std::tuple<int,int,int>>for_buttons; // przechowuje trojki- ktore guziki i na jakie wartosci

public:
    SaveGame();
    void make_save(std::vector<std::vector<int>>&full_board,std::vector<std::vector<int>>&removed_board ,QPushButton *m_button[9][9],int hint,int mis,std::string user,std::string time, int lvl);
    std::string load_save(std::vector<std::vector<int>>&full_board,std::vector<std::vector<int>>&removed_board,QPushButton *m_button[9][9],int &hint,int &mis,std::string user, int &lvl);
    std::vector<std::tuple<int,int,int>> get_buttons();
    bool is_file(std::string user);
    void Change_username(std::string new_name,std::string old_name);
};

#endif // SAVEGAME_H
