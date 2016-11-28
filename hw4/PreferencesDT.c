//
//  PreferencesDT.c
//  hw4
//
//  Created by Jason Thai on 5/23/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#include "PreferencesDT.h"
#include <stdlib.h>
#include <string.h>

//Sets the minimum number of bed rooms a Client prefers
void setMinBeds(long int minBed, PreferencesType preferencesPtr) {
    preferencesPtr -> minBed = minBed;
}

//Sets the minimum number of bath rooms a Client prefers
void setMinBaths(long int minBaths, PreferencesType preferencesPtr) {
    preferencesPtr -> minBath = minBaths;
}

//Sets the minimum square footage a Client prefers
void setMinSqFt(long int minSqFt, PreferencesType preferencesPtr) {
    preferencesPtr -> minSqFt = minSqFt;
}

//Sets the maximum price a Client wants to pay
void setMaxPrice(long int maxPrice, PreferencesType preferencesPtr) {
    preferencesPtr -> maxPrice = maxPrice;
}
