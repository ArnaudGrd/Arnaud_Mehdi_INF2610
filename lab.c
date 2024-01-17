/* INF2610 - TP1
/ Matricule 1 : 2241426
/ Matricule 2 : 2188585
*/
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Constantes des avions
const int NUMBER_OF_WHEELS = 7;
const int NUMBER_OF_WINGS = 2;
const int NUMBER_OF_FRONT_WHEELS = 3;
const int FIGURES_IN_WING_ID = 9;

struct Wing
{
    int *id; // un tableau d’entiers
};

struct Wheel
{
    int id;           // un entier
    bool isRearWheel; // un booléen
};

struct Plane
{
    char *id;             // un tableau de caractères
    char planeType[10];   // une chaîne de caractères de dimension 10
    bool isAvailable;     // un booléen
    struct Wheel *wheels; // un tableau de type struct Wheel
    struct Wing *wings;   // un tableau de type struct Wing
};

// Creation de nos 7 roues pour l'avion
struct Wheel *createWheels(int id)
{
    struct Wheel *currentWheel = (struct Wheel *)malloc(sizeof(struct Wheel) * NUMBER_OF_WHEELS);

    for (int iterPtr = 0; iterPtr < NUMBER_OF_WHEELS; iterPtr++)
    {
        currentWheel[iterPtr].id = id;
        currentWheel[iterPtr].isRearWheel = (iterPtr < NUMBER_OF_FRONT_WHEELS) ? false : true;
        id++;
    };

    return currentWheel;
};

void populateWingAttributes(struct Wing *wing, int id)
{

    wing->id = (int *)malloc(sizeof(int) * FIGURES_IN_WING_ID);

    for (int iterPtr = FIGURES_IN_WING_ID - 1; iterPtr >= 0; iterPtr--)
    {
        wing->id[iterPtr] = id % 10;
        id = id / 10;
    };
};

struct Wing *createWings(struct Wing *wing, long longId)
{
    struct Wing *currentWing = (struct Wing *)malloc(sizeof(struct Wing) * NUMBER_OF_WINGS);

    for (int iterPtr = 0; iterPtr < NUMBER_OF_WINGS; iterPtr++)
    {
        populateWingAttributes(&currentWing[iterPtr], longId);
        longId++;
    };

    return currentWing;
};

void createPlanes(struct Plane *plane, char *id, int numberOfPlanes)
{
    for (int iterPtr = 0; iterPtr < numberOfPlanes; iterPtr++)
    {
        plane[iterPtr].id = id;
        plane[iterPtr].isAvailable = true;
        plane[iterPtr].wheels = createWheels(atoi(id));
        plane[iterPtr].wings = createWings(plane[iterPtr].wings, atoll(id));
        id++;
    };
};

void setAvailability(struct Plane plane, bool isAvailable)
{
    plane.isAvailable = isAvailable;
};

char *getAvailablePlanes(struct Plane *planes, int numberOfPlanes)
{
    char *availablePlanes = (char *)malloc(sizeof(char) * numberOfPlanes);
    int iterPtr = 0;
    int iterPtr2 = 0;

    while (iterPtr < numberOfPlanes)
    {
        if (planes[iterPtr].isAvailable)
        {
            availablePlanes[iterPtr2] = *planes[iterPtr].id;
            iterPtr2++;
        };
        iterPtr++;
    };

    return availablePlanes;
};

void setPlaneType(struct Plane *plane)
{
    int idOfFirstWing = plane->wings[0].id[0];

    if (idOfFirstWing >= 1 && idOfFirstWing <= 2)
    {
        strcpy(plane->planeType, "Small");
    }
    else if (idOfFirstWing >= 3 && idOfFirstWing <= 6)
    {
        strcpy(plane->planeType, "Medium");
    }
    else if (idOfFirstWing >= 7 && idOfFirstWing <= 8)
    {
        strcpy(plane->planeType, "Large");
    }
}

char *getPlanesByType(struct Plane *planes, char *planeType, int numberOfPlanes)
{
    char *planesByType = (char *)malloc(sizeof(char) * numberOfPlanes);
    int iterPtr = 0;
    int iterPtr2 = 0;

    while (iterPtr < numberOfPlanes)
    {
        if (strcmp(planes[iterPtr].planeType, planeType) == 0)
        {
            planesByType[iterPtr2] = *planes[iterPtr].id;
            iterPtr2++;
        };
        iterPtr++;
    };

    return planesByType;
};

int main(int argc, char **argv)
{
    printf("Hello\n");
    /* Remove comment once the code is completed for the given section to test */

    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */

    /*Test createWheels*/
    int id = 1635;
    struct Wheel *wheels;
    wheels = createWheels(id);
    int i = 0;

    while (i < 7)
    {
        printf("%d\n", wheels[i].id);
        printf("%s\n", wheels[i].isRearWheel ? "true" : "false");
        i++;
    };

    /* Create wing - [4 points] */

    /*Test populateWingAttributes*/
    int idWing = 315131687;
    struct Wing wing;
    populateWingAttributes(&wing, idWing);
    int i2 = 0;
    while (i2 < 9)
    {
        printf("%s %d\n", "Position", 9 - i);
        printf("%d\n", wing.id[i]);
        i2++;
    }

    
    long longId = 1;
    struct Wing* wings = NULL;
    wings = createWings(wings, longId);
    

    /* Create plane - [4 points] */
    
    int numberOfPlanes = 3;
    struct Plane* planes = malloc(sizeof(struct Plane) * numberOfPlanes);
    createPlanes(planes, "101", 3);

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    struct Plane plane = planes[0];
    setAvailability(plane, true);
    

    /* Get available planes - [1 point] */
    
    getAvailablePlanes(planes, numberOfPlanes);
    

    /* Classify planes - [2 points] */
    // Renamed to prevent conflict with the first plane
    struct Plane plane1 = planes[1];
    setPlaneType(&plane1);
    

    /* Return type specific planes - [2 points] */
    
    char planeType[] = "Small";
    getPlanesByType(planes, planeType,numberOfPlanes);
    
}
