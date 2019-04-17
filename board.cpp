#include <iostream>
#include <QtWidgets>

#include "board.h"

Board::Board(bool p1, bool p2){
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
    p1_ = p1;
    p2_ = p2;

    if(p1 && p2){
        P1_ = new Player;
        P2_ = new Player;
    }else if (p1 || p2){
        P1_ = new Player;
        A1_ = new AI;
    }else{
        A1_ = new AI;
        A2_ = new AI;
    }

}
