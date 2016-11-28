//
//  ClientDT.c
//  hw4
//
//  Created by Jason Thai on 5/22/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#include "ClientDT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Set the client ID
ClientType createClient(char id[]) {
    
    ClientType clientPtr = calloc(1, sizeof(struct client_type));
    strncpy(clientPtr -> id, id, strlen(id) - 2);
    return clientPtr;
}

//Deallocate memory for client
void destroyClient(ClientType client) {
    free(client);
    client = NULL;
}

