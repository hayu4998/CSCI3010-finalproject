#ifndef LAND_H
#define LAND_H
#include <QWidget>
#include <QColor>
#include <QGraphicsItem>
#include <vector>

enum class Resource{Forest, Gold, Iron};
class Land: public QObject, public QGraphicsItem{

    Q_OBJECT

public:

    Land(){}

    Land(bool, int x, int y);

    int get_x(){return x_;}

    int get_y(){return y_;}

    Resource get_resource(){return resource_;}

    int get_population(){return population_;}

    QColor get_color(){return color_;}

    int get_belongs(){return belongs_;}

    void Active_Land(bool p){p?Is_Active_Player1_ = true : Is_Active_Player2_ = true;}

    void Occupy(){Is_Occupied_ = true;}

    void switch_player(){player_ = !player_;}

    void Set_Land();

    void Set_Color(QColor Color){color_ = Color;update();}

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:

    void Land_Clicked(Land *L, bool player);

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:

    bool Is_Occupied_;

    Resource resource_;

    int population_;

    QColor color_;

    int x_;

    int y_;

    const static int width_ = 90;

    bool Is_Active_Player1_;

    bool Is_Active_Player2_;

    static bool player_;

    int belongs_;

};

#endif // LAND_H
