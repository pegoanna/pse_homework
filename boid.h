//boid.h 
#ifndef BOID_H
#define BOID_H

#include "position.h"
#include "speed.h"

class Boid{
    public:

        //constructors
        Boid(Position position_boid, Speed speed_boid);
        Boid();

        //return funtions
        Position return_boid_pos() const;
        Speed return_boid_spe() const;

        void move_boid();
        void check_edge();
        void check_speed();

    private:
        Position position_boid;
        Speed speed_boid;
};

#endif