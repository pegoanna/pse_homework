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

        void set_x_pos(int px);
        void set_y_pos(int py);


    private:
        int x;
        int y;
};

#endif