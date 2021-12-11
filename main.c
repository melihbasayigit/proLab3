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

typedef struct node {
    int ID;
    int priority;
 
    struct node* next;
} Node;

typedef struct PlaneClass Plane;

// GLOBAL VARIABLES
bool IsDayCompleted = false; 
FILE *fptr; // File pointer for input.txt .. The file will be used in many lines and methods.
int Time = 1;
char str[MAX];
// GLOBAL VALUE FOR READ TO FILE FUNCTION
Plane planes[28];

Node* newNode(int d, int p)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->ID = d;
    temp->priority = p;
    temp->next = NULL;
 
    return temp;
}

int peek(Node** head)
{
    return (*head)->ID;
}

void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

void push(Node** head, int d, int p)
{
    Node* start = (*head);
     Node* temp = newNode(d, p);
    if ((*head)->priority > p) {
 
        temp->next = *head;
        (*head) = temp;
    }
    else {
        while (start->next != NULL &&
            start->next->priority < p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

int isEmpty(Node** head)
{
    return (*head) == NULL;
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
    setTriedCount();
    // Program Started.
    importInput();
    sortPlanes();

    Node* pq = newNode(planes[0].planeId, planes[0].reqLandTime);
    for (int i = 1; i < 27; i++)
    {
        push(&pq, planes[i].planeId, planes[i].reqLandTime);
    }
 
    while (!isEmpty(&pq)) {
        printf("%d ", peek(&pq));
        pop(&pq);
    }

    // Listeyi prioritye göre sırala

    return 0;
}