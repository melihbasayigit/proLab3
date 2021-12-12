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
 
    struct node* next;
} Node;

typedef struct PlaneClass Plane;

// GLOBAL VARIABLES
bool IsDayCompleted = false; 
FILE *fptr; FILE *ptr;// File pointer for input.txt .. The file will be used in many lines and methods.
int InputSize = MAX;
int Time = 1;
char str[MAX];
// GLOBAL VALUE FOR READ TO FILE FUNCTION
Plane planes[28];

// DEFINE FUNC FIRST
int findIndexByID(int id);

Node* newNode(int d)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->ID = d;
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

void printAllList(Node ** head) {
    int counter = 0;
    Node * temp = *head;
    if((*head) != NULL) {
        printf("%d ", (*head)->ID);
        counter++;
    }
    while(temp->next != NULL) {
        temp = temp->next;
        printf("%d ", temp->ID);
        counter++;
    }
    printf("\nCOUNTER :: %d", counter);
    printf("\n");
}

void deleteElement(Node** head, int id)
{
    Node* temp = *head;
    // find it
    if (temp->ID == id) { // search the head
        (*head) = (*head)->next;
        free(temp);
    }
    else {
        Node * del;
        while((temp->next)->ID != id) {
            temp = temp->next;
        }
        del = temp->next;
        // delete it
        temp->next = temp->next->next;
        free(del);
    }    
}

void push(Node** head, int d)
{
    Node* start = (*head);
    Node* temp = newNode(d);
 
    temp->next = *head;
    (*head) = temp;
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

int sizeInput() { // Return size of planes in the input file.
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
    for (int i = 0; i < InputSize; i++)
    {
        planes[i].triedLandCount = 0;   
    }
}

void importInput() {
    if((fptr=fopen(INPUT,"r")) == NULL) {
        printf("Dosya Acilamadi.\n");
    }
    else {
        fgets(str,MAX,fptr); // Read the first line of input file. The first line is information line fror columns. 
        for (int i = 0; i < InputSize; i++)
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
    for (int i = 0; i < InputSize; i++)
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

void writeOutputFile() {
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
    for (int i = 0; i < InputSize; i++)
    {
        for (int j = i+1; j < InputSize; j++)
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
            else if (planes[i].reqLandTime == planes[j].reqLandTime) {
                if(planes[i].priorityId <= planes[j].priorityId) {
                    Plane y;
                    y.planeId = planes[j].planeId;
                    y.priorityId = planes[j].priorityId;
                    planes[j].planeId = planes[i].planeId;
                    planes[j].priorityId = planes[i].priorityId;
                    planes[i].priorityId = y.priorityId;
                    planes[i].planeId = y.planeId;
                }
            }
        }
        
    }
    
}

int findIndexByID(int id) {
    for (int i = 0; i < InputSize; i++)
    {
        if(planes[i].planeId == id) {
            return i;
        }
    }
}

int IndexOfLast() {
    for (int i = InputSize - 1; i >= 0; i--)
    {
        if(Time == planes[i].reqLandTime) {
            return i;
        }
    }
    
}

int IndexOfFirst() {
    for (int i = 0; i < InputSize; i++)
    {
        if(Time == planes[i].reqLandTime) {
            return i;
        }
    }
}

void addTakeOffQueue(int id) {

}

void StartFlights(Node **head) {
    Node* temp = *head;
    // find it
    bool found = false;
    while(!found) {
        if(planes[findIndexByID(temp->ID)].reqLandTime == Time) {
            found = true;
            // check tried counts 
            if(planes[findIndexByID(temp->ID)].triedLandCount >= 3) {
                Node * checkFor3 = temp;
                bool landComp = false;
                while(checkFor3->next != NULL) {
                    if (planes[findIndexByID(checkFor3->ID)].triedLandCount >= 3 && landComp == false)
                    {
                        found = true;
                        planes[findIndexByID(checkFor3->ID)].triedLandCount = -1;
                        planes[findIndexByID(checkFor3->ID)].LandTime = Time;
                        deleteElement(&(*head),checkFor3->ID);
                        //ADD THIS PLANE TO TAKE OFF QUEUE.
                        landComp = true;
                    }
                    if(landComp == true) {
                        if (planes[findIndexByID(checkFor3->ID)].triedLandCount >= 3) {
                            // TRANSFER THE PLANE TO THE OTHER AIRPORT
                        }
                    }
                    checkFor3 = checkFor3->next;
                }
                if(found == true) {
                    // ADD +1 TRIED THE OTHERS // IF TRIED COUNT >= 0, ADD 1. 
                }
            }
            if(found == true) {
                break;
            }
            //CHECK PRIORITIES.
            Node * checkForPri = temp;
            bool landComp = false;
            if(planes[findIndexByID(checkForPri->ID)].priorityId == 1) {
                found = true;
                planes[findIndexByID(checkForPri->ID)].triedLandCount = -1;
                planes[findIndexByID(checkForPri->ID)].LandTime = Time;
                deleteElement(&(*head),checkForPri->ID);
                // ADD IT TO THE TAKE OFF QUEUE
                landComp = true;
                checkForPri = temp;
            }
            else if (planes[findIndexByID(checkForPri->ID)].priorityId == 2 && landComp == false) {
                found = true;
                planes[findIndexByID(checkForPri->ID)].triedLandCount = -1;
                planes[findIndexByID(checkForPri->ID)].LandTime = Time;
                deleteElement(&(*head),checkForPri->ID);
                // ADD IT TO THE TAKE OFF QUEUE
                landComp = true;
                checkForPri = temp;
            }
            else if (planes[findIndexByID(checkForPri->ID)].priorityId == 3 && landComp == false) {
                
                found = true;
                planes[findIndexByID(checkForPri->ID)].triedLandCount = -1;
                planes[findIndexByID(checkForPri->ID)].LandTime = Time;
                deleteElement(&(*head),checkForPri->ID);
                // ADD IT TO THE TAKE OFF QUEUE
                landComp = true;
                checkForPri = temp;
            }
            else if (planes[findIndexByID(checkForPri->ID)].priorityId == 4 && landComp == false) {
                
                found = true;
                planes[findIndexByID(checkForPri->ID)].triedLandCount = -1;
                planes[findIndexByID(checkForPri->ID)].LandTime = Time;
                deleteElement(&(*head),checkForPri->ID);
                // ADD IT TO THE TAKE OFF QUEUE
                landComp = true;
                checkForPri = temp;
            }
        }
        temp = temp->next;
    }
    timeUp();
}

/*void dl(Node ** head) {
    deleteElement(&(*head),12);
}*/

int main() {
    InputSize = sizeInput();
    setTriedCount();
    // Program Started.
    importInput();
    sortPlanes();
    printInputFile();
    printf("\n\n");
    
    // TRY IDNEX OF LAST AND INDEX OF FIRST FUNCTION

    // Create first node.
    Node* pq = newNode(planes[0].planeId);
    // Add the other nodes.
    for (int i = 1; i < InputSize; i++)
    {
        push(&pq, planes[i].planeId);
    }
    StartFlights(&pq);
    printAllList(&pq);

    return 0;
}