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
int totalFlightInDay = 0;
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

void whatIsTime() {
    printf("\n\nTime : %d",Time);
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
        printf("%d %d %d %d %d %d\n",planes[i].priorityId, planes[i].planeId, planes[i].reqLandTime, planes[i].LandTime, planes[i].delayTime, planes[i].takeOffTime);
    }
}

void printTried() {
    for (int i = 0; i < 24; i++) //change int 24 to plane number.
    {
        printf("%d %d %d %d %d %d %d\n",planes[i].priorityId, planes[i].planeId, planes[i].reqLandTime, 
                planes[i].LandTime, planes[i].delayTime, planes[i].takeOffTime, planes[i].triedLandCount);
    }
}

void writeOutputFile() {
    if((ptr = fopen(OUTPUT,"w")) == NULL) {
        printf("Dosya acilamadi.\n");
    }
    fputs("oncelik_id ucak_id, talep_edilen_inis_saati, inis_saati, gecikme_suresi, kalkis_saati\n", ptr);
    for (int i = 0; i < 24; i++)
    {
        if(planes[i].LandTime == -1) {
            fprintf(ptr,"%d %d %d %s\n", planes[i].priorityId, planes[i].planeId, planes[i].reqLandTime, 
                                        "Ucak Sabiha gokcen hava limanina yonlendirilmistir.");
        }
        else {
            fprintf(ptr,"%d %d %d %d %d %d\n", planes[i].priorityId, planes[i].planeId, planes[i].reqLandTime, 
                                        planes[i].LandTime, planes[i].delayTime, planes[i].takeOffTime);
        }
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

void addTakeOffQueue(Node ** head, int id) {

}

void transferPlane(Node ** head, int id) {
    printf("%d id li ucak Sabiha gokcene transfer edildi.\n");
    deleteElement(&(*head),id);
    int idIndex = findIndexByID(id);
    planes[idIndex].LandTime = -1;
}

void landFlight(Node ** head, int id) {
    printf("%d id li ucak inis yapti\n", id);
    deleteElement(&(*head),id);
    int idIndex = findIndexByID(id);
    planes[idIndex].LandTime = Time;
    planes[idIndex].delayTime = planes[idIndex].LandTime - planes[idIndex].reqLandTime;
}

void addlandQueue(Node ** head) {
    for (int i = IndexOfFirst(); i < IndexOfLast() +1 ; i++)
    {
        push(&(*head), planes[i].planeId);
    }
}

void delayAllQueue(Node **head) {
    Node * temp = *head;
    //find it
    bool found = false;
    while(!found) {
        if(temp == NULL) {
            break;
        }
        if(planes[findIndexByID(temp->ID)].reqLandTime == Time) {
            break;
        }
        temp = temp->next;
    }
    bool comp = false;
    while(!comp) {
        if(temp == NULL) {
            break;
        }
        planes[findIndexByID(temp->ID)].triedLandCount++;
        temp = temp->next;
    }
}

void StartFlights(Node **head) {
    if(Time > 1) {
        addlandQueue(&(*head));
    }
    Node* temp = *head;
    // find it
    int searchCount = 0;
    bool searchFailed = false;
    bool found = false; // the correct time was found.
    while(!found) {
        if(planes[findIndexByID(temp->ID)].reqLandTime == Time || searchFailed == true) {
            found = true;
            bool landComp = false;




            // check tried counts 
            Node * checkFor3 = temp;
            int countof3 = 0;
            while (checkFor3 != NULL) {
                if(planes[findIndexByID(checkFor3->ID)].triedLandCount == 3) {
                    countof3++;
                }
                checkFor3 = checkFor3->next;
            }
            if(countof3 == 0) {
                // 3 KONTROLU NEGATIF
                printf("\nNEGATIF\n");
            } 
            else if (countof3 == 1) {
                // 3 KONTROLU VAR SADECE BIR UCAK
                printf("3 KONT VAR SADECE BIR UCAK\n");
                checkFor3 = temp;
                while (checkFor3 != NULL)
                {
                    if(planes[findIndexByID(checkFor3->ID)].triedLandCount == 3) {
                        landFlight(head,checkFor3->ID);
                        landComp = true;
                        break;
                    }
                    checkFor3 = checkFor3->next;
                }
            }
            else {
                printf("IDSI KUCUK OLAN BULUNUYOR\n");
                // ID'SI KUCUK OLANI BUL VE INDIR.
                checkFor3 = temp;
                int minTempID = MAX;
                while(checkFor3 != NULL) {
                    if(planes[findIndexByID(checkFor3->ID)].triedLandCount == 3) {
                        if(checkFor3->ID < minTempID) {
                            minTempID = checkFor3->ID;
                        }
                    }
                    checkFor3 = checkFor3->next;
                }
                landFlight(head,minTempID);
                landComp = true;
                // KALANLARI AKTAR
                checkFor3 = temp;
                while(checkFor3 != NULL) {
                    if(planes[findIndexByID(checkFor3->ID)].triedLandCount == 3) {
                        transferPlane(head,checkFor3->ID);
                        printf("!! UCAK SABIHA GOKCEN HAVA LIMANINA YONLENDIRILMISTIR\n");
                    }
                    checkFor3 = checkFor3->next;
                }
            }
            // 3 KONTROLU NEGATIF ISE
            for (int u = 1; u < 5; u++) // priority from 1 to 4.
            {
                if(landComp == false) {
                    Node * checkForPri = temp;
                    int countPri = 0;
                    while(checkForPri != NULL) {
                        if(planes[findIndexByID(checkForPri->ID)].priorityId == u) {
                            countPri++;
                        }
                        checkForPri = checkForPri->next;
                    }
                    if(countPri == 0) {
                        // DIGER ONCELIKLERI KONTROL ET.
                    }
                    else if(countPri == 1) {
                        checkForPri = temp;
                        while(checkForPri != NULL) {
                            if(planes[findIndexByID(checkForPri->ID)].priorityId == u) {
                                landFlight(head,checkForPri->ID);
                                landComp = true;
                                break;
                            }
                            checkForPri = checkForPri->next;
                        }
                    }
                    else {
                        checkForPri = temp;
                        int minTempID = MAX;
                        while(checkForPri != NULL) {
                            if(planes[findIndexByID(checkForPri->ID)].priorityId == u) {
                                if(checkForPri->ID < minTempID) {
                                    minTempID = checkForPri->ID;
                                }
                            }
                            checkForPri = checkForPri->next;
                        }
                        // ID'SI KUCUK OLANI INDIR
                        landFlight(head,minTempID);
                        landComp = true;
                    }
                }
            }
        }
        temp = temp->next;
        searchCount++;
        if(searchCount >= 250 && *head != NULL) {
            searchFailed = true;
            temp = *head;
        }
        else if(searchCount >= 250) {
            if(isEmpty(&(*head))) {
                printf("\nProgram Tamamlanmistir. !!!\n");
                found = true;
                break;
            }
        }
    }
    


    delayAllQueue(&(*head));
}

int main() {
    InputSize = sizeInput();
    setTriedCount();
    // Program Started.
    importInput();
    sortPlanes();
    //printInputFile();
    printf("\n\n");
        
    // Create first node.
    Node* pq = newNode(planes[0].planeId); // add the first element of the list.
    for (int i = 1; i < 4; i++) // at 1 am.
    {
        push(&pq, planes[i].planeId);
    }
    
    for (int i = 0; i < 10; i++)
    {
        StartFlights(&pq);
        printf("\n");
        //startTakeOffQueue
        timeUp();
        printAllList(&pq);
    }
    printAllList(&pq);
    //printTried();
    return 0;
}