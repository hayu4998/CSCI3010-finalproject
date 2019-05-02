#ifndef AISCOREDISPLAY_H
#define AISCOREDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QColor>

class AIScoreDisplay: public QObject, public QGraphicsItem{

    Q_OBJECT

public:

    AIScoreDisplay(int location, int width, int player);

    void change_length(int width){width_ = width*5;update();}

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

    static const int height_ = 20;

    int width_;

    int location_;

    QColor color_;

    int player_;
};

#endif // AISCOREDISPLAY_H
