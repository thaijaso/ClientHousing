//
//  ArrayList.c
//  hw4
//
//  Created by Jason Thai on 5/18/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#include "ArrayList.h"
#include "ClientDT.h"
#include "AddressDT.h"
#include "HousesDT.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct list_type {
    void *data;
    int size;
    int capacity;
    int elementSize;
    int (*comparePtr) (void *d1, void *d2);
};


// returns the pointer to the list; NULL if list not created
ListType create(int elSize, int (*comp) (void *item1, void * item2)) {
    // allocate memory for a structure variable containing all
    // list components
    ListType listptr = malloc(sizeof(struct list_type));
    // if allocation was succesfull
    if (listptr != NULL) {
        listptr->size = 0;
        listptr->capacity = 10;
        listptr->elementSize = elSize;
        listptr->comparePtr = comp;
        // allocate memory for the actual array
        listptr->data = malloc(10*(listptr->elementSize));
        // if array not created, deallocate the list too
        if (listptr->data == NULL) {
            free(listptr);
            listptr = NULL;
        }
    }
    
    return listptr;
}

void destroy(ListType listptr) {
    free(listptr->data);
    free(listptr);
    listptr = NULL;
}

int size_is(ListType listptr) {
    return listptr->size;
}

int is_empty(ListType listptr) {
    return listptr->size == 0;
}

void make_empty(ListType listptr) {
    // if list is larger than 200 elements, create a smaller one
    if (listptr->capacity > 200)
        listptr->data = realloc(listptr->data, listptr->elementSize * 100);
    
    listptr->size = 0;
    listptr->capacity = 100;
}


// adds a component to the array, if enough memory available
void push(ListType listptr, void *item) {
    if (listptr->size >= listptr->capacity) {
        void *temp = realloc(listptr->data, listptr->elementSize * (listptr->capacity + 100));
        if (temp != NULL) {
            listptr->capacity += 100;
            listptr->data = temp;
            // copy the element, since we cannot use data[i], we need to copy the data using memcpy
            memcpy(listptr->data + (listptr->size) * (listptr->elementSize), item, listptr->elementSize);
            
            listptr->size++;
        }
    }
    else {
        memcpy(listptr->data + (listptr->size) * (listptr->elementSize), item, listptr->elementSize);
        //ClientType c = (ClientType) (listptr->data + (listptr->size) * (listptr->elementSize));
        listptr->size++;
    }
}

void delete(ListType listptr, void *item) {
//    int i;
//    
//    for (i = 0; i < listptr -> size; i++) {
//        if (listptr -> data[i] == *item) {
//            listptr -> data[i] = listptr -> data[listptr -> size - 1];
//            //listptr -> data[listptr -> size - 1] = NULL;
//            (listptr -> size)--;
//            break;
//        }
//    }
}

//Returns 1 if the arraylist is full, otherwise 0
int is_full(ListType listptr) {
    if (listptr->size < listptr->capacity)
        return 0;
    
    else {
        void * temp = malloc(listptr->elementSize* (listptr->capacity + 100));
        if (temp != NULL) {
            free(temp);
            return 0; 
        }
        return 1;
    }
}

//Print contents of array list
void printl(ListType listptr, void (*printItem) (void *d)) {
    int i;
    for(i = 0; i < listptr->size; i++) {
        // since we cannot use data[i], we need to calculate the address
        // of the element to be sent to the client's print function
        // since data is of type void, the formula is:
        // the beginning address of the array + (offset x element size)
        printItem(listptr->data + i * (listptr->elementSize));
        //printf(" ");
    }
    //printf("\n");
}

//Gets an element from the list
void *get(ListType listptr, int index) {
    //printf("HEAD: %p, index: %d, offest: %x, legit loc: %p\n", listptr->data, index, index * (listptr->elementSize),listptr->data +index * (listptr->elementSize) );
    return (listptr->data + index * (listptr->elementSize));
   
}

