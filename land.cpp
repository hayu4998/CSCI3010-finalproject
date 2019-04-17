#include "land.h"
#include <cstdlib>
#include <QtWidgets>
#include <iostream>
#include <QDebug>
bool Land::player_ = false;

Land::Land(){

}

Land::Land(bool start, int x, int y){

    QColor C(255,255,255);
    color_ = C;
    x_ = x;
    y_ = y;

    if(start){
        resource_ = Resource::Forest;
        Is_Occupied_ = false;
        population_ = 50;
    }else{
        int rd = rand() % 3;
        rd == 0? resource_ = Resource::Forest:(rd == 1? resource_ = Resource::Gold:Resource::Iron);
        Is_Occupied_ = false;
        population_ = rand() % 50 +1;
        QColor C(255,255,255);
        color_ = C;
    }
}

QRectF Land::boundingRect() const{
    return QRectF(25+x_*width_,25+y_*width_,width_,width_);
}

QPainterPath Land::shape() const
{
    QPainterPath path;
    path.addRect(25+x_*width_, 25+y_*width_, width_, width_);
    return path;
}


void Land::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_.dark(option->state & QStyle::State_Sunken ? 120 : 100)));
    painter->drawRect(QRectF(25+width_*x_, 25+width_*y_,width_,width_));
    painter->setBrush(b);
}

void Land::mousePressEvent(QGraphicsSceneMouseEvent *event){

    qDebug()<<"Mouse Press Detected";

    QGraphicsItem::mousePressEvent(event);

    if(!Is_Occupied_){
        Is_Occupied_ = true;
        QColor C;
        if(player_){
            C = QColor(255,255,0);
        }else{
            C = QColor(255,0,255);
        }
        color_ = C;
    }

    emit Land_Clicked(this);
    update();
}



