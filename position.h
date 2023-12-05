//position.h 
#ifndef POSITION_H
#define POSITION_H

class Position{
    public:
        //constructors
        Position(int x, int y);
        Position();

        //const members
        int x_pos() const;
        int y_pos() const;


    private:
        int x;
        int y;
};

#endif