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

    //write to shared memory
    printf("Writing: \"%s\"\n", "Hello my name is Jeff");
    strncpy(block, "Hello my name is Ash", BLOCK_SIZE);
    
    //detach from shared memory
    detach_memory_block(block);

    return 0;
}