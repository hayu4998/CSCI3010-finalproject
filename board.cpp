#include <iostream>
#include <QtWidgets>

#include "board.h"

Board::Board(){

    turn_ = 0;

    player_turn_ = true;

    Stored_Land_ = new Land;

    Is_Start_ = true;

    Null_Land_ = new Land;

}

void Board::setBoard(bool p1,bool p2){
    p1_ = p1;
    p2_ = p2;

    P1_ = Player::Player_Factory(p1_);
    P2_ = Player::Player_Factory(p2_);

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
    emit Update_Player_Data_Signal(Update_Player_Data(true),true,Get_Player_Soldier_Option(true));
    emit Update_Player_Data_Signal(Update_Player_Data(false),false, Get_Player_Soldier_Option(false));
}

void Board::taketurn(bool type){



    if(update_resources(Stored_Land_,type)){
        Players_Resource_Grow();
        Stored_Land_ ->Set_Land();
        emit Update_Player_Data_Signal(Update_Player_Data(true),true, Get_Player_Soldier_Option(true));
        emit Update_Player_Data_Signal(Update_Player_Data(false),false, Get_Player_Soldier_Option(false));

        active_land_near_by(Stored_Land_->get_x(),Stored_Land_->get_y());

    }else if(Stored_Land_->get_belongs() != 0){
        Players_Resource_Grow();
        QColor C;
        if (!player_turn_){
            C = QColor(255,255,0);
            Stored_Land_ -> Set_Color(C);
        }else{
            C = QColor(255,0,255);
            Stored_Land_ -> Set_Color(C);
        }

        emit Update_Player_Data_Signal(Update_Player_Data(true),true, Get_Player_Soldier_Option(true));
        emit Update_Player_Data_Signal(Update_Player_Data(false),false, Get_Player_Soldier_Option(false));

        switch_turn();
        Stored_Land_->switch_player();
    }else{
        Players_Resource_Grow();
        Stored_Land_ ->Set_Color(QColor(255,255,255));
        switch_turn();
        Stored_Land_->switch_player();
    }

    End_Game();
    std::cout<<"turn: "<<turn_<<std::endl;
    turn_++;

    Stored_Land_ = Null_Land_;


}

void Board::active_land_near_by(int x, int y){

    for(int i = -1; i<2; i++){
        for(int j = -1; j<2; j++){
            if(x+i>=0 && x+i<8 && y+j>=0 && y+j<8){
                Play_board_[x+i][y+j]->Active_Land(player_turn_);
            }
        }
    }
    switch_turn();
}

void Board::reactive_land_near_by(int x, int y, bool player){

    for(int i = -1; i<2; i++){
        for(int j = -1; j<2; j++){
            if(x+i>=0 && x+i<8 && y+j>=0 && y+j<8){
                Play_board_[x+i][y+j]->Active_Land(player);
            }
        }
    }
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
        setBoard(p1,p2);QColor C;
    }else{
        if(Stored_Land_->get_belongs() == 0){
            taketurn(true);
        }else{
            taketurn(false);
        }

    }
}

bool Board::update_resources(Land *L, bool type){
    if(L == Null_Land_){return false;}
    bool result;
    if(type){

        result = player_turn_?P1_->Add_Land(L):P2_->Add_Land(L);

    }else{

        Player * attack;
        Player * Defence;

        if(player_turn_){
            attack = P1_;
            attack = P2_;
        }else{
            attack = P1_;
            Defence = P2_;
        }

        //updating resource if conqur
        if(attack->Battle_Lost()){
            L->Set_Belongs(player_turn_);
            //reset active cells
            for(int i = 0 ; i<8 ;i++){
                for(int j = 0 ; j<8 ;j++){

                    Play_board_[i][j]->Deactive_Land();
                }
            }

            for(int i = 0 ; i<8 ;i++){

                for(int j = 0 ; j<8 ;j++){

                    if(Play_board_[i][j]->get_belongs() == 1){
                        reactive_land_near_by(i,j,true);
                    }else if(Play_board_[i][j]->get_belongs() == 2){
                        reactive_land_near_by(i,j,false);
                    }
                }
            }

            Defence->Lost_Land(L);

            return update_resources(L,true);

        }else{
            return false;
        }
    }
    return result;
}

QString Board::Update_Player_Data(bool player_turn){
    QString result;

    result = player_turn? "Player 1: \n" + P1_->Output_Data():"Player 2: \n"+P2_->Output_Data();

    return result;
}

int Board::Get_Player_Soldier_Option(bool player){
    int max_soldier;

    max_soldier = player?P1_->Max_Soilder():P2_->Max_Soilder();

    return max_soldier;
}

void Board::Tranning_Soldiers(int soldiers){

    player_turn_?P1_->Transform_Soldier(soldiers):P2_->Transform_Soldier(soldiers);

}

void Board::Players_Resource_Grow(){

    player_turn_?P1_->grow():P2_->grow();

}

void Board::End_Game(){

    Player * P1;
    Player * P2;

    P1 = P1_ ;
    P2 = P2_;

    QMessageBox M;
    if(turn_>12 && turn_<20){
        if(P1->get_gold() <= P2->get_gold()/2){
            M.setText("Game Over");
            M.setInformativeText("Player 2 win with Economic Overthrow");
            M.exec();
            emit Game_Over_Signal();
        }else if(P2->get_gold() <= P1->get_gold()/2){
            M.setText("Game Over");
            M.setInformativeText("Player 1 win with Economic Overthrow");
            M.exec();
            emit Game_Over_Signal();
        }else if(P1->get_solider() < P2->get_solider()/2){
            M.setText("Game Over");
            M.setInformativeText("Player 2 win with Military deterrence");
            M.exec();
            emit Game_Over_Signal();
        }else if(P2->get_solider() < P1->get_solider()/2){
            M.setText("Game Over");
            M.setInformativeText("Player 1 win with Military deterrence");
            M.exec();
            emit Game_Over_Signal();
        }else{
            int P1_Land_count = 0;
            int P2_Land_count = 0;
            for(int i = 0 ; i<8 ;i++){
                for(int j = 0 ; j<8 ;j++){
                    if(Play_board_[i][j]->get_belongs() == 1){
                        P1_Land_count++;
                    }else if(Play_board_[i][j]->get_belongs() == 2){
                        P2_Land_count++;
                    }
                }
            }
            if(P1_Land_count <= P2_Land_count/2){
                M.setText("Game Over");
                M.setInformativeText("Player 2 win with Desperate Potential(2X Land)");
                M.exec();
                emit Game_Over_Signal();
            }else if(P2_Land_count <= P1_Land_count/2){
                M.setText("Game Over");
                M.setInformativeText("Player 1 win with Desperate Potential(2X Land)");
                M.exec();
                emit Game_Over_Signal();
            }
        }

    }else if(turn_ == 20){
        if(P1->Max_Soilder() < P2->Max_Soilder()){
            M.setText("Game Over");
            M.setInformativeText("Player 2 win in the final battle with more soldiers");
            M.exec();
        }else if(P1->Max_Soilder() > P2->Max_Soilder()){
            M.setText("Game Over");
            M.setInformativeText("Player 1 win in the final battle with more soldiers");
            M.exec();
        }else{
            M.setText("Game Over");
            M.setInformativeText("Draw");
            M.exec();
        }
        emit Game_Over_Signal();
    }
}




















