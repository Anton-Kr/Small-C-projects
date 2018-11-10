/* Program:     Simple Shell
   Author:      A. Krutyakov
   Date:        September 30, 2017
   File name:   asgn4-krutyakova2.c
   Compile:     cc -o asgn4-krutyakova2 asgn4-krutyakova2.c
   Run:         asgn4-krutyakova2
   
   The program is a simple Unix shell.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
	int i;
	char *argv[10] = {"dir", "-la"};
	char *cmdString = "ls";
	argv[9] = NULL;	
	printf("%p\n", getlogin());
	
	int pid, c_pid;
	if((c_pid = fork()) == 0){
		i = execv(cmdString, argv);
	}
	else if(c_pid < 0){
		printf("Error: %s", argv[0]);
		for(int i = 0; i<3; i++){
			printf("%s", argv[i]);
		}
		printf("\n");
	}	
	
	
}
