#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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
    int triedLandCount; // Tried Landing Count. If this value reaches 3 land immediatly or go to the other airport.
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
bool IsDayCompleted = false; 
FILE *fptr; // File pointer for input.txt .. The file will be used in many lines and methods.
int Time = 1;
char str[MAX];
// GLOBAL VALUE FOR READ TO FILE FUNCTION
Plane planes[28];

bool IsEmpty() { // Return true if it is empty.
    if(front->next == rear) 
        return true;
    else 
        return false;
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

void timeUp() {
    Time++;
    if(Time == 25) {
        Time = 0;
        IsDayCompleted = true;
    }
}

int sizeInput(FILE * ptr) { // Return size of planes in the input file.
    if((ptr = fopen(INPUT,"r")) == NULL) {
        printf("Dosya acilamadi\n");
    }
    char temp[100];
    int count = 0;
    while(1){
        fgets(temp,100,ptr);
        if(strlen(temp) < 5) {
            break;
        }
        else {
            count++;
        }
    }
    fclose(ptr);
    return count -1;
}

void setTriedCount() {
    FILE * ptr;
    for (int i = 0; i < sizeInput(ptr); i++)
    {
        planes[i].triedLandCount = 0;   
    }
}

void importInput() {
    if((fptr=fopen(INPUT,"r")) == NULL) {
        printf("Dosya Acilamadi.\n");
    }
    else {
        FILE * ptrForSize;
        fgets(str,MAX,fptr); // Read the first line of input file. The first line is information line fror columns. 
        for (int i = 0; i < sizeInput(ptrForSize); i++)
        {
            fgets(str,MAX,fptr);
            if(strlen(str) > 4) {
                sscanf(str,"%d %d %d", &planes[i].priorityId, &planes[i].planeId , &planes[i].reqLandTime);
            }       
        }
    }
    fclose(fptr);
}

void printInputFile() {
    FILE * ptr;
    for (int i = 0; i < sizeInput(ptr); i++)
    {
        printf("%d %d %d\n",planes[i].priorityId, planes[i].planeId, planes[i].reqLandTime);
    }
    
}

void printOutputFile() {
    for (int i = 0; i < 24; i++) //change int 24 to plane number.
    {
        printf("%d %d %d\n",planes[i].priorityId, planes[i].planeId, planes[i].reqLandTime);
    }
}

void writeOutputFile(FILE * ptr) {
    if((ptr = fopen(OUTPUT,"w")) == NULL) {
        printf("Dosya acilamadi.\n");
    }
    fputs("oncelik_id ucak_id, talep_edilen_inis_saati, inis_saati, gecikme_suresi, kalkis_saati\n", ptr);
    for (int i = 0; i < 24; i++)
    {
        fprintf(ptr,"%d %d %d %d %d %d\n", planes[i].priorityId, planes[i].planeId, planes[i].reqLandTime, 
                                        planes[i].LandTime, planes[i].delayTime, planes[i].takeOffTime);
    }
    fclose(ptr);
}

void sortPlanes() {
    for (int i = 0; i < 28; i++)
    {
        for (int j = i+1; j < 28; j++)
        {
            Plane x;
            if(planes[i].reqLandTime > planes[j].reqLandTime) {
                x.planeId = planes[j].planeId;
                x.priorityId = planes[j].priorityId;
                x.reqLandTime = planes[j].reqLandTime;
                planes[j].planeId = planes[i].planeId;
                planes[j].priorityId = planes[i].priorityId;
                planes[j].reqLandTime = planes[i].reqLandTime;
                planes[i].priorityId = x.priorityId;
                planes[i].reqLandTime = x.reqLandTime;
                planes[i].planeId = x.planeId;
            }
        }
        
    }
    
}


int main() {
    // Create the first and the last element of the linked list.
    front = malloc(sizeof(List));
    rear = malloc(sizeof(List));
    front->next = rear;
    setTriedCount();
    // Program Started.
    importInput();
    sortPlanes();
    printInputFile();
}