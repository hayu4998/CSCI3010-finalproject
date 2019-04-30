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

    void taketurn(bool type);

    void active_land_near_by(int i, int j);

    void switch_turn(){player_turn_ = !player_turn_;}

    bool update_resources(Land *L, bool type);

    Land *Play_board_[8][8];

    QString Update_Player_Data(bool player_turn);

    int Get_Player_Soldier_Option(bool player);

    void Tranning_Soldiers(int soldiers);

    void Players_Resource_Grow();

public slots:

    void Land_Clicked_Slot(Land *L, bool player);

    void Start_Button_Clicked_Slot(bool p1, bool p2);

signals:

    void Update_Player_Data_Signal(QString Output, bool player, int soilders);

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

    Land * Null_Land_;
};

#endif // BOARD_H
