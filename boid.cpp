#include <iostream>
using namespace std;
#include <math.h>
#include <ostream>
using std::ostream;
#include "boid.h"
#include <vector>
using std::vector;

#define TURNFACTOR 3

#define LEFTMARGIN 2
#define RIGHTMARGIN 48
#define BOTTOMMARGIN 2
#define TOPMARGIN 28

#define D_SEP 7
#define D_CA 4

#define AVOIDFACTOR 0.7
#define ALIGNFACTOR 0.7
#define CENTERINGFACTOR 0.7

#define MAXSPEED 7
#define MINSPEED 2


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
    position_boid.set_x_pos( position_boid.x_pos() + static_cast<float> (rand())/(RAND_MAX/(RIGHTMARGIN - LEFTMARGIN )));
    position_boid.set_y_pos( position_boid.y_pos() + static_cast<float> (rand())/(RAND_MAX/(TOPMARGIN - BOTTOMMARGIN )));
    float abs_speed{MINSPEED + static_cast <float> (rand())/(RAND_MAX/(MAXSPEED - MINSPEED ))};
    speed_boid.set_x_spe(static_cast<float> (rand())/(RAND_MAX/( 2 * abs_speed)) - abs_speed);
    float vy_abs{sqrt(abs_speed*abs_speed - speed_boid.x_spe()*speed_boid.x_spe())};
    speed_boid.set_y_spe(2 * vy_abs * signbit( 2 * rand() - RAND_MAX) - vy_abs);
}

//return pos e spe boid
Position Boid::return_boid_pos() const{
    return position_boid;
}

Speed Boid::return_boid_spe() const{
    return speed_boid;
}

void Boid::check_edge(){
    if (position_boid.x_pos() + speed_boid.x_spe() < LEFTMARGIN){
        speed_boid.set_x_spe(speed_boid.x_spe() + TURNFACTOR);
        //cout << "Incrementata vx " << return_boid_spe() << endl;
        if((speed_boid.abs_speed() > MAXSPEED) || (speed_boid.abs_speed() < MINSPEED)){
            check_speed();
        }
    }
    if (position_boid.x_pos() + speed_boid.x_spe() > RIGHTMARGIN){
        speed_boid.set_x_spe(speed_boid.x_spe() - TURNFACTOR);
        //cout << "Decrementata vx" << return_boid_spe() << endl;
        if((speed_boid.abs_speed() > MAXSPEED) || (speed_boid.abs_speed() < MINSPEED)){
            check_speed();
        }
    }
    if (position_boid.y_pos() + speed_boid.y_spe() < BOTTOMMARGIN){
        speed_boid.set_y_spe(speed_boid.y_spe() + TURNFACTOR);
        //cout << "Incrementata vy" << return_boid_spe() << endl;
        if((speed_boid.abs_speed() > MAXSPEED) || (speed_boid.abs_speed() < MINSPEED)){
            check_speed();
        }
    }
    if (position_boid.y_pos() + speed_boid.y_spe() > TOPMARGIN){
        speed_boid.set_y_spe(speed_boid.y_spe() - TURNFACTOR);
        //cout << "Decrementata vy" << return_boid_spe() << endl;
        if((speed_boid.abs_speed() > MAXSPEED) || (speed_boid.abs_speed() < MINSPEED)){
            check_speed();
        }
    }

    
}

void Boid::move_boid(){
    check_edge();
    position_boid.set_x_pos(position_boid.x_pos() + speed_boid.x_spe());
    position_boid.set_y_pos(position_boid.y_pos() + speed_boid.y_spe());
    //cout<<"boid spostato alla posizione"<<return_boid_pos()<<endl;
}

void Boid::check_speed(){
    if (speed_boid.abs_speed() > MAXSPEED){
        float abs_value = speed_boid.abs_speed();
        //cout << "Fattore di scala: " << floorf((MAXSPEED/abs_value)* 100) / 100<< endl;
        speed_boid.set_x_spe(speed_boid.x_spe()*(floorf((MAXSPEED/abs_value)* 100) / 100));
        speed_boid.set_y_spe(speed_boid.y_spe()*(floorf((MAXSPEED/abs_value)* 100) / 100));
        //cout << "Modicata velocità max " << return_boid_spe() << " con valore assoluto " << speed_boid.abs_speed()  << endl;
    }
    if (speed_boid.abs_speed() < MINSPEED){
        float abs_value = speed_boid.abs_speed();
        //cout << "Fattore di scala: " << ceilf(MINSPEED/abs_value * 100) / 100 << endl;
        speed_boid.set_x_spe(speed_boid.x_spe()*(ceilf((MINSPEED/abs_value)* 100) / 100));
        speed_boid.set_y_spe(speed_boid.y_spe()* (ceilf((MINSPEED/abs_value)* 100) / 100));
        //cout << "Modicata velocità min " << return_boid_spe() << " con valore assoluto " << speed_boid.abs_speed()  << endl;
    }
}

float Boid::distance(Boid& second_boid){
    float deltax=position_boid.x_pos() - second_boid.position_boid.x_pos();
    float deltay=position_boid.y_pos() - second_boid.position_boid.y_pos();
    return (sqrt((deltax*deltax)+(deltay*deltay)));
}



void Boid::separation(vector<Boid>& otherboid){
    float close_dx{0};
    float close_dy{0};
    
    for(auto itr=otherboid.begin(); itr<otherboid.end(); ++itr){
        //cout<<"distanza boid"<<distance(*itr)<<endl;
        if((distance(*itr) <= D_SEP) && (distance(*itr)!= 0)){
            close_dx += position_boid.x_pos() - itr->position_boid.x_pos();
            close_dy += position_boid.y_pos() - itr->position_boid.y_pos();
        }
    }
    speed_boid.set_x_spe(speed_boid.x_spe() + close_dx * AVOIDFACTOR);
    speed_boid.set_y_spe(speed_boid.y_spe() + close_dy * AVOIDFACTOR);
    //cout<<"SEPARATION modifica"<<return_boid_spe()<<endl;
    check_speed();
    //cout<<"SEPARATION modifica per superazione limite "<<return_boid_spe()<<endl;
}

void Boid::alignment(vector<Boid>& otherboid){
    float xvel_avg{0};
    float yvel_avg{0};
    float close_boids{0};

    
    for(auto itr=otherboid.begin(); itr<otherboid.end(); ++itr){
        //cout<<"distanza boid"<<distance(*itr)<<endl;
        if((distance(*itr) < D_CA) && (distance(*itr) != 0)){
            xvel_avg += itr->speed_boid.x_spe();
            yvel_avg += itr->speed_boid.y_spe();
            close_boids += 1;
        }
    }
    if (close_boids>0){
    xvel_avg = xvel_avg/close_boids;
    yvel_avg = yvel_avg/close_boids;
    }

    speed_boid.set_x_spe(speed_boid.x_spe() + ((xvel_avg - speed_boid.x_spe())*ALIGNFACTOR));
    speed_boid.set_y_spe(speed_boid.y_spe() + ((yvel_avg - speed_boid.y_spe())*ALIGNFACTOR));
    
    //cout<<"ALIGNMENT modifica"<<return_boid_spe()<<endl;
    check_speed();
    //cout<<"ALIGNMENT modifica per superazione limite "<<return_boid_spe()<<endl;
}

void Boid::cohesion(vector<Boid>& otherboid){
    float xpos_avg{0};
    float ypos_avg{0};
    float close_boids{0};

    
    for(auto itr=otherboid.begin(); itr<otherboid.end(); ++itr){
        //cout<<"distanza boid"<<distance(*itr)<<endl;
        if((distance(*itr) < D_CA) && (distance(*itr) != 0)){
            xpos_avg += itr->position_boid.x_pos();
            ypos_avg += itr->position_boid.y_pos();
            close_boids += 1;
        }
    }
    if (close_boids>0){
    xpos_avg = xpos_avg/close_boids;
    ypos_avg = ypos_avg/close_boids;
    speed_boid.set_x_spe(speed_boid.x_spe() + ((xpos_avg - position_boid.x_pos())*CENTERINGFACTOR));
    speed_boid.set_y_spe(speed_boid.y_spe() + ((ypos_avg - position_boid.y_pos())*CENTERINGFACTOR));
    }

    
    //cout<<"COHESION modifica"<<return_boid_spe()<<endl;
    check_speed();
    //cout<<"COHESION modifica per superazione limite "<<return_boid_spe()<<endl;
}

// operators
ostream& operator<<(ostream& os, const Boid& b)
{
	return os << '(' << b.return_boid_pos()
		<< ',' << b.return_boid_spe() << ')';
}
