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
        //funzione per il calcolo della distanza
        float distance(Boid& second_boid);

        void separation(vector<Boid>& otherboid);
        void cohesion(vector<Boid>& otherboid);

    private:
        Position position_boid;
        Speed speed_boid;
};

#endif