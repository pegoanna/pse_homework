#include <iostream>
using namespace std;
#include <ostream>
using std::ostream;
#include <math.h>

#include "speed.h"

#define MINSPEED 2
#define MAXSPEED 10

//constructor
Speed::Speed(float vxx, float vyy)
    :vx{vxx}, vy{vyy}
{
}

const Speed& default_speed()
{
    static Speed ss{MINSPEED,MINSPEED};
    return ss;
}

Speed::Speed()
    :vx{default_speed().x_spe()}, vy{default_speed().y_spe()}
{ 
}

//return x e y
float Speed::x_spe() const{
    return vx;
}

float Speed::y_spe() const{
    return vy;
}

// set speed value
void Speed::set_x_spe(float sx){
    vx=sx;
}
void Speed::set_y_spe(float sy){
    vy=sy;
}

//calcolo velocità assoluta
float Speed::abs_speed(){
    return sqrt(vx*vx + vy*vy);
}


// operators
ostream& operator<<(ostream& os, const Speed& s)
{
	return os << '(' << s.x_spe()
		<< ',' << s.y_spe() << ')';
}