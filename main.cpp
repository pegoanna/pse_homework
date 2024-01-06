#include "boid.h"
#include "reynold.h"
using namespace std;

#define X_MIN 0
#define X_MAX 50
#define Y_MIN 0
#define Y_MAX 30

#define NUMBER_OF_BOID 30
#define NUMBER_MOVEMENT 50

int main(){

    srand(static_cast<unsigned> (time(0)));
    vector<Boid> boid_vector;
    vector<thread> thread_boid_vector;

    ofstream outfile  ("coordinates.txt")   ;
    outfile<<X_MIN<<" "<<X_MAX<<" "<<Y_MIN<<" "<<Y_MAX<<endl;
    
    for(int i{0}; i<NUMBER_OF_BOID; ++i){
        boid_vector.push_back(Boid());
    }
    
    cout<<"Avvio della simulazione con "<<NUMBER_OF_BOID<<" boid che subiranno "<<NUMBER_MOVEMENT<<" movimenti"<<endl;
    
    //vettore di thread corrispondente ai boid
    for(auto itr{boid_vector.begin()}; itr != boid_vector.end(); ++itr){
        thread_boid_vector.push_back(thread{reynold_alghoritm, ref(boid_vector), itr, NUMBER_MOVEMENT, NUMBER_OF_BOID});
    }
    //thread per il salvataggio delle coordinate
    thread save{saveCoordinates, ref(outfile), ref(boid_vector), NUMBER_MOVEMENT};
    
    for(auto itr{thread_boid_vector.begin()}; itr != thread_boid_vector.end(); ++itr){
        itr->join();
    }
    
    save.join();
    
    cout<<"Fine della simulazione e risultati salvati nel file"<<endl;
    
    outfile.close();
    
    return 0;	
}