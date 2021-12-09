#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define INPUT "input.txt"
#define OUTPUT "output.txt"

struct PlaneClass {
    int priorityId;
    int planeId;
    int reqLandTime; // Requested Landing Time
    int LandTime;
    int delayTime;
    int takeOffTime;
};

struct LinkedList {
    int data;
    int priority;
    struct LinkedList *next;
};

typedef struct PlaneClass Plane;
typedef struct LinkedList List;

// GLOBAL VARIABLES
int triedLandCount = 0; // Tried Landing Count. If this value reaches 2. 
FILE *fptr; // File pointer for input.txt .. The file will be used in many lines and methods.

int Empty(List * n) { // n is the front of the linked list.
    if(n->next == NULL && n->data == -1) {
        return 0;
    }
    else {
        return 1;
    }
}

int size(List * n) {
    int count = 0;
    List * temp = n;
    while(temp->next != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

struct LinkedList * addQ(List * n, int d) { // n is the end link pointer of the linked list.
    List * new;
    new = malloc(sizeof(List));
    new->data = d;
    // replace end pointer list and new pointer list
    int tempdata = n->data;
    return new;
}

struct LinkedList * pollQ(List * n) { // n is the front of the linked list.
    List * second;
    second = n->next;
    n->data = second->data;
    n->next = second->next;
    return n;
}

struct LinkedList * peekQ(List * n) { // n is the front of the linked list.
    List * new;
    return new;
}

struct LinkedList * clearQ() { // n is the front of the linked list.
    List * n;
    n = malloc(sizeof(List));
    n->data = -1;
    n->next = NULL;
    return n;
}

struct LinkedList * removeQ(List * n, int d) {
    List * temp;
    temp = malloc(sizeof(List));
    temp = n;
    // serach the first element of the linked list.
    if(temp->data == d) {
        // delete it.
        temp->next = temp->next->next;
    }
    while(temp->next != NULL) {
        if(temp->next->data == d) {
            // Delete it.
            temp->next = temp->next->next;
        }
        else {
            // continue for searching
            temp = temp->next;
        }
    }
    return temp;
}

struct LinkedList * front(List * n) {
    List * temp = n;
    return n;
}

struct LinkedList * back(List * n) {
    List * temp = n;
    // there is a if statement for if the linked list has one element.
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

void printAllQueue(List * n) { // n is the front of the linked list.
    List * ptr = n;
    int i = 0;
    while(ptr != NULL) {
        printf("%d %d \t",i,ptr->data);
        i++;
        ptr = ptr->next;
    }
}


void importFile() {
    if((fptr = fopen(INPUT,"r")) == NULL) {
        printf("File could not be opened.\n");
        exit(1);
    }
    
    
    


    fclose(fptr);
}

int main() {
    // Create the first and the last element of the linked list.
    List * front; List * rear; 
    front = malloc(sizeof(List));
    rear = malloc(sizeof(List));
    rear->data = -1;
    front->data = -1; // if the data value is still same end of the program, is empty.

    List * second;
    List * third;
    second = malloc(sizeof(List));
    third = malloc(sizeof(List));

    front->next = second;
    second->next = third;
    front->data = 1;
    second->data = 2;
    third->data =3;

    /*printf("%d %d\n",front->data, front->next->data);
    front = dequeue(front);
    printf("%d %d\n",front->data, front->next->data);*/
    front = removeQ(front,2);
}