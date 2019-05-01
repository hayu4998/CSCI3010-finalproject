#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(0));

    QGraphicsView * view = ui->graphicsView;

    scene = new QGraphicsScene;

    view->setScene(scene);

    Board* game = new Board;

    Game_Board_ = game;

    Is_Start_Turn_ = true;

    Game_Mode_ = 5;

    breaker_ = true;

    player_turn_ = true;

    QString Info_winning = "Winning Criteria: \n After 10 turns: \n\t 1.Twice Gold \n\t 2.Twice Land \n\t 3.Twice Soilder \n After 20 turns: \n\tEvery resource transfer to \n\tSoilders and the one with \n\tmore soilders win";
    QString Info_cost = "Cost: \n\t-Road: 150 lumber + 10 gold\n\t-Soldier: 20 gold + 5 iron + 1 population\n\t-War: More Soldier lead to higher chance to win.\n\tAttacker lost 10%+1 Soldiers, winner get the land";
    QString Info_gain = "Gain: \n\t-Forest: +50 lumber each turn\n\t-Gold Mine: +50 gold each turn\n\t-Iron Mine: +20 iron each turn";
    Start_Pop_Up_ = new QMessageBox;
    Start_Pop_Up_ -> setText("Game Rules:");
    Start_Pop_Up_ -> setInformativeText(Info_winning + "\n" + Info_cost + "\n" + Info_gain);

    connect(this,&MainWindow::Start_Button_Clicked,Game_Board_,&Board::Start_Button_Clicked_Slot);
    connect(Game_Board_,&Board::Update_Player_Data_Signal, this,&MainWindow::Player_Data_Display_Slot);
    connect(Game_Board_,&Board::Game_Over_Signal,this, &MainWindow::Game_Over_Slot);
    connect(Game_Board_,&Board::Turn_Update_Signal, this, &MainWindow::Turn_Update_Slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Land_Clicked_Slot(Land * L){
    qDebug()<< L->get_x();
    qDebug()<< L->get_y();
}

void MainWindow::on_Start_Button_clicked()
{
    qDebug()<<"Start Button click Detected";

    if(Game_Mode_ == 0){
        emit Start_Button_Clicked(true,true);
    }else if(Game_Mode_ == 1){
        emit Start_Button_Clicked(true,false);
    }else if(Game_Mode_ == 3){
        emit Start_Button_Clicked(false,false);
    }else{
        Fault_Operation_Pop_Up_ = new QMessageBox;
        Fault_Operation_Pop_Up_->setText("Error: Invalid Mode");
        Fault_Operation_Pop_Up_->setInformativeText("You haven't select mode");
        Fault_Operation_Pop_Up_->exec();
        breaker_ = false;
    }

    if(Is_Start_Turn_ && breaker_){
        QString s = "Finish Turn";
        ui->Start_Button->setText(s);
        for(int i = 0 ; i<8 ; i++){
            for(int j = 0; j<8 ; j++){

                scene->addItem(Game_Board_->Play_board_[i][j]);

                connect(Game_Board_->Play_board_[i][j], &Land::Land_Clicked, this, &MainWindow::Land_Clicked_Slot);

            }
        }
        ui->Player2_Train_Soilder_Button->setEnabled(false);
        ui->Player2_Soilder_Persentage_Bar->setEnabled(false);
        Is_Start_Turn_ = false;
    }else{
        player_turn_ = !player_turn_;
        if(player_turn_){
            ui->Player2_Train_Soilder_Button->setEnabled(false);
            ui->Player2_Soilder_Persentage_Bar->setEnabled(false);
            ui->Player1_Train_Soilder_Button->setEnabled(true);
            ui->Player1_Soilder_Persentage_Bar->setEnabled(true);
        }else{
            ui->Player2_Train_Soilder_Button->setEnabled(true);
            ui->Player2_Soilder_Persentage_Bar->setEnabled(true);
            ui->Player1_Train_Soilder_Button->setEnabled(false);
            ui->Player1_Soilder_Persentage_Bar->setEnabled(false);
        }

    }

    breaker_ = true;
}

void MainWindow::on_Multiplayer_Mode_Button_clicked()
{
    if(Is_Start_Turn_){
        Game_Mode_ = 0;
        ui->Multiplayer_Mode_Button->setText("Selected: Multiplayer Mode");
        ui->Singleplayer_Mode_Button->setText("Singleplayer");
    }
}

void MainWindow::on_Singleplayer_Mode_Button_clicked()
{
    if(Is_Start_Turn_){
        Game_Mode_ = 1;
        ui->Singleplayer_Mode_Button->setText("Selected: Singleplayer Mode");
        ui->Multiplayer_Mode_Button->setText("Multiplayer");
    }
}

void MainWindow::Player_Data_Display_Slot(QString Output, bool player, int soldier){
    if(player){
        ui->Player1_Text_Display->setText(Output);
        ui->Player1_Soilder_Persentage_Bar->setRange(0,soldier);
        ui->Player1_Soilder_Persentage_Bar->setTickInterval(soldier/10);
        ui->Player1_Soilder_Persentage_Bar->setTickPosition(QSlider::TicksBelow);
    }else{
        ui->Player2_Text_Display->setText(Output);
        ui->Player2_Soilder_Persentage_Bar->setRange(0,soldier);
        ui->Player2_Soilder_Persentage_Bar->setTickInterval(soldier/10);
        ui->Player2_Soilder_Persentage_Bar->setTickPosition(QSlider::TicksBelow);
    }
    ui->Player1_Quantity_Indicator_Label->setText("Quantity");
    ui->Player2_Quantity_Indicator_Label->setText("Quantity");
    ui->Player1_Soilder_Persentage_Bar->setValue(0);
    ui->Player2_Soilder_Persentage_Bar->setValue(0);
}

void MainWindow::on_Player1_Soilder_Persentage_Bar_valueChanged(int value){
    ui->Player1_Quantity_Indicator_Label->setText(("Quantity: "+std::to_string(value)).c_str());
}

void MainWindow::on_Player2_Soilder_Persentage_Bar_valueChanged(int value){
    ui->Player2_Quantity_Indicator_Label->setText(("Quantity: "+std::to_string(value)).c_str());
}

void MainWindow::on_Player1_Train_Soilder_Button_clicked()
{
    Game_Board_->Tranning_Soldiers(ui->Player1_Soilder_Persentage_Bar->value());
    emit Game_Board_->Update_Player_Data_Signal(Game_Board_->Update_Player_Data(true),true, Game_Board_->Get_Player_Soldier_Option(true));
}


void MainWindow::on_Player2_Train_Soilder_Button_clicked()
{
    Game_Board_->Tranning_Soldiers( ui->Player2_Soilder_Persentage_Bar->value());
    emit Game_Board_->Update_Player_Data_Signal(Game_Board_->Update_Player_Data(false),false, Game_Board_->Get_Player_Soldier_Option(false));

    //qDebug()<<ui->Player1_Soilder_Persentage_Bar->value();
}

void MainWindow::Game_Over_Slot(){
    qDebug()<<"EndGame Received";
    ui->Start_Button->setEnabled(false);
}

void MainWindow::on_Reset_Button_clicked()
{
    QGraphicsView * view = ui->graphicsView;

    scene = new QGraphicsScene;

    view->setScene(scene);

    ui->Player1_Text_Display->setText("");
    ui->Player2_Text_Display->setText("");

    ui->Start_Button->setEnabled(true);

}

void MainWindow::Turn_Update_Slot(int Turn){
    QString S = ("Turn: " +std::to_string(Turn)).c_str();
    if(Turn == 9){
        S = S + "\n BEWARE: Sudden Death start in next turn! Train your soldiers!";
    }
    ui->Turn_Indicator_Label->setText(S);

}
