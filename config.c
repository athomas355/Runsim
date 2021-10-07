#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "config.h"

#define IPC_RESULT_ERROR (-1)

static int get_shared_block(char *filename, int size) {
    key_t key;

    key = ftok(filename, 0);
    printf("key = %x\n", key);
    if(key == IPC_RESULT_ERROR) {
        return IPC_RESULT_ERROR;
    }

    return shmget(key, size, 0644 | IPC_CREAT);
}

//pointer attaches to shared memory segment
char * attach_memory_block(char *filename, int size) {
    int shared_block_id = get_shared_block(filename, size);
    char *result;

    if(shared_block_id == IPC_RESULT_ERROR) {
        return NULL;
    }

    result = shmat(shared_block_id, NULL, 0);
    if(result == (char *)IPC_RESULT_ERROR) {
        return NULL;
    }

    return result;
}

bool detach_memory_block(char *block) {
    return (shmdt(block) != IPC_RESULT_ERROR);
}
bool destroy_memory_block(char *filename){
    int shared_block_id = get_shared_block(filename, 0);

    if(shared_block_id == IPC_RESULT_ERROR) {
        return NULL;
    }

    return (shmctl(shared_block_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}

//Blocks until a license is available.
int getlicense(void) {
    
    return 0;
}           

//Increments the number of available licenses.
int returnlicense(void) {
    *nlicenses++;
    return *nlicenses;
}  

//Performs any needed initialization of the license object.
int initlicense(int n) {
    nlicenses = (int*)block;
    *nlicenses = n;
    return 0;
} 

//Addsnlicenses to the number available.
void addtolicenses(int n) {
    *nlicenses = n + *nlicenses;
}   

//Decrements the number of licenses byn tashish715  Valleyhawks123
void removelicenses(int n) {
    *nlicenses = n - *nlicenses;
}

void logmsg(char* msg) {
    FILE *file = fopen("logfile", "a");

    fputs(msg, file);

    fclose(file);
}

int read_data_file(char *time_delay[], char *repeat_factor[] ){
    char dummy[10000];
    int line_ctr = 0;
    while (!feof(stdin)) {
      scanf("%s %s %s", dummy, time_delay[line_ctr], repeat_factor[line_ctr]);
      line_ctr++;
    }

    return line_ctr;
}
    