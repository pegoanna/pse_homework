#include "reynold.h"

mutex mut;
condition_variable readyToControlPosition;
condition_variable readyToSafe;
condition_variable readyToMove;

//movimenti calcolati
int performed{0};
//movimenti effettuati
int moved{0};

void reynold_alghoritm(vector<Boid>& BoidVector, vector<Boid>::iterator BoidItr, int movement, int number_Boid){
    
    unique_lock<mutex> lock(mut);
    int movement_performed{0};

    while (movement_performed < movement){
        //criteri di Reynold
        BoidItr->separation(BoidVector);
        BoidItr->alignment(BoidVector);
        BoidItr->cohesion(BoidVector);

        //movimento calcolato
        performed++;

        if (performed < number_Boid){
            readyToMove.wait(lock);
        }
        else{
            readyToMove.notify_all();
        }

        BoidItr->move_boid();

        //boid mosso
        moved++;

        if(moved == number_Boid){
            readyToSafe.notify_one();
        }
        //movimento eseguito per ogni boid del vettore
        movement_performed++;
        readyToControlPosition.wait(lock);
    }
   
}


void saveCoordinates(ostream& file, vector<Boid>& BoidVector, int movement){
    unique_lock<mutex> lock(mut);
    int movement_saved{0};

    while (movement_saved < movement){
        readyToSafe.wait(lock);

        //salvataggio posizione dei boid
        for(auto itr{BoidVector.begin()}; itr !=BoidVector.end(); ++itr){
            file<<itr->return_boid_pos()<<" ";
        }
        file<<endl;
        //incremento dei movimenti salvati
        movement_saved++;
        //reset degli indici
        performed = 0;
        moved = 0;

        readyToControlPosition.notify_all();

    }
}