#include <iostream>
#include <ostream>
#include "boid.h"
#include <vector>
#include <fstream>
//librerie per thread e mutex
#include <thread>
#include <mutex>
#include "reynold.h"

using std::vector;
using namespace std;



#define X_MIN 0
#define X_MAX 50
#define Y_MIN 0
#define Y_MAX 30



#define DIM_VECTOR 15
#define NUMBER_MOVEMENT 50
int main()
{

    srand(static_cast<unsigned> (time(0)));
    vector<Boid> boid_vector;
    vector<thread> thread_boid_vector;

    ofstream outfile  ("coordinates.txt")   ;
    outfile<<X_MIN<<" "<<X_MAX<<" "<<Y_MIN<<" "<<Y_MAX<<endl;
    /*
    // senza thread
    for (int i{0}; i <DIM_VECTOR ; ++i)
    {
        boid_vector.push_back(Boid()); 
    }
    for (int i{0}; i <DIM_VECTOR ; ++i)
    {
        cout<<"coordinate iniziali boid numero "<<i<<" : "<<boid_vector[i]<<endl;  
    }

    int count{0};

    for (int j{0}; j<NUMBER_MOVEMENT; ++j){
        for (auto itr{boid_vector.begin()}; itr != boid_vector.end() ; ++itr)
        {
            cout<< "CONTROLLO IL BOID NUMERO "<<count<<*itr<<endl;
            itr->separation(boid_vector);
            itr->alignment(boid_vector);
            itr->cohesion(boid_vector);
            itr->move_boid();
            cout<< "il boid numero "<<count<<" si sposta a"<<*itr<<endl;  
            outfile<<itr->return_boid_pos()<<" "; 
            count++;
        }
        outfile<<endl;
        cout<<endl;
        count=0;
    }
    */


   //con thread
   for(int i{0}; i<DIM_VECTOR; ++i){
        boid_vector.push_back(Boid());
   }
   
   for(auto itr{boid_vector.begin()}; itr != boid_vector.end(); ++itr){
        thread_boid_vector.push_back(thread{reynold_alghoritm, ref(boid_vector), itr, NUMBER_MOVEMENT});
   }

    cout<<"Avvio del boid"<<DIM_VECTOR<<"per"<<NUMBER_MOVEMENT<<"movimenti"<<endl;
   
   for(auto itr{thread_boid_vector.begin()}; itr != thread_boid_vector.end(); ++itr){
        itr->join();
   }

   cout<<"risultati salvati nel  file delle coordinate"<<endl;

    

    outfile.close();

    return 0;	
}