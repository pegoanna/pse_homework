#ifndef BOID_H
#define BOID_H

#include "position.h"
#include "speed.h"
#include <vector>
using std::vector;
#include <ostream>

class Boid{
    public:

        //costruttori
        Boid(Position position_boid, Speed speed_boid);
        Boid();

        //funzioni di ritorno
        Position return_boid_pos() const;
        Speed return_boid_spe() const;

        //funzione per muovere il boid
        void move_boid();

        //funzione per il calcolo della distanza
        float distance(Boid& second_boid);

        //criteri per l'algoritmo
        void separation(vector<Boid>& otherboid);
        void alignment(vector<Boid>& otherboid);
        void cohesion(vector<Boid>& otherboid);

    private:

        void check_edge();
        void check_speed();

        Position position_boid;
        Speed speed_boid;
};


// operators
        std::ostream& operator<<(std::ostream& os, const Boid& b);

#endif