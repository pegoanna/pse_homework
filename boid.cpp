#include <iostream>
using namespace std;

#include "boid.h"

//constructor
Boid::Boid(Position pos_, Speed spe_)
    :pos{pos_}, spe{spe_}
{  
}

const Boid& default_boid()
{
    static Boid bb{Position(), Speed()};
    return bb;
}

Boid::Boid()
    :pos{default_boid().boid_pos()}, spe{default_boid().boid_spe()}
{ 
}

//return pos e spe boid
Position Boid::boid_pos() const{
    return pos;
}

Speed Boid::boid_spe() const{
    return spe;
}