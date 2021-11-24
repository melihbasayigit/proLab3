#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct PlaneClass {
    int priorityId;
    int planeId;
    int reqBoardTime; // Requested Boarding Time
};

typedef struct PlaneClass Plane;

// GLOBAL VARIABLES
int triedBoardCount = 0; // Tried Boarding Count. If this value reaches 2. 


int main() {
    Plane airbus;
    triedBoardCount++;
    printf("%d",triedBoardCount);
}