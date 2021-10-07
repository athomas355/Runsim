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
    
    if(argc != 2 || strtol(argv[1], NULL, 0) > 20) {
        printf("Usage: runsim n\n\t-n = number of licenses\n\t-n should not be more than 20");
    }

    FILE *file = fopen("logfile", "a");
    fputs("Time\tPID\t\tIteration#\t# of Iteration\n", file);
    fclose(file);

    char str_buffer[8];
    char str_buffer_1[8];   //buffers used for converting ints to strings
    char str_buffer_2[8];   //buffers used for converting ints to strings
    char* testsim_argv[5];
    testsim_argv[0] = "testsim";
    testsim_argv[1] = str_buffer_1;
    testsim_argv[2] = str_buffer_2;
    testsim_argv[3] = str_buffer;
    testsim_argv[4] = NULL;

    char *sleep_time[NUM_OF_PROCESSES];
    char *repeat_factor[NUM_OF_PROCESSES];
    for(int i = 0; i < NUM_OF_PROCESSES; i++) {
        sleep_time[i] = malloc(100);
        repeat_factor[i] = malloc(100);
    }
    //number of licenses from command line
    int numOfLicenses = strtol(argv[1], NULL, 0);
    
    //command line error checking

    //connect to shared memory
    block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if(block == NULL) {
        printf("runsim: ERROR: couldn't get block\n");
        return -1;
    }

    //this is a regression test
    //write to shared memory 
    #define MSG "Hello my name is Ash"
    printf("Writing from runsim: \"%s\"\n", MSG);
    strncpy(block + sizeof(int), MSG, BLOCK_SIZE - sizeof(int));
    initlicense(numOfLicenses);
    int num_of_lines = read_data_file(sleep_time, repeat_factor);

    
        
    for(int i = 0; i < num_of_lines; i++) {
        testsim_argv[1] = sleep_time[i];
        testsim_argv[2] = repeat_factor[i];
        sprintf(str_buffer, "%d", i);
        //fork runsim here and exec child process to testsim.c
        // child process because return value 
        
        int status = fork();
        if (status == 0) {
            printf("here in child; decreasing licenses\n");
            removelicenses(1);
            //request license object here using getlicense
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
            returnlicense();
        }
        
    }
    
    // for(int i = 0; i < 3; i++) {
    //     wait(NULL); //parent waits here loop before
    // }

    for(int i = 0; i < NUM_OF_PROCESSES; i++) {
        free(sleep_time[i]);
        free(repeat_factor[i]);
    }
    
    //detach from shared memory
    detach_memory_block(block);

    //need to destroy shared memory

    return 0;
}