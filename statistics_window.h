#ifndef STATISTICS_WINDOW_H
#define STATISTICS_WINDOW_H

#include <QWidget>
#include<QListWidget>
#include<QListWidgetItem>
#include<QVBoxLayout>
#include<QComboBox>
#include<QTableView>
#include<QMessageBox>
#include<QLabel>
#include<QPushButton>
#include<QStandardItemModel>
#include"Result_struct.h"
#include"statistics.h"
#include"my_button.h"
#include<memory>
class Statistics_Window : public QWidget
{
    Q_OBJECT
public:
    explicit Statistics_Window(std::string user,QWidget *parent = nullptr);
    void Show_results(int player);
        std::vector<std::vector<Result>>wyniki;
private:
    QVBoxLayout *layout;
    QTableView *tabela;
    std::shared_ptr<QLabel>brak_statystyk;
    std::shared_ptr<QLabel>napis;
    QStandardItemModel* model;
    QComboBox *player_choice;
    Statistics statystyki;
    std::shared_ptr<my_button>back_button;
    void Choice();
    void Set_best(int player);
    void Remove_rows();
    int Get_user_num();
    int Get_length(QString str, int i);
    QString Get_level(int p, int i);
    std::string user;
    void emit_go_back();
public slots:
    void Win_Sumarry(int _lvl, int _m, int _h, QTime _time);

signals:
    void go_back(); // wracanie z Statystyk do menu głównego
    void go_menu(); // idź do menu po wygranej- z podsumowania
    void go_stat(); // Przejscie do zaklady statystyki
};

#endif // STATISTICS_WINDOW_H
