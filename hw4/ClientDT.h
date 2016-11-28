//
//  ClientDT.h
//  hw4
//
//  Created by Jason Thai on 5/22/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#ifndef ClientDT_h
#define ClientDT_h

#include <stdio.h>
#include "AddressDT.h"
#include "PreferencesDT.h"

struct client_type {
    char id[10];
    struct address_type address;
    struct preferences_type preferences;
};

typedef struct client_type *ClientType;
ClientType createClient(char id[]);
void destroyClient(ClientType);

#endif /* ClientDT_h */
