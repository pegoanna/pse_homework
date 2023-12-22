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
#define D_SEP 10
#define D_CA 10
#define AVOIDFACTOR 10
#define ALIGNFACTOR 10
#define CENTERINGFACTOR 10


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
        if(distance(*itr) < D_SEP){
            close_dx += position_boid.x_pos() - itr->position_boid.x_pos();
            close_dy += position_boid.y_pos() - itr->position_boid.y_pos();
        }
    }
    
    speed_boid.set_x_spe(speed_boid.x_spe() + close_dx * AVOIDFACTOR);
    speed_boid.set_y_spe(speed_boid.y_spe() + close_dy * AVOIDFACTOR);
}

void Boid::alignment(vector<Boid>& otherboid){
    float xvel_avg{0};
    float yvel_avg{0};
    float close_boids{0};

    
    for(auto itr=otherboid.begin(); itr<otherboid.end(); ++itr){
        if(distance(*itr) < D_CA){
            xvel_avg += itr->speed_boid.x_spe();
            yvel_avg += itr->speed_boid.y_spe();
            close_boids += 1;
        }
    }
    if (close_boids>0){
    xvel_avg = xvel_avg/close_boids;
    yvel_avg = yvel_avg/close_boids;
    }

    speed_boid.set_x_spe((xvel_avg - speed_boid.x_spe())*ALIGNFACTOR);
    speed_boid.set_y_spe((yvel_avg - speed_boid.y_spe())*ALIGNFACTOR);
}

void Boid::cohesion(vector<Boid>& otherboid){
    float xpos_avg{0};
    float ypos_avg{0};
    float close_boids{0};

    
    for(auto itr=otherboid.begin(); itr<otherboid.end(); ++itr){
        if(distance(*itr) < D_CA){
            xpos_avg += itr->position_boid.x_pos();
            ypos_avg += itr->position_boid.y_pos();
            close_boids += 1;
        }
    }
    if (close_boids>0){
    xpos_avg = xpos_avg/close_boids;
    ypos_avg = ypos_avg/close_boids;
    }

    speed_boid.set_x_spe((xpos_avg - position_boid.x_pos())*CENTERINGFACTOR);
    speed_boid.set_y_spe((ypos_avg - position_boid.y_pos())*CENTERINGFACTOR);
}