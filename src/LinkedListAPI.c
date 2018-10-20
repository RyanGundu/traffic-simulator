/**
 * @file LinkedListAPI.h
 * @author Michael Ellis
 * @date January 2017
 * @brief File containing the function definitions of a doubly linked list
 */
#ifndef _LIST_API_
#define _LIST_API_
#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
#include "../include/LinkedListAPI.h"
#include "../include/car.h"

#include <stdio.h>
#include <stdlib.h>

/**
*Node of a linked list. This list is doubly linked, meaning that it has points to both the node immediately in front 
of it, as well as the node immediately behind it.
**/
typedef struct listNode{
    void *data;
    struct listNode *previous;
    struct listNode *next;
} Node;

/**
 *Dummy head of the list. Contains no actual data on it beyond a pointer to the front and end of the list.
 **/
typedef struct listHead{
    Node *head;
    Node *tail;
    void (*deleteNode)(void *toBeDeleted);
    int (*compare)(const void *first,const void *second);
    void (*printNode)(void *toBePrinted);
} List;

/**Function to point the listhead to the appropriate functions. Allocates memory to the struct.
*@return pointer to the list head
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/
List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)) {
	
	List *linkedList = malloc(sizeof(List));
    linkedList->head = NULL;
    linkedList->tail = NULL;


    linkedList->deleteNode = deleteFunction;
    linkedList->compare = compareFunction;
    linkedList->printNode = printFunction;
    return linkedList;
}

/**Function for creating a node for a linked list. This node contains generic data and may be connected to 
other notes in a list.
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - is a generic pointer to any data type.
**/
Node *initializeNode(void *data) {

    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}

/**Inserts a Node to the front of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertFront(List *list, void *toBeAdded) {

    Node* newNode = initializeNode(toBeAdded);

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return;  
    } 
    newNode->next = list->head;
    list->head->previous = newNode;
    list->head = newNode;
}

/**Inserts a Node to the back of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertBack(List *list, void *toBeAdded) {

     Node *newNode = initializeNode(toBeAdded);

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        
    } else {
        newNode->previous = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }

}
 
/** Uses the comparison function in the List struct to place the element in the appropriate position in the list.
*this is intended to be used from the beginning in order to keep the list completely sorted.
*@pre List exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param list a pointer to the dummy head of the list containing function pointers for delete and compare, as well 
as a pointer to the first and last element of the list.
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertSorted(List *list, void *toBeAdded) {

    int x = 0;
    Node *newNode = initializeNode(toBeAdded);
    
    Node *temp = list->head;
    /* if list empty */
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    }
    /* if only 1 node in list */
    else if (temp->previous == NULL && temp->next == NULL) {
        x = list->compare(temp->data, newNode->data);
        if (x == 1) {
            insertFront(list, newNode->data);
        }
        else if (x == -1){
            insertBack(list, newNode->data);
        }
    } else { 
        temp = list->tail;
        x = list->compare(temp->data, newNode->data);

        if (x == -1) {
            insertBack(list, newNode->data);
        } else {
            while (1) {
                if (x == 1) {
                    temp = temp->previous;
                    x = list->compare(temp->data, newNode->data);
                }
                if (x == -1) {
                    newNode->next = temp->next;
                    temp->next = newNode;
                    newNode->previous = temp;
                    newNode->next->previous = newNode;
                    break;
                } 
                if (temp->previous == NULL) {
                    insertFront(list, newNode->data);
                    break;
                }

            }
       }
    }
}

/**Function to remove a node from the list and alter the pointers accordingly to not disrupt the order of the 
 *data structure. 
 *@pre List must exist and have memory allocated to it
 *@post toBeDeleted will have its memory freed if it exists in the list.
 *@param list pointer to the dummy head of the list containing deleteFunction function pointer
 *@param toBeDeleted pointer to data that is to be removed from the list
 *@return returns EXIT_SUCCESS on success, and EXIT_FAILURE when empty. Returns -1 when the node cannot be found.
 **/
int deleteNodeFromList(List *list, void *toBeDeleted) {

    Node *temp = list->head;

    if (temp == NULL) {
        return EXIT_FAILURE;
    }
    while (temp != NULL) {
            if (list->compare(temp->data, toBeDeleted) == 0) {
                


                 /* deleting the only node in list */
                if (temp->next == NULL && temp->previous == NULL) {
                    list->head = NULL;
                    list->tail = NULL;
                    list->deleteNode(temp->data);
                    free(temp);
                    temp = NULL;
                    return EXIT_SUCCESS;
                }
                /* deleting the last node in a list */
                 else if (temp->next == NULL && temp->previous != NULL) {
                    list->tail = list->tail->previous;
                    list->tail->next = NULL;
                    list->deleteNode(temp->data);
                    free(temp);
                    temp = NULL;
                    return EXIT_SUCCESS;
                }
                /* deleating first node in a list */
                else if (temp->previous == NULL && temp->next != NULL) {
                    list->head = list->head->next;
                    list->head->previous = NULL;
                    list->deleteNode(temp->data);
                    free(temp);
                    temp = NULL;
                    return EXIT_SUCCESS;
                }
                /* deleting a node in the middle of a list */
                else if (temp->previous != NULL && temp->next != NULL) {
                    temp->previous->next = temp->next;
                    temp->next->previous = temp->previous;
                    list->deleteNode(temp->data);
                    free(temp);
                    temp = NULL;
                    return EXIT_SUCCESS;
                }
            }
            temp = temp->next;
    } 

    return -1;
}

/** Deletes the entire linked list head to tail, starting with the nodes, followed by the list itself.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
void deleteList(List *list) {
    Node *temp = list->head;

    while (temp != NULL) {
            deleteNodeFromList(list, temp->data);
            temp = temp->next;
    } 
    free(list);
    list = NULL;
}

/**Function to return the data at the front of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the head of the list
 *@return pointer to the data located at the head of the list
 **/
void *getFromFront(List *list) {
    return list->head->data;
}

/**Function to return the data at the back of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the tail of the list
 *@return pointer to the data located at the tail of the list
 **/
void *getFromBack(List *list) {
    return list->tail->data;
}
/**Function to print list from tail to head. This will utilize the list's printNode function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printBackwards(List *list) {

    Node *temp = list->tail;
    while (temp != NULL) {
            list->printNode(temp->data);
            temp = temp->previous;
    } 
}

/**Function to print list from head to tail. This will utilize the list's printNode function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printForward(List *list) {

    Node *temp = list->head;
    while (temp != NULL) {
            list->printNode(temp->data);
            temp = temp->next;
    } 
}

#endif


