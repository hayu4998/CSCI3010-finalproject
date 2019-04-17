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

    Board * game = new Board;

    qDebug()<<"Example status";

    for(int i = 0 ; i<8 ; i++){
        for(int j = 0; j<8 ; j++){

            scene->addItem(game->Play_board_[i][j]);

            connect(game->Play_board_[i][j], &Land::Land_Clicked, this, &MainWindow::Land_Clicked_Slot);

        }
    }

    //Land * test = new Land(false, 0,0);
    //scene->addItem(test);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Land_Clicked_Slot(Land * L){
    qDebug()<< L->get_x();
    qDebug()<< L->get_y();
}
