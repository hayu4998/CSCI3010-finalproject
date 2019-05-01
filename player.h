#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QColor>
#include "land.h"
#include <vector>
#include <QMessageBox>

class Player:public QObject{
    Q_OBJECT
public:

    Player();

    static Player* Player_Factory(bool type);

    int get_gold(){return gold_;}

    int get_solider(){return soldier_;}

    int Max_Soilder();

    void Transform_Soldier(int soldier);

    void grow();

    bool Add_Land(Land * L);

    void Lost_Land(Land *L);

    bool Battle_Lost();

    void Conquering_Land();

    QString Output_Data();

signals:

    void take_turn();

private:

    int gold_mine_;

    int forest_;

    int iron_mine_;

    int gold_;

    int population_;

    int lumber_;

    int soldier_;

    int iron_;

    static int turn_;

    static bool player_turn_;

};

class AI: public Player{

public:
    AI():Player(){}

    void Choose();

    int target_;
};

#endif // PLAYER_H
