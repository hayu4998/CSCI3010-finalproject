#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QColor>

class Player:public QObject{
    Q_OBJECT
public:

    Player();

    void transform_soilder(float gold);

    void grow();

signals:

    void take_turn();

private:

    int gold_mine_;

    int forest_;

    int iron_mine_;

    float gold_;

    int population_;

    int lumber_;

    int soilder_;

    float iron_;

    static int turn_;

};

class AI: public Player{

public:
    AI();

    void take_turn();

private:
    int target_;
};

#endif // PLAYER_H
