#include "player.h"

Player::Player(){

    //initalize starting conditions;
    gold_ = 200;
    population_ = 50;
    lumber_ = 200;
    soilder_ = 0;
    iron_ = 50;
    gold_mine_ = 0;
    forest_ = 0;
    iron_mine_ = 0;

}
// keep tract of number of turn
int Player::turn_ = 0;

void Player::grow(){

    //growing schema
    gold_ += 50*gold_mine_;
    population_ += population_/10;
    lumber_ += 100 * lumber_;
    iron_ += 20*iron_mine_;
}

