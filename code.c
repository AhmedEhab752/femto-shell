#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <unistd.h>

#include <signal.h>



#define	MAX_SIZE_CMD	256

#define	MAX_SIZE_ARG	16

#define CHARACTERS_NUM  50





char userinput[CHARACTERS_NUM];

char cmd[MAX_SIZE_CMD];				// string holder for the command

char *argv[MAX_SIZE_ARG];			// an array for command and arguments

pid_t pid;		                        // global variable for the child process ID

char i;						// global for loop counter

int character_index = 0;

void get_cmd();					// get command string from the user

void convert_cmd();				// convert the command string to the required format by execvp()

void c_shell();					// to start the shell

void log_handle(int sig);			// signal handler to add log statements



int main(){



	// start the shell

	c_shell();



	return 0;

}



void c_shell(){

	while(1){

		// get the command from user

		get_cmd();



		// bypass empty commands

		if(!strcmp("", cmd)) continue;



		// check for "exit" command

                if(!strcmp("exit", cmd)) break;



		// fit the command into *argv[]

		convert_cmd();



		// fork and execute the command

		pid = fork();

		if(-1 == pid){

			printf("failed to create a child\n");

		}

		else if(0 == pid){

			// printf("hello from child\n");

			// execute a command

			

			execvp(argv[0], argv);

		}

		else{

			// printf("hello from parent\n");

			// wait for the command to finish if "&" is not present

			if(NULL == argv[i]) waitpid(pid, NULL, 0);

		}

	}

}



void get_cmd(){

	// get command from user

	printf("Shell>\t");

	fgets(cmd, MAX_SIZE_CMD, stdin);

	// remove trailing newline

	if ((strlen(cmd) > 0) && (cmd[strlen (cmd) - 1] == '\n'))

        	cmd[strlen (cmd) - 1] = '\0';

	//printf("%s\n", cmd);

}



void convert_cmd(){

	// split string into argv

	char *ptr;

	i = 0;

	ptr = strtok(cmd, " ");

	while(ptr != NULL){

		//printf("%s\n", ptr);

		argv[i] = ptr;

		i++;

		ptr = strtok(NULL, " ");

	}

}



