//
//  ArrayList.h
//  hw4
//
//  Created by Jason Thai on 5/18/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#ifndef ArrayList_h
#define ArrayList_h

#include <stdio.h>
#include "ClientDT.h"
#include "HousesDT.h"

typedef struct list_type *ListType;

ListType create(int elSize, int (*compare) (void *item1, void *item2));
void destroy(ListType listP);
void make_empty(ListType listP);
int is_empty(ListType listP);
int is_full(ListType listP);
int size_is(ListType listP);
void push(ListType listP, void *item);
void delete(ListType listP, void* item);
void printl(ListType listP, void (*printItem) (void *item));
void *get(ListType listP, int index);

#endif /* ArrayList_h */
