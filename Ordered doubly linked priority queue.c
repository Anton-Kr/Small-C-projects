/* Program:     Ordered doubly linked priority queue.
   Author:      A. Krutyakov
   Date:        September 03, 2017
   File name:   asgn3-krutyakova2.c
   Compile:     cc -o asgn3-krutyakova2 asgn3-krutyakova2.c
   Run:         asgn3-krutyakova2
   
   The program accepts various inputs that either add (+), remove(-), query(?), or terminate(#) 
   the program. The program takes the inputs and adds them to a doubly-linked list, ordering 
   the data by priority, with the higher priority being closest to the head of the list. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct NODE {  //Definition of the NODE that will be used to simulate the process. 
   char strng[20];   
   struct NODE *next; //Forward and backward links
} Node;

typedef struct HEADER { // Definition of the HEADER 
   Node *headPtr; 
   Node *tailPtr;
} Header; 

void initHeader(Header *headerPtr); //Prototypes for the functions
void sortedAppend(Header *headerPtr, Node *nodePtrPtr);
void descPrintlist(Header *headerPtr);
void ascPrintlist(Header *headerPtr);

int main() {
   char optype; 
   time_t currentTime;
   Header header;
   Header *headerPtr = &header;
   Node *nodePtr = NULL;
   initHeader(headerPtr);
   scanf("%c", &optype);
   while(optype != '#'){
      nodePtr = (Node *) malloc(sizeof(Node)); 
      currentTime = time(NULL);
      nodePtr->arrivalTime = (int) currentTime; //Adds the current time to the arrival time of the task
      if(optype == '+'){
         scanf("%s", nodePtr->strng);
         if(dupSearch(headerPtr, nodePtr->id) == 0){ //ensure no duplicates exist
            printf("ADD: ");
            sortedAppend(headerPtr, nodePtr);
         }
         else{
            printf("%s \n", "ERROR - Process id exists - ");
            query(headerPtr, nodePtr->id);
         }
      }
      else if(optype == 'a'){
         ascPrintlist(headerPtr);
      }
      else if(optype == 'd'){
         descPrintlist(headerPtr);           
      }
      scanf("%c", &optype);
   }
   descPrintlist(headerPtr);
   ascPrintlist(headerPtr);
}
void initHeader(Header *headerPtr) {//Resets the header's head and tail ptrs to NULL
   headerPtr->headPtr = NULL;
   headerPtr->tailPtr = NULL;
}

void sortedAppend(Header *headerPtr, Node *nodePtr) { 
   Node *tempPtr = headerPtr->headPtr;
   if (tempPtr == NULL){ //Adding first node 
      headerPtr->headPtr = nodePtr;
      nodePtr->next = NULL;
   }
   else{
      while( strcmp(nodePtr->strng, tempPtr->strng) <= 0 && (tempPtr->next != NULL)){ 
         tempPtr = tempPtr->next;  //Iterate until node found or the list is finished
      }
      if(nodePtr->priority < tempPtr->priority && tempPtr->next == NULL){ //Adding node to end. Check is there to determine if it's really in the end, or just before the end. 
         tempPtr->next = nodePtr; 
         headerPtr->tailPtr = nodePtr;
         nodePtr->next = NULL;
         nodePtr->prev = tempPtr;
      }
      else if(tempPtr->prev == NULL){ //Adding node in the beginning
         nodePtr->next = tempPtr;
         nodePtr->prev = NULL;
         headerPtr->headPtr = nodePtr;
         tempPtr->prev = nodePtr;
      } 
      else{ //Adding node to the middle
          nodePtr->next = tempPtr;
          nodePtr->prev = tempPtr->prev;
          tempPtr->prev->next = nodePtr;
          tempPtr->prev = nodePtr;
      }
   }
   printf("%s \n",  nodePtr->string );
}

void descPrintlist(Header *headerPtr) {
   printf("Descending Order:\n");
   Node *tempPtr;
   tempPtr = headerPtr->tailPtr; 
   while(tempPtr !=NULL){
      printf("%d %s %d %d %d %d \n", tempPtr->id, tempPtr->program, tempPtr->jobtype, 
      tempPtr->priority, tempPtr->arrivalTime, tempPtr->executionTime);
      tempPtr = tempPtr->prev;
   }
}

void ascPrintlist(Header *headerPtr) {
       printf("Ascending Order:\n");
    Node *tempPtr; 
    tempPtr = headerPtr->headPtr;
    while(tempPtr !=NULL){
      printf("%d %s %d %d %d %d \n", tempPtr->id, tempPtr->program, tempPtr->jobtype,
      tempPtr->priority, tempPtr->arrivalTime, tempPtr->executionTime);
      tempPtr = tempPtr->next;
   }
}
