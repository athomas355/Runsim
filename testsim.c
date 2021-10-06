#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main() {
    printf("\ntestsim: Hello, World!\n\n\n");

    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if(block == NULL) {
        printf("Error: couldn't get block\n");
        return -1;
    }

    printf("Reading from testsim \"%s\"\n", block);

    //detach from shared memory
    detach_memory_block(block);
}