#include <iostream>
#include <QtWidgets>

#include "board.h"

Board::Board(){

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(i==7 && j == 0){
                Play_board_[i][j] = new Land(true,i,j);
                connect(Play_board_[i][j], &Land::Land_Clicked,this,&Board::Land_Clicked_Slot);
            }else if(i == 0 && j == 7){
                Play_board_[i][j] = new Land(true,i,j);
                connect(Play_board_[i][j], &Land::Land_Clicked,this,&Board::Land_Clicked_Slot);
            }else{
                Play_board_[i][j] = new Land(false,i,j);
                connect(Play_board_[i][j], &Land::Land_Clicked,this,&Board::Land_Clicked_Slot);
            }
        }
    }

    P1_ = new Player;
    P2_ = new Player;

    A1_ = new AI;
    A2_ = new AI;

    player_turn_ = true;

    Stored_Land_ = new Land;

    Is_Start_ = true;

    active_land_near_by(0,7);
    active_land_near_by(7,0);

}

void Board::setBoard(bool p1,bool p2){
    p1_ = p1;
    p2_ = p2;

    //initial actived cells


    //active aviable squares
    player_turn_ = true;

}

void Board::taketurn(){
    active_land_near_by(Stored_Land_->get_x(),Stored_Land_->get_y());
}

void Board::active_land_near_by(int x, int y){
    for(int i = -1; i<2; i++){
        for(int j = -1; j<2; j++){
            if(x+i>=0 && x+i<8 && y+j>=0 & y+j<8){
                Play_board_[x+i][y+j]->Active_Land(player_turn_);
            }
        }
    }
    switch_turn();
}

void Board::Land_Clicked_Slot(Land *L){
    Stored_Land_ = L;
}

void Board::Start_Button_Clicked_Slot(){
    if(Is_Start_){

    }else{
        taketurn();
    }
}

