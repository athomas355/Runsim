#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "config.h"

void sig_handler(int signum){
    printf("Caught signal %d, coming out...\n", signum);
    abort();
}

int main(int argc, char* argv[]) {

    int sleep_time = strtol(argv[1], NULL, 0);
    int repeat_factor = strtol(argv[2], NULL, 0);
    
    //error check the command line inputs
    if(sleep_time <= 0) {
        printf("testsim: ERROR: sleep time must be positive integer\n");
        exit(-1);
    }

    if(repeat_factor <= 0) {
        printf("testsim: ERROR: repeat factor must be positive integer\n");
        exit(-1);
    }
    
    char msg[1024];
    char time_buffer[27];
    time_t timer;
    struct tm* tm_info;
    int currentPID;
    signal(SIGINT, sig_handler);    //signal handling for ctrl+c
    signal(SIGALRM,sig_handler); // Register signal handler
    alarm(3);  // Scheduled alarm after # seconds                                

    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if(block == NULL) {
        printf("Error: couldn't get block\n");
        return -1;
    }

    printf("Reading from testsim \"%s\"\n", block);


    for(int i = 0; i < repeat_factor; i++) {
        //sleeps
        printf("About to sleep\t");
        sleep(sleep_time);
        printf("slept\n");

        //current time
        timer = time(NULL);
        tm_info = localtime(&timer);

        //if you change 26 here make sure to change 26 in other places as well
        strftime(time_buffer, 26, "%H:%M:%S", tm_info);
        currentPID = (int)getpid();

        sprintf(msg, "%s\t%d\t%d of %d\n", time_buffer, currentPID, i + 1, repeat_factor);

        logmsg(msg);
    }

    //detach from shared memory
    detach_memory_block(block);
}