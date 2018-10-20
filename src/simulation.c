#include "../include/simulation.h"
#include "../include/car.h"
#include "../include/LinkedListAPI.h"

/**
* Checks The general direction of a car and corresponds it with 
the time it takes to cross
*@param a cars general direction (F, L, R)
*/
double checkTimeToCross(char direc) {

	if (direc == 'F')
		return 2;
	if (direc == 'L')
		return 2.5;
	if (direc == 'R')
		return 1;

	return 0;
}

/**
*Simulates a cars actual arrival tima at an intersection aswell as its completion time
*@param all the lists (N, E, S, W)
*/
void simulation (List *N, List *E, List *S, List *W) {


	double globalTimer = 1;
	double lightTimer = 1;
	
	int lightDirection = 0;
	int x = 0;
	int flag = 0;
	double y = 0;

	double arrivalTime = 0.0;
	double pastComplete[4]; //Stores a cars completion time if it cannot pass

	const double LEFT = 2.5;
	const double RIGHT = 1;
	const double FORWARD = 2;

	List *currentList = E;
	
	if (N->head != NULL)
		currentList = N;
	else if (E->head != NULL) {
		currentList = E;
		globalTimer = globalTimer + 14;
	}
	else if (S->head != NULL) {
		currentList = S;
		globalTimer = globalTimer + 28;
	}
	else if (W->head != NULL) {
		currentList = W; 
		globalTimer = globalTimer + 42;
	}


	Node *temp = currentList->head;
	Car *car;

	printf("Initial Vehicle Information  Intersection Arrival Time  Completed at Time\n"); 

	while (1) {

		/* if all lists are empty */
		 if (N->head == NULL && E->head == NULL && S->head == NULL && W->head == NULL)
			break;
		
		if (flag == 0) {
			y = 15;
		} else {
			y = 14;
		}

		while (lightTimer < y) {

			car = (Car *)temp->data;

			arrivalTime = car->time; 

			if (car->time < pastComplete[lightDirection])
				arrivalTime = pastComplete[lightDirection];

			
			if (car->time <= globalTimer && lightTimer < 11) {

				if (car->direc2 == 'F') { 

					globalTimer = globalTimer + FORWARD;
					lightTimer = lightTimer + FORWARD;
				} else if (car->direc2 == 'L') {
					globalTimer = globalTimer + LEFT;
					lightTimer = lightTimer + LEFT;
				} else if (car->direc2 == 'R') {
					globalTimer = globalTimer + RIGHT;;
					lightTimer = lightTimer + RIGHT;
				}

				pastComplete[lightDirection] = globalTimer;
				printf("%c %c %.1lf %30.1lf %30.1lf\n",car->direc1,car->direc2,car->time, arrivalTime,globalTimer);

				/* if last car in list add remaining time and go to next Light direction */
				if (temp->next == NULL) {
					globalTimer = globalTimer - lightTimer + 14;
					deleteNodeFromList(currentList, car);
					break;

				} else { // otherwise delete the car and continue through list
					deleteNodeFromList(currentList, car);
					temp = currentList->head;
				} 

			/* A car can turing left may proceed from 1-11 seconds */
			} else if (car->time <= globalTimer && lightTimer < 12 && car->direc2 == 'L') {

				globalTimer = globalTimer + LEFT;
				lightTimer =  lightTimer + LEFT; 

				pastComplete[lightDirection] = globalTimer;
				printf("%c %c %.1lf %30.1lf %30.1lf\n", car->direc1, car->direc2, car->time, arrivalTime, globalTimer);
				/* if last car in list, adds remaining time and goes to the next Light direction */
				if (temp->next == NULL) {
					globalTimer = globalTimer - lightTimer + 14;
					deleteNodeFromList(currentList, car);
					break;
				} else { // otherwise delete the car and continue through list
					deleteNodeFromList(currentList, car);
					temp = currentList->head;
				} 
					
			/* if unable to proceed through intesection this calculates the time it will be able to cross and add it's direction time */
			} else if (lightTimer > 10 && lightTimer < 14 && car->time <= globalTimer) {

					x = 14 - lightTimer; // time left at intersection
					pastComplete[lightDirection] = x + 42 + globalTimer + checkTimeToCross(car->direc2);
					printf("%c %c %.1lf %30.1lf %30.1lf\n", car->direc1, car->direc2, car->time, arrivalTime, pastComplete[lightDirection]);
					if (temp->next == NULL)
					globalTimer = globalTimer - lightTimer + 14; // adds remaining time and goes to the next Light direction 
					deleteNodeFromList(currentList, car);
					break;

			} else {
				lightTimer += 0.5;
				globalTimer += 0.5;
			}
				
		}

		flag = 1;
		lightTimer = 0;
		/* cheange Light Direction */
		++lightDirection;
		
		/* if a full rotation of the intersection is made */
		if (lightDirection == 4)
			lightDirection = 0;

		if (lightDirection == 0) {
			if (N->head != NULL) {
				currentList = N;
			} else {
				++lightDirection;
				currentList = E;
				globalTimer += 14;
			}
		}
		if (lightDirection == 1) {
			if (E->head != NULL) {
				currentList = E;
			} else {
				++lightDirection;
				currentList = S;
				globalTimer += 14;
			}
		}
		if (lightDirection == 2) {
			if (S->head != NULL) {
				currentList = S;
			} else {
				++lightDirection;
				currentList = W;
				globalTimer += 14;
			}
		}
		if (lightDirection == 3) {
			if (W->head != NULL) {
				currentList = W;
			} else {
				lightDirection = 0;
				currentList = N;
				globalTimer += 14;
			}
		}
		 temp = currentList->head; 

	}

}

