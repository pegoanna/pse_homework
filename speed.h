//speed.h 
#ifndef SPEED_H
#define SPEED_H

class Speed{
    public:
        //constructors
        Speed(int vx, int vy);
        Speed();

        //const members
        int x_spe() const;
        int y_spe() const;


    private:
        int vx;
        int vy;    
};

#endif