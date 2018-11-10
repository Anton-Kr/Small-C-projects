/* Program:        Gomoku-N Game using threads
    Author:        A. Krutyakov
    Date:          October 23, 2017
    File name:     asgn5-krutyakova2.c
    Compile:       cc -lpthread asgn5-krutyakova2 
    Run:           asgn5-krutyakova2

    The program first accepts a game size, then provides a game interface for a two player Gomuko game, using the size selected. The program uses threads to check the board for any potential wins, each round.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
    
void print2DArray(int **array, int numOfRows, int numOfCols);
void *checkHorizon(void *ptr );
void *checkDiag(void *ptr );
void *checkVertical(void *ptr );

typedef struct BUFFER { //Contains shared data
    int winCond; 
    int boardsize;
    int turn;
    int n;
    int **array2D;
}Buffer;

int main() {
    Buffer buffer;
    buffer.array2D = (int **) malloc(sizeof(int *) * buffer.boardsize);
    int gameLength = 0;
    int x, y;
    int  iret1, iret2, iret3;
    printf("Please enter game size");
    scanf("%d", &buffer.n);      
    buffer.boardsize = 2*buffer.n;
    buffer.winCond = 0;
    for (int i = 0; i < buffer.boardsize; i++) {
        buffer.array2D[i] = (int*) malloc(sizeof(int) * buffer.boardsize); //Allocates memory for the array.
    }
    while(buffer.winCond == 0 && gameLength < ((buffer.boardsize)*(buffer.boardsize))){ //Main game continues until win
        if(buffer.turn == 1) buffer.turn = 2; //... or until draw is declared.
        else buffer.turn = 1;
        print2DArray(buffer.array2D, buffer.boardsize, buffer.boardsize);
        do {
            printf("PLAYER: %i turn. Enter valid, (x,y) coordinate of turn, seperated by a space. \n" , buffer.turn);
            scanf("%i %i", &x, &y);
        } while(x >= buffer.boardsize || y >= buffer.boardsize || buffer.array2D[y][x] != 0); //Checks that the user
        buffer.array2D[y][x] = buffer.turn; //...enters a valid coordinate, that isnt already used.
        pthread_t thread1, thread2, thread3;
        int iret1, iret2, iret3;
        // create and start the three threads
        iret1 = pthread_create(&thread1, NULL, checkHorizon, (void*) &buffer);
        iret2 = pthread_create(&thread2, NULL, checkVertical, (void*) &buffer);
        iret2 = pthread_create(&thread3, NULL, checkDiag, (void*) &buffer);
        pthread_join( thread1, NULL);
        pthread_join( thread2, NULL);
        pthread_join( thread3, NULL);
        gameLength++;
    }
    print2DArray(buffer.array2D, buffer.boardsize, buffer.boardsize);
    if(buffer.winCond == 0) printf("DRAW. \n");
    else printf("Player %i wins!. \n", buffer.turn);
}

void *checkHorizon(void *ptr){
    Buffer *buffer = (Buffer*)ptr;
    int consecBuf = 0; 
    for(int i = 0; i<buffer->boardsize; i++){ //Checks each row
        for(int j = 0; j<buffer->boardsize; j++){ 
            if (buffer->array2D[i][j] == buffer->turn){
                consecBuf++; //Increments the buffer, if the location == turn.
                if (consecBuf == buffer->n){ //When buffer detects N elements, we "win"
                    buffer->winCond = 1; 
                }
            }
            else consecBuf = 0;
        }
    }
    return NULL;
}

void *checkVertical(void *ptr){
    Buffer *buffer = (Buffer*)ptr;
    int consecBuf = 0;
    for(int j = 0; j<buffer->boardsize; j++){ //Check each column
        for(int i = 0; i<buffer->boardsize; i++){
            if (buffer->array2D[i][j] == buffer->turn){
                consecBuf++; //Increments the buffer if location == trun
                if (consecBuf == buffer->n) buffer->winCond = 1; //When n elements, we win.
            }
            else consecBuf = 0;
        }
    }    
    return NULL;
}

void *checkDiag(void *ptr){ 
    //k works like an offset, as we need to check more then just the center diag line.
    Buffer *buffer = (Buffer*)ptr;
    int consecBuf = 0;
    // "\" type of check
    for(int k = 0; k<(buffer->boardsize -1); k++){ 
        for(int i = k, j = 0; i<buffer->boardsize && j<buffer->boardsize; i++ , j++){
            if (buffer->array2D[i][j] == buffer->turn){
                consecBuf++;
                if (consecBuf == buffer->n) buffer->winCond = 1;
            }
            else consecBuf = 0; //Resets the buffer if there is a break.
        }
        consecBuf = 0;
    }
    //Now must check "below" the center diag line
    for(int k = 1; k<(buffer->boardsize -1); k++){
        for(int i = 0, j = k; i<buffer->boardsize && j<buffer->boardsize; i++ , j++){
            if (buffer->array2D[i][j] == buffer->turn){
                consecBuf++;
                if (consecBuf == buffer->n) buffer->winCond = 1;
            }
            else consecBuf = 0; //Resets the buffer if there is a break.
        }
        consecBuf = 0;
    }    
    // "/" type of check
    for(int k = 0; k<(buffer->boardsize -1); k++){ 
        for(int i = k, j = buffer->boardsize; i<buffer->boardsize && j>=0; i++ , j--){
            if (buffer->array2D[i][j] == buffer->turn){
                consecBuf++;
                if (consecBuf == buffer->n) buffer->winCond = 1;
            }
            else consecBuf = 0; //Resets the buffer if there is a break.
        }
        consecBuf = 0;
    }
    // Now must check "below" the center diag line 
    for(int k = 1; k<(buffer->boardsize -1); k++){
        for(int i = buffer->boardsize - k, j = 0; i>=0 && j<buffer->boardsize; i-- , j++){
            if (buffer->array2D[i][j] == buffer->turn){
                consecBuf++;
                if (consecBuf == buffer->n) buffer->winCond = 1;
            }
            else consecBuf = 0; //Resets the buffer if there is a break.
        }
        consecBuf = 0;
    }
    return NULL;
}

void print2DArray(int **array, int numOfRows, int numOfCols) {
    int i, j;
    for (i = 0; i < numOfRows; i++) {
        for (j = 0; j < numOfCols; j++) {
            if(array[i][j] == 1) printf("=X=");
            else if (array[i][j] == 2) printf("=O=");
            else printf("= =");
        }
        printf("\n");
    }
}