//
//  AddressDT.c
//  hw4
//
//  Created by Jason Thai on 5/18/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#include "AddressDT.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Set client name
void setName(char name[], AddressType addressPtr) {
    strcpy(addressPtr -> name, name);
}

//Set client address
void setAddress(char address[], AddressType addressPtr) {
    strcpy(addressPtr -> address, address);
}

//Set client city and state
void setCityState(char cityState[], AddressType addressPtr) {
    strcpy(addressPtr -> cityState, cityState);
}

//Set client phone number
void setPhone(char phone[], AddressType addressPtr) {
    strcpy(addressPtr -> phone, phone);
}










