#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "config.h"


int main(int argc, char* argv[]) {
    
    //number of licenses from command line
    int numOfLicenses = strtol(argv[1], NULL, 0);;

    //command line error checking

    //connect to shared memory
    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if(block == NULL) {
        printf("Error: couldn't get block\n");
        return -1;
    }

    //this is a regression test
    //write to shared memory 
    #define MSG "Hello my name is Ash"
    printf("Writing from runsim: \"%s\"\n", MSG);
    strncpy(block, MSG, BLOCK_SIZE);

    //fork runsim here and exec child process to testsim.c
    // child process because return value zero
    if (fork() == 0) {
        execve("testsim", argv, NULL);
    }
    // parent process because return value non-zero.
    else {
        sleep(3);
        printf("Hello from Parent!\n");
    }

    //detach from shared memory
    detach_memory_block(block);

    return 0;
}