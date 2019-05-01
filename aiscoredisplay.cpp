#include "aiscoredisplay.h"
#include <QPainter>

AIScoreDisplay::AIScoreDisplay(int location, int width, int player){
    width_ = width*5;
    location_ = location;

    player_= player;
    player_ == 1? color_ = QColor(255,255,0):color_ =QColor(255,0,255);
}

QRectF AIScoreDisplay::boundingRect() const{
    return QRectF(0,location_,width_+100,height_);
}

QPainterPath AIScoreDisplay::shape() const{
    QPainterPath path;
    path.addRect(0,location_,width_+100, height_);
    return path;
}
void AIScoreDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));
    painter->drawRect(QRectF(0, 0, width_+100, height_));

    painter->setBrush(b);

    //QString Display_text = ("Player " + std::to_string(player_) + ": " + std::to_string(width_/10) + "->").c_str();
    //painter->drawText(QRectF(10+location_, 0, width_, height_),Qt::AlignCenter, Display_text);
}
