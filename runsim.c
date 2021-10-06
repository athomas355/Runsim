#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include "config.h"


int main(int argc, char* argv[]) {
    
    char str_buffer[8];
    char* testsim_argv[5];
    testsim_argv[0] = "testsim";
    testsim_argv[1] = "1";
    testsim_argv[2] = "3";
    testsim_argv[3] = str_buffer;
    testsim_argv[4] = NULL;
    //number of licenses from command line
    int numOfLicenses = strtol(argv[1], NULL, 0);

    //command line error checking

    //connect to shared memory
    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if(block == NULL) {
        printf("runsim: ERROR: couldn't get block\n");
        return -1;
    }

    //this is a regression test
    //write to shared memory 
    #define MSG "Hello my name is Ash"
    printf("Writing from runsim: \"%s\"\n", MSG);
    strncpy(block, MSG, BLOCK_SIZE);

    for(int i = 0; i < 3; i++) {
        sprintf(str_buffer, "%d", i);
        //fork runsim here and exec child process to testsim.c
        // child process because return value 
        
        int status = fork();
        if (status == 0) {
            printf("here in child\n");
            if (execve("testsim", testsim_argv, NULL) == -1) {
                perror("runsim: ERROR: ");
            }
        }
        else if (status == -1) {
            printf("fork call failed in iteration %d\n", i);
            exit(-1);
        }
        else {
            printf("here in parent\n");
            wait(NULL);
        }
        
    }
    // for(int i = 0; i < 3; i++) {
    //     wait(NULL); //parent waits here loop before
    // }
    //detach from shared memory
    detach_memory_block(block);

    return 0;
}