#include <iostream>
#include <QtWidgets>

#include "board.h"

Board::Board(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(i==0 && j == 0){
                Play_board_[i][j] = new Land(true,i,j);
            }else if(i == 7 && j == 7){
                Play_board_[i][j] = new Land(true,i,j);
            }else{
                Play_board_[i][j] = new Land(false,i,j);
            }
        }
    }

    P1_ = new Player;
    P2_ = new Player;

    A1_ = new AI;
    A2_ = new AI;
}

void Board::setBoard(bool p1,bool p2){
    p1_ = p1;
    p2_ = p2;
}
