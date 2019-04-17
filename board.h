#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include <QColor>
#include <QGraphicsItem>

#include "land.h"
#include "player.h"

class Board{
public:

    Board();

    void setBoard(bool p1,bool p2);

    void taketurn(bool p1, bool p2);

    Land *Play_board_[8][8];

private:

    Player *P1_;
    Player *P2_;

    AI *A1_;
    AI *A2_;

    bool p1_;
    bool p2_;
};

#endif // BOARD_H
