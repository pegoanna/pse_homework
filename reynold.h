#ifndef REYNOLD_H
#define REYNOLD_H

#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "boid.h"

using namespace std;


void reynold_alghoritm(vector<Boid>& VectorBoid, vector<Boid>::iterator BoidItr, int movement);
void saveCoordinates(ostream file, vector<Boid>& VectorBoid, int movement);


#endif