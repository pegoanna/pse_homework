#include "reynold.h"

mutex mut;
condition_variable readyToControlPosition;
condition_variable readyToSafe;
condition_variable readyToMove;

int performed{0};
int moved{0};

void reynold_alghoritm(vector<Boid>& VectorBoid, vector<Boid>::iterator BoidItr, int movement, int number_Boid){
    
    unique_lock<mutex> lock(mut);
    int movement_performed{0};

    while (movement_performed < movement){
        
        BoidItr->separation(VectorBoid);
        BoidItr->alignment(VectorBoid);
        BoidItr->cohesion(VectorBoid);

        performed++;
        cout<<"Boid calcolati"<<performed<<endl;

        if (performed < number_Boid){
            readyToMove.wait(lock);
        }
        else{
            readyToMove.notify_all();
        }

        BoidItr->move_boid();

        moved++;
        cout<<"Boid mossi"<<moved<<endl;

        if(moved == number_Boid){
            readyToSafe.notify_one();
        }
        movement_performed++;
        cout<<"calcolo"<<movement_performed<<endl;
        readyToControlPosition.wait(lock);
    }
   
}


void saveCoordinates(ostream& file, vector<Boid>& VectorBoid, int movement){
    unique_lock<mutex> lock(mut);
    int movement_saved{0};

    while (movement_saved < movement){
        readyToSafe.wait(lock);

        for(auto itr{VectorBoid.begin()}; itr !=VectorBoid.end(); ++itr){
            file<<itr->return_boid_pos()<<" ";
        }
        file<<endl;

        movement_saved++;
        performed = 0;
        moved = 0;

        readyToControlPosition.notify_all();

    }
}