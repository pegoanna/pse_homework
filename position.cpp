#include <iostream>
using namespace std;

#include "position.h"

//constructor
Position::Position(float xx, float yy)
    :x{xx}, y{yy}
{
    if (x<0 || x>1920 || y<0 || y>1080)
    cerr <<"invalidate position\n";
    exit(1);

}

const Position& default_position()
{
    static Position pp{0,0};
    return pp;
}

Position::Position()
    :x{default_position().x_pos()}, y{default_position().y_pos()}
{ 
}

//return x e y
float Position::x_pos() const{
    return x;
}

float Position::y_pos() const{
    return y;
}

//set position value
void Position::set_x_pos(float px){
    x=px;
}
void Position::set_y_pos(float py){
    y=py;
}