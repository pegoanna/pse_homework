#ifndef SPEED_H
#define SPEED_H

#include <ostream>

class Speed{
    public:
        //costruttori
        Speed(float vx, float vy);
        Speed();

        //funzioni di ritorno
        float x_spe() const;
        float y_spe() const;


        void set_x_spe(float sx);
        void set_y_spe(float sy);

        //funzioni per il calcolo della velocità assoluta
        float abs_speed();

    private:
        float vx;
        float vy;    
};


// operators
        std::ostream& operator<<(std::ostream& os, const Speed& s);
   

#endif