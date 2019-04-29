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

    Start_Pop_Up_ = new QMessageBox;
    Start_Pop_Up_ -> setText("Winning Criteria:");
    Start_Pop_Up_ -> setInformativeText("After 10 turns: \n\t 1.Twice Gold \n\t 2.Twice Land \n\t 3.Twice Soilder \n After 20 turns: \n\tEvery resource transfer to \n\tSoilders and the one with \n\tmore soilders win");

    connect(this,&MainWindow::Start_Button_Clicked,Game_Board_,&Board::Start_Button_Clicked_Slot);
    connect(Game_Board_,&Board::Update_Player_Data_Signal, this,&MainWindow::Player_Data_Display_Slot);
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
        Is_Start_Turn_ = false;
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

void MainWindow::Player_Data_Display_Slot(QString Output, bool player){
    if(player){
        ui->Player1_Text_Display->setText(Output);
    }else{
        ui->Player2_Text_Display->setText(Output);
    }
}









