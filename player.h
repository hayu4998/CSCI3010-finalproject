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

    virtual int Max_Soilder();

    void Transform_Soldier(int soldier);

    void grow();

    virtual bool Add_Land(Land * L);

    void Lost_Land(Land *L);

    virtual bool Battle_Lost();

    void Conquering_Land();

    QString Output_Data();

    int get_forest(){return forest_;}

    int get_gold_mine(){return gold_mine_;}

    int get_iron_mine(){return iron_mine_;}

    int get_iron(){return iron_;}

    int get_population(){return population_;}

    int get_lumber(){return lumber_;}

    void increment_resource(Resource R);

    void Change_Resource(std::string s, int quantity);

    static int get_turn(){return turn_;}

    static bool get_player_turn(){return player_turn_;}

    void Choose(Land *Array[8][8]);

    Land* optimal_Choice(Land *Array[8][8], Resource Target);

    static void Set_player_turn(bool player_turn){player_turn_ = player_turn;}

signals:

    void take_turn(Land * target);

    void train_soldiers(int num);

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

    int Max_Soilder() override;

    bool Add_Land(Land * L) override;

    bool Battle_Lost() override;
};

#endif // PLAYER_H
