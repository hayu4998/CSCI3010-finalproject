#include <iostream>
#include <QtWidgets>

#include "board.h"

Board::Board(){



    P1_ = new Player;
    P2_ = new Player;

    A1_ = new AI;
    A2_ = new AI;

    player_turn_ = true;

    Stored_Land_ = new Land;

    Is_Start_ = true;

    Null_Land_ = new Land;

}

void Board::setBoard(bool p1,bool p2){
    p1_ = p1;
    p2_ = p2;

    qDebug()<<"Start setting board";
    //initial cells
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
    qDebug()<<"Start setting avaliable slots";

    //active aviable squares
    player_turn_ = true;
    Is_Start_ = false;

    active_land_near_by(0,7);
    active_land_near_by(7,0);

    //setting Player data display
    emit Update_Player_Data_Signal(Update_Player_Data(true),true);
    emit Update_Player_Data_Signal(Update_Player_Data(false),false);
}

void Board::taketurn(bool type){

    active_land_near_by(Stored_Land_->get_x(),Stored_Land_->get_y());
    Stored_Land_ ->Set_Land();
    update_resources(Stored_Land_,type);

    emit Update_Player_Data_Signal(Update_Player_Data(true),true);
    emit Update_Player_Data_Signal(Update_Player_Data(false),false);

    Stored_Land_ = Null_Land_;
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

void Board::Land_Clicked_Slot(Land *L, bool player){

    if(L == Null_Land_){

        Stored_Land_ = L;
        if(player){
            QColor C;
            C = QColor(255,200,0);
            L -> Set_Color(C);
        }else{
            QColor C;
            C = QColor(255,0,200);
            L -> Set_Color(C);
        }

    }else{

        QColor Default;
        if(Stored_Land_->get_belongs() == 0){
            Default = QColor(255,255,255);
        }else if(Stored_Land_->get_belongs() == 1){
            Default = QColor(255,255,0);
        }else{
            Default = QColor(255,0,255);
        }
        Stored_Land_->Set_Color(Default);
        Stored_Land_ = L;

        if(player){
            QColor C;
            C = QColor(255,200,0);
            L -> Set_Color(C);
        }else{
            QColor C;
            C = QColor(255,0,200);
            L -> Set_Color(C);
        }
    }
}

void Board::Start_Button_Clicked_Slot(bool p1, bool p2){
    if(Is_Start_){
        setBoard(p1,p2);
    }else{
        if(Stored_Land_->get_belongs() == 0){
            taketurn(true);
        }else{
            taketurn(false);
        }

    }
}

void Board::update_resources(Land *L, bool type){

    if(type){

        if(p1_ && p2_){

            player_turn_?P1_->Add_Land(L):P2_->Add_Land(L);

        }else if(p1_ || p2_){

            player_turn_?P1_->Add_Land(L):A2_->Add_Land(L);

        }else{

            player_turn_?A1_->Add_Land(L):A2_->Add_Land(L);

        }

    }else{

        Player * tmp;
        if(p1_ && p2_){

            player_turn_?tmp = P1_ : tmp = P2_;

        }else if(p1_ || p2_){
            player_turn_? tmp = P1_ : tmp = A2_;

        }else{
            player_turn_? tmp = A1_ : tmp = A2_;

        }

        //updating resource if conqur
        if(tmp->Battle_Lost()){
            update_resources(L,true);
        }
    }

}

QString Board::Update_Player_Data(bool player_turn){
    QString result;
    if(p1_ && p2_){

        result = player_turn? "Player 1: \n" + P1_->Output_Data():"Player 2: \n"+P2_->Output_Data();

    }else if(p1_ || p2_){

        result = player_turn? "Player 1: \n" + P1_->Output_Data():"Player 2: \n"+A2_->Output_Data();

    }else{

        result = player_turn? "Player 1: \n" + A1_->Output_Data():"Player 2: \n"+A2_->Output_Data();
    }
    return result;
}
