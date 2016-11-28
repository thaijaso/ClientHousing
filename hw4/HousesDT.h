//
//  HousesDT.h
//  hw4
//
//  Created by Jason Thai on 5/23/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#ifndef HousesDT_h
#define HousesDT_h

#include <stdio.h>

struct house_type {
    long int mls;
    char address[30];
    char city[30];
    char zip[30];
    long int beds;
    long int bathrooms;
    long int sqft;
    long int price;
};

typedef struct house_type *HouseType;
HouseType createHouse();
void setHouseMls(long int mls, HouseType housePtr);
void setHouseAddress(char address[], HouseType housePtr);
void setHouseCity(char city[], HouseType housePtr);
void setHouseZip(char zip[], HouseType housePtr);
void setHouseBeds(long int beds, HouseType housePtr);
void setHouseBaths(long int baths, HouseType housePtr);
void setHouseSqFt(long int sqft, HouseType housePtr);
void setHousePrice(long int price, HouseType housePtr);

#endif /* HousesDT_h */
