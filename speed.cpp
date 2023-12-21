#include <iostream>
using namespace std;
#include <math.h>

#include "speed.h"
//constructor
Speed::Speed(float vxx, float vyy)
    :vx{vxx}, vy{vyy}
{
    if (vx<0 || vx>100 || vy<0 || vy>100)
    cerr <<"invalidate speed\n";
    exit(1);

}

const Speed& default_speed()
{
    static Speed ss{0,0};
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

