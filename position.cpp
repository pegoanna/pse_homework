#include <iostream>
using namespace std;
#include <ostream>
using std::ostream;

#include "position.h"

#define LEFTMARGIN 2
#define RIGHTMARGIN 48
#define BOTTOMMARGIN 2
#define TOPMARGIN 28

//constructor
Position::Position(float xx, float yy)
    :x{xx}, y{yy}
{
}

const Position& default_position()
{
    static Position pp{0,0};
    return pp;
}

Position::Position()
    :x{default_position().x_pos()}, y{default_position().y_pos()}
{
   // x += static_cast<float> (rand())/(RAND_MAX/(RIGHTMARGIN - LEFTMARGIN ));
   // y += static_cast<float> (rand())/(RAND_MAX/(TOPMARGIN - BOTTOMMARGIN ));
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
     

// operators
ostream& operator<<(ostream& os, const Position& p)
{
	return os  << p.x_pos()
		<< ' ' << p.y_pos();
}