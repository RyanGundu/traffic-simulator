#include "../include/LinkedListAPI.h"
#include "../include/car.h"
#include "../include/simulation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
*function prompts user for a valid fileName if an invalid one is given 
*/
FILE* myOpenforReading (char fileName[]) {
	FILE* fileptr; 
	char newFile[50];
	fileptr = fopen(fileName, "r");
	if (fileptr == NULL) {
      	printf("Could not open file %s.\n",fileName);
      	printf("Please enter a new file name:\n");
      	scanf("%s",newFile);
      	fileptr = myOpenforReading(newFile);
      return fileptr; 
   }
   return fileptr;
}

int main (int arg, char *argv[]) {


	FILE *fptr = NULL;
	fptr = myOpenforReading( argv[1] );
	char *text = malloc(sizeof(char) * 10);
	char direc1 = '\0';
	char direc2 = '\0';
	double time = 0;

	int numCars = 0;

	List *N = initializeList(&printNode, &deleteListNode, &compare);
	List *E = initializeList(&printNode, &deleteListNode, &compare);
	List *S = initializeList(&printNode, &deleteListNode, &compare);
	List *W = initializeList(&printNode, &deleteListNode, &compare); 
	
	/* Reads from the file line by line */
	while ( fgets ( text, 10, fptr ) ) {

		sscanf(text, "%c %c %lf",&direc1, &direc2, &time);
		Car *a = createCar(direc1, direc2, time);
		if (direc1 == 'N') {
			insertSorted(N, a);	
			++numCars;
		}
		else if (direc1 == 'E') {
			insertSorted(E, a);
			++numCars;
		}
		else if (direc1 == 'S') {
			insertSorted(S, a);
			++numCars;
		}
		else if (direc1 == 'W') {
			insertSorted(W, a);
			++numCars;

		}

	} 

	if (numCars != 0) {
		simulation(N,E,S,W);
	} else {
		printf("No data\n");
	}
	deleteList(N);
	deleteList(E);
	deleteList(S);
	deleteList(W);

	fclose(fptr);

	return 0;
}


