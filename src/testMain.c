#include "../include/LinkedListAPI.h"
#include "../include/car.h"
#include "../include/simulation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Test main */

int main (int arg, char *argv[]) {

	/* Note: insertSorted is being used, so the expected output will be placed appropriately the current list */

	List *N = initializeList(&printNode, &deleteListNode, &compare);

	printf("Expected Output: N F 2.70\n");
	Car *a = createCar('N', 'F', 2.7);
	insertSorted(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n");

	printf("Expected Output: z l 0.00\n");
	a = createCar('z', 'l', 0);
	insertSorted(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n");

	/* The rest of the list remains after deleting "z l 0.00"  */
	printf("Expected Output (after deletion): N F 2.70\n");
	deleteNodeFromList(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n");


/*	printf("Expected Output:  falure due to empty input");
	a = createCar('', 'Z', 9);
	insertSorted(N, a);	
	printf("Actual Output\n");
	printForward(N);
	printf("\n"); */

	printf("Expected Output: R 1 10\n");
	a = createCar('R', '1', 10);
	insertSorted(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n");

	printf("Expected Output: 2 7 -9999999.00\n");
	a = createCar('2', '7', -9999999);
	insertSorted(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n");

	printf("Expected Output: # L 0.00\n");
	a = createCar('#', 'L', 00);
	insertSorted(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n");

 /* Generates an error yet runs printing a 0 in place of the empty case */
/*	printf("Expected Output: ff 0 -0.3\n");
	a = createCar('A', '', -0.3);
	insertSorted(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n"); */

	printf("Expected Output: ! ! 1.10\n");
	a = createCar('!', '!', 1.1);
	insertSorted(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n");

	printf("Expected Output: 2 2 2.00\n");
	a = createCar('2', '2', 2);
	insertSorted(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n"); 

	/* Tests printing forward and back */
	printf("List printed forwards:\n");
	printForward(N);
	printf("\n");
	printf("List printed backwards:\n");
	printBackwards(N);
	printf("\n");

	/* Tests insertFront */
	printf("Expected head node after insert front: A A 10.00\n");
	a = createCar('A', 'A', 10);
	insertFront(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n"); 
	/* Tests insertBack */
	printf("Expected tail node after insert back: B B 99\n");
	a = createCar('B', 'B', 99);
	insertBack(N, a);	
	printf("Actual Output:\n");
	printForward(N);
	printf("\n"); 

	deleteList(N);

	return 0;
}


