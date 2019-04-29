#include "player.h"

//tract player turn
bool Player::player_turn_ = true;
// keep tract of number of turn
int Player::turn_ = 0;

Player::Player(){

    //initalize starting conditions;
    gold_ = 200;
    population_ = 50;
    lumber_ = 200;
    soldier_ = 0;
    iron_ = 50;
    gold_mine_ = 0;
    forest_ = 1;
    iron_mine_ = 0;
}


void Player::grow(){

    //growing schema
    gold_ += 50*gold_mine_;
    population_ += population_/10;
    lumber_ += 100 * forest_;
    iron_ += 20*iron_mine_;
    player_turn_ = !player_turn_;
}


void Player::Add_Land(Land *L){
    Resource R = L->get_resource();
    if(R == Resource::Forest){
        forest_++;
    }else if(R == Resource::Gold){
        gold_mine_++;
    }else{
        iron_mine_++;
    }
    population_+=L->get_population();
    grow();
}

QString Player::Output_Data(){

    std::string Output = "";
    Output += "Population: " + std::to_string(population_) + "\n";
    Output +=  "Gold: " + std::to_string(gold_) + " with " + std::to_string(gold_mine_) + " gold mines \n";
    Output +=  "Lumber: " + std::to_string(lumber_) + " with " + std::to_string(forest_) + " forests \n";
    Output += "Iron: " + std::to_string(iron_) + " with " + std::to_string(iron_mine_) + " iron mines \n";
    Output += "Soldier: " + std::to_string(soldier_) + "\n";

    return QString(Output.c_str());
}
