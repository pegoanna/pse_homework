#ifndef POSITION_H
#define POSITION_H

#include <ostream>

class Position{
    public:
        //costruttori
        Position(float x, float y);
        Position();

        //funzioni di ritorno
        float x_pos() const;
        float y_pos() const;

        void set_x_pos(float px);
        void set_y_pos(float py);

    private:
        float x;
        float y;
};


// operators
        std::ostream& operator<<(std::ostream& os, const Position& p);
   
#endif