//boid.h 
#ifndef BOID_H
#define BOID_H

#include "position.h"
#include "speed.h"

class Boid{
    public:

        //constructors
        Boid(Position pos, Speed spe);
        Boid();

        Position boid_pos() const;
        Speed boid_spe() const;


    private:
        Position pos;
        Speed spe;
};

#endif