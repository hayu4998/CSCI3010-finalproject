#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include "board.h"


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



private slots:
    void Land_Clicked_Slot(Land * L);

    void on_Start_Button_clicked();

    void on_Multiplayer_Mode_Button_clicked();

    void on_Singleplayer_Mode_Button_clicked();

    void Player_Data_Display_Slot(QString Output, bool player);

signals:
    void Start_Button_Clicked(bool p1,bool p2);

private:
    Ui::MainWindow *ui;

    QGraphicsScene * scene;

    bool Is_Start_Turn_;

    Board *Game_Board_;

    int Game_Mode_;

    QMessageBox *Fault_Operation_Pop_Up_;

    bool breaker_;

};

#endif // MAINWINDOW_H
