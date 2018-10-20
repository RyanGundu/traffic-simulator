#ifndef CAR
#define CAR

/**
*The struct or data that each node in a list contains
a light direction (N, E, S, W) a general direction (L, F, R) and a time
**/
typedef struct car {
	char direc1;
	char direc2;
	double time;
} Car;

/**
*Creates a car containing the data
*@param Cars light direction (char)
*@param Cars direction at intersection (char)
*@param Cars time to reach intersection (double)
**/
Car *createCar (char direc1, char direc2, double time);

/**
 *User-defined comparison for two pointers to generic data. Must define an element of these pointers to use to compare
 *the two pointers with each other.
 *@pre first and second must be comparable.
 *@param first pointer to data to be compared with second.
 *@param second pointer to data to be compared with first.
 *@return for sorting purposes,
 *<0 The element pointed by 'first' goes before the element pointed by 'second'
 *0  The element pointed by 'first' is equivalent to the element pointed by 'second'
 *>0 The element pointed by 'first' goes after the element pointed by 'second'
 **/
int compare(const void *first,const void *second);

/**User defined function to print an element of the list.
 *@pre Data must be able to be printed via a standard print function
 *@param toBePrinted pointer to the data that is to be printed. Taken from a data structure.
 **/
void printNode(void *data);

/**User defined function to delete linked list node based on the incoming data.
 *@pre Data must not already be freed or NULL
 *@param toBeDeleted Pointer to generic data to be deleted in the list.
 **/
void deleteListNode(void *toBeDeleted);

#endif




