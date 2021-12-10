#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define TEMP "temp.txt"
#define MAX 256

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
List LList[MAX];
List * front; 
List * rear; 
int triedLandCount = 0; // Tried Landing Count. If this value reaches 2. 
FILE *fptr; // File pointer for input.txt .. The file will be used in many lines and methods.
char str[MAX];

int IsEmpty() { // Return 1 if it is empty.
    if(front->next == rear) 
        return 1;
    else 
        return 0;
}

int size(List * n) {
    int count = 0;
    
    return count;
}

void addQ(int d, int p) { // n is the end link pointer of the linked list.
    List * new;
    new = malloc(sizeof(List));
    new->data = d;
    new->priority = p;

    
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

struct LinkedList * frontQ(List * n) {
    List * temp = n;
    return n;
}

struct LinkedList * backQ(List * n) {
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

void readTheFileYouFkcIdiotC() {
    if((fptr=fopen(INPUT,"r")) == NULL) {
        printf("Dosya Acilamadi.\n");
    }
    else {
        /*for (int i = 0; i < 24; i++)
        {
            fgets(str,MAX,fptr);
            fscanf(,"%d %d %d",str);
        }*/
        for (int i = 0; i < 40; i++)
        {
            fgets(str,MAX,fptr);
            printf("%s",str);
        }
        
    }
    fclose(fptr);
}

int main() {
    // Create the first and the last element of the linked list.
    front = malloc(sizeof(List));
    rear = malloc(sizeof(List));
    front->next = rear;
    // Program Started.
    readTheFileYouFkcIdiotC();
}