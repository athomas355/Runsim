#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "config.h"
#include "pshm_ucase.h"

int mode = 0700;    //user all access, group has no access, and o has no access

//function for allocating shared memory
int allocate_shm_mem(size_t size) {
    int fd = shm_open(SHMKEY, O_RDONLY, mode);

    if(fd < 0) {
        perror("Error: ");
        //printf("shm_open failed\n");
        exit(-1);
    }

    struct shmbuf *fshmp;

    if(ftruncate(fd, sizeof(*fshmp)) == -1) {
        //perror(errno);
        printf("ftruncate failed %d\n", errno);
        exit(-1);
    }

    return fd;
}

//function for deallocating shared memory


int main(int argc, char* argv[]) {

    char* string = "runsim: Hello, World!";
    size_t len = strlen(string);

    //number of licenses
    int numOfLicenses = strtol(argv[1], NULL, 0);          //if not an integer atoi will fail
    // perror(errno);
    // exit(1);

    if(numOfLicenses < 0) {
        //error for input of a negative number
        // perror(errno);
        printf("Cannot have negative licenses.\n");
        exit(1);
    }

    if (len > BUF_SIZE - 2) {   //you have to leave room for the null byte
        fprintf(stderr, "String is too long\n");
        exit(EXIT_FAILURE);
    }

    //open shared memory
    int fd = allocate_shm_mem(1024*1024);

    // int fd = shm_open(SHMKEY, O_RDWR, 0700);
    // if(fd == -1) {
    //     perror(errno);
    //     exit(-1);
    // }

    struct shmbuf *shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    shmp->cnt = len;
    //passing the address of shmp->buf 
    //buf is pointing to a copy of string
    memcpy(&shmp->buf, string, len);

    write(STDOUT_FILENO, &shmp->buf, len);
    write(STDOUT_FILENO, "\n", 1);


    exit(EXIT_SUCCESS);
    //printf("runsim: Hello, World!\n");
}