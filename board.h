#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
//#include <QColor>
//#include <QGraphicsItem>

#include "land.h"
#include "player.h"

class Board: public QObject{
    Q_OBJECT
public:

    Board();

    void setBoard(bool p1,bool p2);

    void taketurn();

    void active_land_near_by(int i, int j);

    void switch_turn(){player_turn_ = !player_turn_;}

    Land *Play_board_[8][8];

public slots:

    void Land_Clicked_Slot(Land *L);

    void Start_Button_Clicked_Slot();

private:

    Player *P1_;
    Player *P2_;

    AI *A1_;
    AI *A2_;

    bool p1_;
    bool p2_;

    bool player_turn_;

    Land *Stored_Land_;

    bool Is_Start_;
};

#endif // BOARD_H
