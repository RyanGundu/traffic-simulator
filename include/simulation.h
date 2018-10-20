#ifndef SIMULATION
#define SIMULATION

#include "../include/LinkedListAPI.h"

/**
* Checks The general direction of a car and corresponds it with 
the time it takes to cross
*@param a cars general direction (F, L, R)
*/
double checkTimeToCross(char direc);

/**
*Simulates a cars actual arrival tima at an intersection aswell as its completion time
*@param all the lists (N, E, S, W)
*/
void simulation (List *N, List *E, List *S, List *W);

#endif
