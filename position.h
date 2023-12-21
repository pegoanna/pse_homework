//position.h 
#ifndef POSITION_H
#define POSITION_H

class Position{
    public:
        //constructors
        Position(float x, float y);
        Position();

        //const members
        float x_pos() const;
        float y_pos() const;

        void set_x_pos(float px);
        void set_y_pos(float py);


    private:
        float x;
        float y;
};

#endif