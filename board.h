#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include <iostream>
//#include <QColor>
//#include <QGraphicsItem>

#include "land.h"
#include "player.h"

class Board: public QObject{
    Q_OBJECT
public:

    Board();

    void setBoard(bool p1,bool p2);

    void taketurn(bool type);

    void active_land_near_by(int i, int j);

    void reactive_land_near_by(int i, int j, bool player);

    void switch_turn(){player_turn_ = !player_turn_;std::cout<<"Switch turn"<<std::endl;}

    bool update_resources(Land *L, bool type);

    QString Update_Player_Data(bool player_turn);

    int Get_Player_Soldier_Option(bool player);

    void Tranning_Soldiers(int soldiers);

    void Players_Resource_Grow();

    int End_Game();

    void AI_Start_Game();

    Land *Play_board_[8][8];

public slots:

    void Land_Clicked_Slot(Land *L);

    void Start_Button_Clicked_Slot(bool p1, bool p2);

    void AI_Choice_Slot(Land* L);



signals:

    void Update_Player_Data_Signal(QString Output, bool player, int soilders);

    void Game_Over_Signal(int result);

    void Turn_Update_Signal(int turn);

    void message_carrier(std::string Winning_message);

    void Start_Button_Clicked_Signal();

private:

    Player *P1_;
    Player *P2_;

    bool p1_;
    bool p2_;

    bool player_turn_;

    Land *Stored_Land_;

    bool Is_Start_;

    Land * Null_Land_;

    int turn_;
};

#endif // BOARD_H
