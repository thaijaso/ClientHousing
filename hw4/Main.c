//
//  Main.c
//  hw4
//
//  Created by Jason Thai on 5/20/16.
//  Copyright © 2016 Jason Thai. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ArrayList.h"
#include "ClientDT.h"
#include "AddressDT.h"
#include "PreferencesDT.h"
#include "HousesDT.h"

void promptUser(void);
int compare(int *, int *);
void printClient(void *);
void printHouse(void *);
void clearId(char *);
void clearName(char *);
void clearAddress(char *);
void clearCityState(char *);
void clearPhone(char *);
void createClientsView(ListType, ListType);
void createHouseView(ListType, ListType);
int houseMeetsPref(ClientType, HouseType);

//Process 3 text files on clients and houses, looks for matches,
//and produces  2 output files of houses that match a client's preferences
int main(void) {
    FILE *clientsf = fopen("clients.txt", "r");
    FILE *preferf = fopen("preferences.txt", "r");
    FILE *housesf = fopen("houses.csv", "r");
    
    char line[200];     //read in from text file line by line
    char id[10];
    char name[60];
    char address[30];
    char cityState[30];
    char phone[30];
    int counter = 0;    //counter tells us what field to populate for each client
    int index;          //Used to grab clients from clientsArr

    //populates variables with null characters
    memset(line, 0, 200);
    clearId(id);
    clearName(name);
    clearAddress(address);
    clearCityState(cityState);
    clearPhone(phone);

    //Used to store the clients and houses structs
    ListType clientsArr, housesArr;
    clientsArr = create(sizeof(struct client_type), compare);
    housesArr = create(sizeof(struct house_type), compare);
    
    
    while (fgets(line, 200, clientsf) != NULL) {    //parse text file line by line
        
        if (counter == 0) {
            strcpy(id, line);   //copy id from line
            counter++;
        } else if (counter == 1 ) {
            strncpy(name, line, strlen(line) - 2);  //copy name, leave out carriage return and new line
            counter++;
        } else if (counter == 2) {
            strncpy(address, line, strlen(line) - 2);   //copy address, leave out carriage return and new line
            counter++;
        } else if (counter == 3) {
            strncpy(cityState, line, strlen(line) - 2);     //copy city and state, leave our carriage and new line
            counter++;
        } else if (counter == 4) {
            strncpy(phone, line, 12);   //copy phone, grab 12 characters since that is how many charagers in a phone number, e.g. 111-111-1111
            counter++;
        } else {
            ClientType client = createClient(id);   //creates a client struct with an ID
            
            //Sets the Client's address struct field, passing in a reference to the Client
            setName(name, &(client -> address));
            setAddress(address, &(client -> address));
            setCityState(cityState, &(client -> address));
            setPhone(phone, &(client -> address));
            
            push(clientsArr, client);   //add client to client array list
            destroyClient(client);      //remove client from heap
            
            //sets variables to null terminator so that we can use it for the next client
            clearId(id);
            clearName(name);
            clearAddress(address);
            clearCityState(cityState);
            clearPhone(phone);
            
            strcpy(id, line);
            counter = 1;
        }
    }
    
    //since file reader stops when there is no new line,  create client struct for last client
    ClientType lastClient = createClient(id);
    
    setName(name, &(lastClient -> address));
    setAddress(address, &(lastClient -> address));
    setCityState(cityState, &(lastClient -> address));
    setPhone(phone, &(lastClient -> address));
    
    push(clientsArr, lastClient);
    destroyClient(lastClient);
    
    //Populate clients with preferences information
    for (index = 0; index < size_is(clientsArr); index++) {
        int found = 0;
        counter = 0;
        ClientType client = (ClientType) get(clientsArr, index);
        char targetId[10];  //Use the client ID to find the corresponding ID in the preferences.txt file
        strcpy(targetId, client -> id);
        
        while(fgets(line, 200, preferf) != NULL) {  //parse preferences.txt file line by line
            char searchId[10];  //The ID in the preferences.txt file
            
            if (counter == 0) {
                
                /**************** THIS IS THE ERROR *************************************/
                strncpy(searchId, line, strlen(line) - 2);
                printf("%s\n", searchId);
                /**************** THIS IS THE ERROR *************************************/
                
                
                if (strcmp(targetId, searchId) == 0) {
                    found = 1;  //if the ID from the clients struct matches the ID from the preferences.txt file, set found = 1
                }
                
                counter++;
            } else {
                
                if (found == 1) {   //if the ID's match, grab the second line from the text file and parse the string for digits
                    long int minBeds;
                    long int minBaths;
                    long int minSqFt;
                    long int maxPrice;
                    
                    sscanf(line, "%ld %ld %ld %ld", &minBeds, &minBaths, &minSqFt, &maxPrice);
                    
                    setMinBeds(minBeds, &(client -> preferences));
                    setMinBaths(minBaths, &(client -> preferences));
                    setMinSqFt(minSqFt, &(client -> preferences));
                    setMaxPrice(maxPrice, &(client -> preferences));
                    
                    break;
                }
                
                counter = 0;
            }
        }
        
        preferf = fopen("preferences.txt", "r");    //We have to reread the text file looking for the ID of the next client in the list
        
    }
    
    counter = 0;
    
    //Parse the houses.txt file
    while(fgets(line, 200, housesf) != NULL) {
        
        
        if (counter != 0) {
            long int houseMls;
            char houseAddress[30];
            char houseCity[30];
            char houseZip[30];
            long int houseBeds;
            long int houseBaths;
            long int houseSqFt;
            long int housePrice;
            
            sscanf(line, "%ld, %[^,], %[^,], %[^,], %ld, %ld, %ld, %ld", &houseMls, &houseAddress, &houseCity, &houseZip, &houseBeds, &houseBaths, &houseSqFt, &housePrice);
        
            HouseType house = createHouse();
            
            setHouseMls(houseMls, house);
            setHouseAddress(houseAddress, house);
            setHouseCity(houseCity, house);
            setHouseZip(houseZip, house);
            setHouseBeds(houseBeds, house);
            setHouseBaths(houseBaths, house);
            setHouseSqFt(houseSqFt, house);
            setHousePrice(housePrice, house);
            
            push(housesArr, house);
            free(house);
        }
        
        counter++;
    }
    
    //printl(clientsArr, printClient);
    //printl(housesArr, printHouse);
    
    //Creates output file for matches
    createClientsView(clientsArr, housesArr);
    createHouseView(clientsArr, housesArr);
    
    /********** Ask user to search for client by name *******/
//    char clientNameSearch[60];
//    memset(clientNameSearch, 0, 60);
//    
//    printf("%s", "Enter client name to display: ");
//    scanf(" %[^\n]s", &clientNameSearch);
//    
//    int found = -1;
//    
//    for (index = 0; index < size_is(clientsArr); index++) {
//        ClientType client = (ClientType) get(clientsArr, index);
//        
//        if (strcmp(clientNameSearch, client -> address.name) == 0) {
//            printClient(client);
//            found = 1;
//        }
//    }
//    
//    if (found == -1) {
//        printf("%s\n", "Client not found.");
//    }
    
    
    /***************** EXTRA CREDIT ATTEMPT *******************/
    
    
    destroy(clientsArr);
    destroy(housesArr);
    fclose(clientsf);
    fclose(preferf);
    fclose(housesf);
}

void promptUser() {
    
}

//Print client information, to be passed to arraylist printl method
void printClient(void* p) {
    ClientType client = ((ClientType) p);
    printf("%s\n", ((ClientType) p) -> id);
    printf("%s\n", ((ClientType) p) -> address.name);
    printf("%s\n", ((ClientType) p) -> address.address);
    printf("%s\n", ((ClientType) p) -> address.cityState);
    printf("%s\n", ((ClientType) p) -> address.phone);
    printf("%ld\n", ((ClientType) p) -> preferences.minBed);
    printf("%ld\n", ((ClientType) p) -> preferences.minBath);
    printf("%ld\n", ((ClientType) p) -> preferences.minSqFt);
    printf("%ld\n", ((ClientType) p) -> preferences.maxPrice);
    printf("\n");
}

//Prints house infomation, to be passed to arraylist printl method
void printHouse(void *p) {
    HouseType house = ((HouseType) p);
}

//Comparator for arraylist function, not used in program currently
int compare(int *a, int *b) {
    short int toReturn = 0;
    if (*a < *b)
        toReturn = -1;
    else if (*a > *b)
        toReturn = 1;
    return toReturn;
}

//Clears ID
void clearId(char *id) {
    int index;
    
    for (index = 0; index < 10; index++) {
        id[index] = '\0';
    }
}

//Clears Name
void clearName(char *name) {
    int index;
    
    for (index = 0; index < 60; index++) {
        name[index] = '\0';
    }
}

//Clear Address
void clearAddress(char *address) {
    int index;
    
    for (index = 0; index < 30; index++) {
        address[index] = '\0';
    }
}

//Clear city state
void clearCityState(char *cityState) {
    int index;
    
    for (index = 0; index < 30; index++) {
        cityState[index] = '\0';
    }
}

//Clear phone number
void clearPhone(char *phone) {
    int index = 0;
    
    for(index = 0; index < 30; index++) {
        phone[index] = '\0';
    }
}

//Create clientsView.txt file
void createClientsView(ListType clientsArr, ListType housesArr) {
    FILE *clientsView = fopen("clientsView.csv", "w");
    fprintf(clientsView, "%s\n", "Client ID,Name,Phone Number,,,MLS,Street Address,City,Zip,Bedroom,Bathroom,Sq Footage,Price");
    int numOfMatches = 0;
    int uniqueClient = 0;   //used to print a client info once
    ListType matches = create(sizeof(struct house_type), compare);
    int clindex, hindex;    //client index, house index
    
    for (clindex = 0; clindex < size_is(clientsArr); clindex++) {
        ClientType client = (ClientType) get(clientsArr, clindex);
        
        for (hindex = 0; hindex < size_is(housesArr); hindex++) {
            HouseType house = (HouseType) get(housesArr, hindex);
            
            if (houseMeetsPref(client, house) == 0) {
                char clientId[10];
                char clientName[60];
                char clientPhone[30];
                
                strcpy(clientId, client -> id);
                strcpy(clientName, client -> address.name);
                strcpy(clientPhone, client -> address.phone);
                
                long int houseMls = house -> mls;
                char houseAddress[30];
                char houseCity[30];
                char houseZip[30];
                
                strcpy(houseAddress, house -> address);
                strcpy(houseCity, house -> city);
                strcpy(houseZip, house -> zip);
                
                long int houseBeds = house -> beds;
                long int houseBaths = house -> bathrooms;
                long int houseSqFt = house -> sqft;
                long int housePrice = house -> price;
                
                if (uniqueClient == 0) {
                    fprintf(clientsView, "%s", clientId);
                    fprintf(clientsView, "%s", ",");
                    fprintf(clientsView, "%s", clientName);
                    fprintf(clientsView, "%s", ",");
                    fprintf(clientsView, "%s", clientPhone);
                } else {
                    fprintf(clientsView, "%s", ",,");
                }
                
                fprintf(clientsView, "%s", ",,,");
                fprintf(clientsView, "%ld", houseMls);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%s", houseAddress);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%s", houseCity);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%s", houseZip);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%ld", houseBeds);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%ld", houseBaths);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%ld", houseSqFt);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%ld", housePrice);
                fprintf(clientsView, "%c", '\n');
                numOfMatches++;
                uniqueClient = -1;
            }
        }
        uniqueClient = 0;
    }
    
    if (numOfMatches == 0) {
        fprintf(clientsView, "%s", "No matches found.");
    }
    
    destroy(matches);
    fclose(clientsView);
}

//Create houseView.csv file
void createHouseView(ListType clientsArr, ListType housesArr) {
    FILE *houseView = fopen("houseView.csv", "w");
    fprintf(houseView, "%s\n", "MLS,Street Address,City,Zip,Bedroom,Bathroom,Sq Footage,Price,,Client ID,Name,Phone Number");
    int numOfMatches = 0;
    int uniqueHouse = 0;
    ListType matches = create(sizeof(struct house_type), compare);
    int hindex, clindex;    //house index, client index
    
    for (hindex = 0; hindex < size_is(housesArr); hindex++) {
        HouseType house = (HouseType) get(housesArr, hindex);
        long int houseMls = house -> mls;
        char houseAddress[30];
        char houseCity[30];
        char houseZip[30];
        strcpy(houseAddress, house -> address);
        strcpy(houseCity, house -> city);
        strcpy(houseZip, house -> zip);
        long int houseBeds = house -> beds;
        long int houseBaths = house -> bathrooms;
        long int houseSqFt = house -> sqft;
        long int housePrice = house -> price;
        
        for (clindex = 0; clindex < size_is(clientsArr); clindex++) {
            ClientType client = (ClientType) get(clientsArr, clindex);
            char clientId[10];
            char clientName[60];
            char clientPhone[30];
            strcpy(clientId, client -> id);
            strcpy(clientName, client -> address.name);
            strcpy(clientPhone, client -> address.phone);
            
            if (houseMeetsPref(client, house) == 0) {
                
                if (uniqueHouse == 0) {
                    fprintf(houseView, "%ld", houseMls);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%s", houseAddress);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%s", houseCity);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%s", houseZip);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%ld", houseBeds);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%ld",houseBaths);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%ld", houseSqFt);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%ld", housePrice);
                } else {
                    fprintf(houseView, "%s", ",,,,,,,");
                }
               
                fprintf(houseView, "%s", ",,");
                fprintf(houseView, "%s", clientId);
                fprintf(houseView, "%s", ",");
                fprintf(houseView, "%s", clientName);
                fprintf(houseView, "%s", ",");
                fprintf(houseView, "%s", clientPhone);
                fprintf(houseView, "%s", "\n");
                numOfMatches++;
                uniqueHouse = -1;
            }
        }
        uniqueHouse = 0;
    }
    
    if (numOfMatches == 0) {
        fprintf(houseView, "%s", "No matches found.");
    }
    
    destroy(matches);
    fclose(houseView);
}

//Returns 0 if house match for Client is found, -1 otherwise
int houseMeetsPref(ClientType client, HouseType house) {
    int doesMatch = 0;
    
    char clientId[10];
    strcpy(clientId, client -> id);
    long int clientMinBeds = client -> preferences.minBed;
    long int clientMinBaths = client -> preferences.minBath;
    long int clientMinSqFt = client -> preferences.minSqFt;
    long int clientMaxPrice = client -> preferences.maxPrice;
    
    long int houseBeds = house -> beds;
    long int houseBaths = house -> bathrooms;
    long int houseSqFt = house -> sqft;
    long int housePrice = house -> price;
    
    if (houseBeds < clientMinBeds) {
        doesMatch = -1;
    }
    
    if (houseBaths < clientMinBaths) {
        doesMatch = -1;
    }
    
    if (houseSqFt < clientMinSqFt) {
        doesMatch = -1;
    }
    
    if (housePrice > clientMaxPrice) {
        doesMatch = -1;
    }
    
    return doesMatch;
}








