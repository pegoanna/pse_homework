#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

#include "boid.h"

#define TURNFACTOR 2
#define LEFTMARGIN 10
#define RIGHTMARGIN 1910
#define BOTTOMMARGIN 10
#define TOPMARGIN 1070
#define DSEP 10
#define AVOIDFACTOR 10


#define MAXSPEED 20
#define MINSPEED 0


//constructor
Boid::Boid(Position pos_, Speed spe_)
    :position_boid{pos_}, speed_boid{spe_}
{  
}

const Boid& default_boid()
{
    static Boid bb{Position(), Speed()};
    return bb;
}

Boid::Boid()
    :position_boid{default_boid().return_boid_pos()}, speed_boid{default_boid().return_boid_spe()}
{ 
}

//return pos e spe boid
Position Boid::return_boid_pos() const{
    return position_boid;
}

Speed Boid::return_boid_spe() const{
    return speed_boid;
}

void Boid::check_edge(){
    if (position_boid.x_pos()<LEFTMARGIN){
        speed_boid.set_x_spe(speed_boid.x_spe() + TURNFACTOR);
    }
    if (position_boid.x_pos()>RIGHTMARGIN){
        speed_boid.set_x_spe(speed_boid.x_spe() - TURNFACTOR);
    }
    if (position_boid.y_pos()<BOTTOMMARGIN){
        speed_boid.set_y_spe(speed_boid.y_spe() + TURNFACTOR);
    }
    if (position_boid.x_pos()>TOPMARGIN){
        speed_boid.set_y_spe(speed_boid.y_spe() - TURNFACTOR);
    }
}

void Boid::move_boid(){
    position_boid.set_x_pos(position_boid.x_pos() + speed_boid.x_spe());
    position_boid.set_y_pos(position_boid.y_pos() + speed_boid.y_spe());
}

void Boid::check_speed(){
    if (speed_boid.abs_speed() > MAXSPEED){
        speed_boid.set_x_spe((speed_boid.x_spe()/speed_boid.abs_speed())*MAXSPEED);
        speed_boid.set_y_spe((speed_boid.y_spe()/speed_boid.abs_speed())*MINSPEED);
    }
    if (speed_boid.abs_speed() < MINSPEED){
        speed_boid.set_x_spe((speed_boid.x_spe()/speed_boid.abs_speed())*MINSPEED);
        speed_boid.set_y_spe((speed_boid.y_spe()/speed_boid.abs_speed())*MAXSPEED);
    }
}

float Boid::distance(Boid& second_boid){
    float deltax=position_boid.x_pos() - second_boid.position_boid.x_pos();
    float deltay=position_boid.y_pos() - second_boid.position_boid.y_pos();

    return sqrt((deltax*deltax)+deltay*deltay);
}



void Boid::separation(vector<Boid>& otherboid){
    float close_dx{0};
    float close_dy{0};
    
    for(auto itr=otherboid.begin(); itr<otherboid.end(); ++itr){
        if(distance(*itr) < DSEP){
            close_dx += position_boid.x_pos() - itr->position_boid.x_pos();
            close_dy += position_boid.y_pos() - itr->position_boid.y_pos();
        }
    }
    
    speed_boid.set_x_spe(speed_boid.x_spe() + close_dx * AVOIDFACTOR);
    speed_boid.set_y_spe(speed_boid.y_spe() + close_dy * AVOIDFACTOR);
}