#include <iostream>
using std::cout;
using std::endl;
#include <ostream>
#include "boid.h"
#include <vector>
#include <fstream>

using std::vector;
using namespace std;

#define DIM_VECTOR 1
#define NUMBER_MOVEMENT 50
int main()
{

    vector<Boid> boid_vector;

    ofstream outfile  ("coordinates.txt")   ;

    
    cout<<"Ciao Alberto"<<endl;
    srand(static_cast<unsigned> (time(0)));
    Boid Alberto;
    cout << "Creato boid con valori: "<< Alberto << "con velocità assoluta: " << Alberto.return_boid_spe().abs_speed() << endl;

    for (int i = 0; i < NUMBER_MOVEMENT ; ++i)
    {
        Alberto.move_boid();
        outfile << "Alberto si muove in posizione " << Alberto.return_boid_pos() << " con velocità "  << Alberto.return_boid_spe() << endl;
        
        cout << "Alberto si muove in posizione " << Alberto.return_boid_pos() << " con velocità "  << Alberto.return_boid_spe() << endl;
    }
    
    
    
    /*for (int i{0}; i <DIM_VECTOR ; ++i)
    {
        boid_vector.push_back(Boid()); 
    }
    for (int i{0}; i <DIM_VECTOR ; ++i)
    {
        cout<<"coordinate iniziali boid numero "<<i<<" : "<<boid_vector[i]<<endl;  
    }
    for (int j{0}; j<NUMBER_MOVEMENT; ++j){
        for (auto itr{boid_vector.begin()}; itr != boid_vector.end() ; ++itr)
        {
            itr->move_boid();
            cout<<*itr<<endl;  
        }
    }*/

    outfile.close();

    return 0;	
}