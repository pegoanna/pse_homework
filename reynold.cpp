#include "reynold.h"

mutex mut;
condition_variable readyToControlPosition;
condition_variable readyToSafe;
condition_variable readyToMove;

void reynold_alghoritm(vector<Boid>& VectorBoid, vector<Boid>::iterator BoidItr, int movement){
    
    //unique_lock<mutex> mlock(mut);

    cout<<"Numero della thread: "<<std::this_thread::get_id()<<endl;

    int movement_performed{0};

    while (movement_performed < movement){
        //readyToControlPosition.wait(mlock);
        mut.lock();
        cout<<"inizio calcoli"<<endl;
        BoidItr->separation(VectorBoid);
        BoidItr->alignment(VectorBoid);
        BoidItr->cohesion(VectorBoid);
        mut.unlock();
        //readyToControlPosition.notify_one();
        movement_performed++;

        if (BoidItr == (VectorBoid.end()-1)){
            readyToSafe.notify_one();
        }
    }
   
}


void saveCoordinates(ostream file, vector<Boid>& VectorBoid, int movement){
    unique_lock<mutex> mlock(mut);
    int movement_saved{0};

    while (movement_saved < movement){
        readyToSafe.wait(mlock);

        for(auto itr{VectorBoid.begin()}; itr !=VectorBoid.end(); ++itr){
            itr->move_boid();
            file<<itr->return_boid_pos();
        }
        file<<endl;

        movement_saved++;
    }
}