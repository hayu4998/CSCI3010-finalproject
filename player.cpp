#include "player.h"
#include <QDebug>
//tract player turn
bool Player::player_turn_ = true;
// keep tract of number of turn
int Player::turn_ = 0;

Player::Player(){

    //initalize starting conditions;
    gold_ = 200;
    population_ = 20;
    lumber_ = 200;
    soldier_ = 0;
    iron_ = 50;
    gold_mine_ = 0;
    forest_ = 1;
    iron_mine_ = 0;
}

Player* Player::Player_Factory(bool type){
    if(type){
        return new Player;
    }else{
        return new AI;
    }
}

void Player::grow(){

    //growing schema
    gold_ += 50*gold_mine_;
    population_ += population_/10;
    lumber_ += 50 * forest_;
    iron_ += 20*iron_mine_;
    player_turn_ = !player_turn_;
    turn_++;
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
    QMessageBox Box;
    if(soldier_ == 0){
        Box.setText("You Lost the battle!");
        Box.setInformativeText("You don't have any soldier");
        Box.exec();
        return false;
    }

    if(rand()%60 < soldier_){
        int lost = soldier_/10+1;
        soldier_ -= lost;

        Box.setText("You Win the battle!");
        Box.setInformativeText(("The battle Lost is" + std::to_string(lost) + "Soldiers").c_str());
        Box.exec();
        return true;
    }else{
        int lost = soldier_/10+1;
        soldier_ -= lost;

        Box.setText("You Lost the battle");
        Box.setInformativeText(("The battle Lost is" + std::to_string(lost) + "Soldiers").c_str());
        Box.exec();
        return false;
    }

}

void Player::Choose(Land * Game_Board[8][8]){

    Resource Target;
    if(get_forest()<3){
        Target = Resource::Forest;
    }else if (get_gold_mine()<=get_iron_mine()/2 || gold_mine_ <= 2) {
        Target = Resource::Gold;
    }else{
        Target = Resource::Iron;
    }

    Land * choice = optimal_Choice(Game_Board,Target);

    if(get_turn() == 9 || get_turn() == 10){
        Transform_Soldier(Max_Soilder());
    }

    emit take_turn(choice);
}

Land* Player::optimal_Choice(Land *Game_Board[8][8], Resource Target){

    Land* Choice = new Land;
    bool indicator = false;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(Game_Board[i][j]->get_Is_Active_Player1() && get_player_turn()){
                if(Target == Game_Board[i][j]->get_resource() && Game_Board[i][j]->get_belongs() == 0){
                    Choice = Game_Board[i][j];
                    indicator = true;
                    break;
                }
            }else if(Game_Board[i][j]->get_Is_Active_Player2() && !get_player_turn()){
                if(Target == Game_Board[i][j]->get_resource() && Game_Board[i][j]->get_belongs() == 0){
                    Choice = Game_Board[i][j];
                    indicator = true;
                    break;
                }
            }
        }
    }
    //qDebug()<<"Break Here";
    if(!indicator && Target == Resource::Forest){
        Choice = optimal_Choice(Game_Board,Resource::Gold);
    }else if(!indicator && Target == Resource::Gold){
        Choice = optimal_Choice(Game_Board,Resource::Iron);
    }else if(!indicator && Target == Resource::Iron){
        Choice = optimal_Choice(Game_Board,Resource::Iron);
    }
    return Choice;
}

int AI::Max_Soilder(){
    int limit_gold = get_gold() / 20;
    int limit_iron = get_iron() / 5;
    if(limit_gold > limit_iron){
        return get_population()>limit_iron? limit_iron:get_population() ;
    }else{
        return get_population()>limit_gold? limit_gold:get_population() ;
    }
}
