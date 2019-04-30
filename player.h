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

    int Max_Soilder();

    void Transform_Soldier(int soldier);

    void grow();

    void Add_Land(Land * L);

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

    void take_turn();

    int target_;
};

#endif // PLAYER_H
