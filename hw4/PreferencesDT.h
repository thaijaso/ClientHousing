//
//  PreferencesDT.h
//  hw4
//
//  Created by Jason Thai on 5/23/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#ifndef PreferencesDT_h
#define PreferencesDT_h

#include <stdio.h>

struct preferences_type {
    long int minBed;
    long int minBath;
    long int minSqFt;
    long int maxPrice;
};

typedef struct preferences_type *PreferencesType;
void setMinBeds(long int minBeds, PreferencesType preferencesPtr);
void setMinBaths(long int minBaths, PreferencesType preferencesPtr);
void setMinSqFt(long int minSqFt, PreferencesType preferencesPtr);
void setMaxPrice(long int maxPrice, PreferencesType preferencesPtr);

#endif /* PreferencesDT_h */
