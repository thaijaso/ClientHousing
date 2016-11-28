//
//  AddressDT.h
//  hw4
//
//  Created by Jason Thai on 5/18/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#ifndef AddressDT_h
#define AddressDT_h

#include <stdio.h>

struct address_type {
    char name[60];
    char address[30];
    char cityState[30];
    char phone[30];
};


typedef struct address_type *AddressType;
void setName(char name[], AddressType addressPtr);
void setAddress(char address[], AddressType addressPtr);
void setCityState(char cityState[], AddressType addressPtr);
void setPhone(char phone[], AddressType addressPtr);

#endif /* AddressDT_h */
