//speed.h 
#ifndef SPEED_H
#define SPEED_H

class Speed{
    public:
        //constructors
        Speed(float vx, float vy);
        Speed();

        //const members
        float x_spe() const;
        float y_spe() const;
        void set_x_spe(float sx);
        void set_y_spe(float sy);

        //function
        float abs_speed();

    private:
        float vx;
        float vy;    
};

#endif