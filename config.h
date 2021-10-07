#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

char * attach_memory_block(char *filename, int size);
bool detach_memory_block(char *block);
bool destroy_memory_block(char *filename);

//functions from prompt
int getlicense(void);           //Blocks until a license is available.
int returnlicense(void);        //Increments the number of available licenses.
int initlicense(int);          //Performs any needed initialization of the license object.
void addtolicenses(int);         //Addsnlicenses to the number available.
void removelicenses(int);        //Decrements the number of licenses by n
void logmsg(char*);
int read_data_file(char *time_delay[], char *repeat_factor[]);

#define BLOCK_SIZE 4096
#define NUM_OF_PROCESSES 20
#define FILENAME "runsim.c"

char *block;        //block points to string in shared memory
int *nlicenses;     //nlicenses points to a number of licenses in shared memory

#endif