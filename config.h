#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

char * attach_memory_block(char *filename, int size);
bool detach_memory_block(char *block);
bool destroy_memory_block(char *filename);

//functions from prompt
int getlicense(void);           //Blocks until a license is available.
int returnlicense(void);        //Increments the number of available licenses.
int initlicense(void);          //Performs any needed initialization of the license object.
int addtolicenses(int);         //Addsnlicenses to the number available.
int removelicenses(int);        //Decrements the number of licenses byn
void logmsg(char*);

#define BLOCK_SIZE 4096
#define FILENAME "runsim.c"

#endif