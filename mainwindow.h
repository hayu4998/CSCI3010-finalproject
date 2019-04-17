#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
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

private slots:
    void Land_Clicked_Slot(Land * L);


private:
    Ui::MainWindow *ui;

    QGraphicsScene * scene;


};

#endif // MAINWINDOW_H
