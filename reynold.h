#ifndef REYNOLD_H
#define REYNOLD_H

#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "boid.h"

using namespace std;


void reynold_alghoritm(vector<Boid>& BoidVector, vector<Boid>::iterator BoidItr, int movement, int number_Boid);
void saveCoordinates(ostream& file, vector<Boid>& BoidVector, int movement);


#endif