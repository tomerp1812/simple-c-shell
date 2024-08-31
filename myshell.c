#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include <sys/wait.h>
#include <stdlib.h>

//clears buffer
void clear (void)
{
    while ( getchar() != '\n' );
}

// A function to print the error message for a failed command
void error(char* command){
    char errorPrint[strlen(command) + 8];
    strcpy(errorPrint, command);
    strcat(errorPrint, " failed");
    perror(errorPrint);
}

// A function to check if the entered command is one of the built-in commands or not
int check(char **command, char allCommands[100][100], int counter, int* pid){
    pid[counter] = getpid();
    if(strcmp(command[0], "cd") == 0){
        int e = chdir(command[1]);
        if(e == -1){
            error(command[0]);
        }
        return 0;
    }
    else if(strcmp(command[0], "history") == 0){
        for (int i = 0; i < counter + 1; ++i) {
            //prints all the history of all commands + the pid of each command
           printf("%d %s\n", pid[i], allCommands[i]);
        }
        return 0;
    }
    else if(strcmp(command[0], "exit") == 0){
        exit(0);
    }else{
        return 1;
    }
}


// A function to print the prompt
void prompt(){
    printf("$ ");
    fflush(stdout);
}

// A function to run the entered command, not one of the built-in commands
int run(char **args){
    pid_t pid = fork();
    //child will run the command
    if(pid == 0){
        int e = execvp(args[0], args);
        if(e == -1){
            error(args[0]);
            exit(1);
        }
    }
    else{
        //father waits for child to finish command
        wait(NULL);
    }
    return pid;
}

int main(int argc, char** argv){
    // Initialize variables
    char commands[100];
    char *token;
    char allCommands[100][100];
    char* delim = " ";
    int counter=0;
    int commandCounter = 0;
    char *args[100] = {NULL};
    int pid[100];

    // Set the PATH environment variable
    char *path = getenv("PATH");
    char *newPath;
    newPath = (char*) malloc(sizeof(char)* strlen(path) + 2 * sizeof(char));
    strcat(newPath, path);
    for (int i = 1; i < argc; ++i) {
        strcat(newPath,":");
       newPath = realloc(newPath, strlen(newPath)*sizeof(char) + strlen(argv[i])*sizeof(char) + 2 * sizeof(char));
       strcat(newPath, argv[i]);
    }
    setenv("PATH", newPath, 1);

    // Enter the main loop to prompt the user for input and execute commands
    while(1){
        prompt();
        // Read user input
        scanf(" %[^\n]", commands);
        strcpy(allCommands[commandCounter], commands);
        // Tokenize the input and store the tokens in args
        token = strtok(commands, delim);
        args[0] = (char*) malloc(sizeof(char) * strlen(token) + sizeof(char));
        strcpy(args[0], token);

        while( token != NULL){
            counter++;
            token = strtok(NULL, delim);
            if(token != NULL){
                args[counter] = (char*) malloc(sizeof(char) * strlen(token) + sizeof(char));
                strcpy(args[counter], token);
            }
        }
        counter = 0;
        // Store the entered command in allCommands and check if it is a built-in command
        if (check(args, allCommands, commandCounter, pid) == 1){
            pid[commandCounter] = run(args);
        }
        commandCounter++;
    }
}