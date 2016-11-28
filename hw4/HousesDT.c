//
//  HousesDT.c
//  hw4
//
//  Created by Jason Thai on 5/23/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#include "HousesDT.h"
#include <stdlib.h>
#include <string.h>

//Allocate memory for House Structure
HouseType createHouse() {
    HouseType housePtr = malloc(sizeof(struct house_type));
    return housePtr;
}

//Set House MLS number
void setHouseMls(long int houseMls, HouseType housePtr) {
    housePtr -> mls = houseMls;
}

//Set House address
void setHouseAddress(char houseAddress[], HouseType housePtr) {
    strcpy(housePtr -> address, houseAddress);
}

//Set House city location
void setHouseCity(char houseCity[], HouseType housePtr) {
    strcpy(housePtr -> city, houseCity);
}

//Set houze zip code
void setHouseZip(char houseZip[], HouseType housePtr) {
    strcpy(housePtr -> zip, houseZip);
}

//Set number of beds in house
void setHouseBeds(long int houseBeds, HouseType housePtr) {
    housePtr -> beds = houseBeds;
}

//Sets bathrooms for house
void setHouseBaths(long int houseBaths, HouseType housePtr) {
    housePtr -> bathrooms = houseBaths;
}

//Sets square footage for house
void setHouseSqFt(long int houseSqFt, HouseType housePtr) {
    housePtr -> sqft = houseSqFt;
}

//Set house price
void setHousePrice(long int housePrice, HouseType housePtr) {
    housePtr -> price = housePrice;
}
