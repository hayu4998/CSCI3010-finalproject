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
    lumber_ += 50 * forest_;
    iron_ += 20*iron_mine_;
    player_turn_ = !player_turn_;
}


bool Player::Add_Land(Land *L){
    if(lumber_ < 150){
        QMessageBox M;
        M.setText("Fail to Conqur the Land!");
        M.setInformativeText("Get more lumber to build a road to the land");
        M.exec();
        return false;
    }
    if(gold_<10){
        QMessageBox M;
        M.setText("Fail to Conqur the Land!");
        M.setInformativeText("Not enough gold to hire labor");
        M.exec();
        return false;
    }
    Resource R = L->get_resource();
    if(R == Resource::Forest){
        forest_++;
    }else if(R == Resource::Gold){
        gold_mine_++;
    }else{
        iron_mine_++;
    }
    population_+=L->get_population();
    lumber_ -= 150;
    gold_ -= 10;
    return true;
}

void Player::Lost_Land(Land *L){
    Resource R = L->get_resource();
    if(R == Resource::Forest){
        forest_--;
    }else if(R == Resource::Gold){
        gold_mine_--;
    }else{
        iron_mine_--;
    }
    population_-=L->get_population();
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

int Player::Max_Soilder(){
    int limit_gold = gold_ / 20;
    int limit_iron = iron_ / 5;
    if(limit_gold > limit_iron){
        return population_>limit_iron? limit_iron:population_ ;
    }else{
        return population_>limit_gold? limit_gold:population_ ;
    }
}


void Player::Transform_Soldier(int soldier){
    gold_ -= 20*soldier;
    iron_ -= 5*soldier;
    population_ -= soldier;
    soldier_ += soldier;
}

bool Player::Battle_Lost(){

    if(soldier_ == 0){
        return false;
    }

    if(rand()%60 < soldier_){
        int lost = soldier_/10+1;
        soldier_ -= lost;
        QMessageBox Box;
        Box.setText("You Win the battle!");
        Box.setInformativeText(("The battle Lost is" + std::to_string(lost) + "Soldiers").c_str());
        Box.exec();
        return true;
    }else{
        int lost = soldier_/10+1;
        soldier_ -= lost;
        QMessageBox Box;
        Box.setText("You Lost the battle");
        Box.setInformativeText(("The battle Lost is" + std::to_string(lost) + "Soldiers").c_str());
        Box.exec();
        return false;
    }

}
