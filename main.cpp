#include <iostream>
using std::cout;
using std::endl;
#include <ostream>
#include "boid.h"
#include <vector>
using std::vector;

#define DIM_VECTOR 10
int main()
{

    vector<Boid> boid_vector;
    
    cout<<"Ciao Alberto"<<endl;
    srand(static_cast<unsigned> (time(0)));
    Boid Alberto;
    cout << "Posizione iniziale del boid: "<< Alberto <<endl;
    
    
    for (int i{0}; i <DIM_VECTOR ; ++i)
    {
        boid_vector.push_back(Boid()); 
    }
    for (int i{0}; i <DIM_VECTOR ; ++i)
    {
        cout<<"coordinate iniziali boid numero "<<i<<" : "<<boid_vector[i]<<endl;  
    }

    for (auto itr{boid_vector.begin()}; itr != boid_vector.end() ; ++itr)
    {
        itr->move_boid();
        cout<<*itr<<endl;  
    }
 






    /*
    copy(boid_vector.cbegin(), boid_vector.cend(),
		operator<<(cout,boid_vector.cbegin())); //iteratore per l'output
	cout << endl;*/





/*
	Date default_d;
	cout << "Default date: " << default_d << endl;
	Date today{1978,Date::Month::jun,25};  // colloquial style
	Date tomorrow = today;  // copy constructor
	tomorrow.add_day(1);
	Date next_year = today;
	next_year.add_year(1);
	cout << "Today: " << today << endl;
	cout << "Tomorrow: " << tomorrow << endl;
	cout << "Next year: " << next_year << endl;
	Date invalid_date = Date{2004,Date::Month::dec,-5};   // verbose style
*/





	return 0;	
}



















