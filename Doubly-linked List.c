/* Program:     Doubly-linked List in C
   Author:      A. Krutyakov
   Date:        September 03, 2017
   File name:   asgn2-krutyakova2.c
   Compile:     cc -o asgn2-krutyakova2 asgn2-krutyakova2.c
   Run:         asgn2-krutyakova2

   The program accepts a process which contains the id, program, job type, priority, execution type
   puts them into a doubly-linked order, and prints them in both FIFO and LIFO order
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct NODE {  //Definition of the NODE that will be used to simulate the process. 
   int id; 
   char program[20];   
   int jobtype;
   int priority;
   int executionTime;
   struct NODE *next; //Forward and backward links
   struct NODE *prev;
} Node;

typedef struct HEADER { // Definition of the HEADER that will link to both the first and the last data in the structure
   Node *headPtr; 
   Node *tailPtr;
   int count;
} Header; 

void initHeader(Header *headerPtr); //Prototypes for the functions
void append(Header *headerPtr, Node *nodePtrPtr);
void printList(Header *headerPtr, int desc);

int main() {
   int id;
   char program[20];   
   int jobtype;
   int priority;
   int executionTime;
   int numofRecords;
   int i;
   time_t currentTime;
   
   Header header;
   Header *headerPtr = &header;
   Node *nodePtr = NULL;
   initHeader(headerPtr);

   scanf("%d", &(numofRecords)); // Number of records we will be recording
   
   for (i = 0; i < numofRecords; i++){
      currentTime = time(NULL);
	  nodePtr = (Node *) malloc(sizeof(Node));
	  scanf("%d%s%d%d%d", &(nodePtr->id), nodePtr->program, &(nodePtr->jobtype), &(nodePtr->priority), &(nodePtr->executionTime));
	  nodePtr->executionTime += (long) currentTime; //Adds current time+execution time. 
      append(headerPtr, nodePtr);   
   }
   printList(headerPtr, 0); //Prints list in both asc and desc order
   printList(headerPtr, 1);
}
void initHeader(Header *headerPtr) {//Resets the header's head and tail ptrs to NULL
   headerPtr->headPtr = NULL;
   headerPtr->tailPtr = NULL;
   headerPtr->count = 0;
}

void append(Header *headerPtr, Node *nodePtr) {
   Node *tempPtr = headerPtr->headPtr;
   int count = headerPtr->count;
   if (tempPtr == NULL) {
      headerPtr->headPtr = nodePtr;
	  nodePtr->prev = headerPtr;
   }
   else {
      while (tempPtr->next != NULL) tempPtr = tempPtr->next;
      tempPtr->next = nodePtr;
	  nodePtr->prev = tempPtr;
	  headerPtr->tailPtr = nodePtr;
      nodePtr->next = NULL;
   }
   headerPtr->count = headerPtr->count + 1;

   return;
}

void printList(Header *headerPtr, int desc) { //2nd parameter used to determine if we are printing in ascending or descending order
   int i = 0;
   if(desc == 1) printf("Descending Order:\n");
   else printf("Ascending Order:\n");
   Node *tempPtr;
   if (headerPtr->count != 0) {
	  if(desc == 1){
         tempPtr = headerPtr->tailPtr; 
	  }
      else{
		  tempPtr = headerPtr->headPtr;
	  }
      for (i = 0; i < headerPtr->count; i++) {
         printf("%d %s %d %d %d \n", tempPtr->id, tempPtr->program, tempPtr->jobtype, tempPtr->priority, tempPtr->executionTime);
		 if(desc == 1) tempPtr = tempPtr->prev;
         else tempPtr = tempPtr->next;
      }
   }
}








