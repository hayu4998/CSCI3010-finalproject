#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include "board.h"
#include "aiscoredisplay.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMessageBox *Start_Pop_Up_;

    void switch_Player();

    void AI_Turn_Iterator();

private slots:
    void Land_Clicked_Slot(Land * L);

    void on_Start_Button_clicked();

    void on_Multiplayer_Mode_Button_clicked();

    void on_Singleplayer_Mode_Button_clicked();

    void Player_Data_Display_Slot(QString Output, bool player, int soldier);

    void on_Player1_Soilder_Persentage_Bar_valueChanged(int value);

    void on_Player2_Soilder_Persentage_Bar_valueChanged(int value);

    void on_Player1_Train_Soilder_Button_clicked();

    void on_Player2_Train_Soilder_Button_clicked();

    void Game_Over_Slot(int result);

    void on_Reset_Button_clicked();

    void Turn_Update_Slot(int Turn);

    void on_Simulate_Slide_Bar_valueChanged(int value);

    void on_Simulation_Start_Button_clicked();

    void Message_receiver(std::string);

    void AI_Start_Click_Slot();

signals:
    void Start_Button_Clicked(bool p1,bool p2);

private:
    Ui::MainWindow *ui;

    QGraphicsScene * scene;

    QGraphicsScene * AI_scene;

    bool Is_Start_Turn_;

    Board *Game_Board_;

    int Game_Mode_;

    QMessageBox *Fault_Operation_Pop_Up_;

    bool breaker_;

    bool player_turn_;

    int Simulations_Left_;

    int Player1_win_count;

    int Player2_win_count;

    AIScoreDisplay *Player1_Score_display_;

    AIScoreDisplay *Player2_Score_display_;

    std::string Winning_Message_;
};

#endif // MAINWINDOW_H
