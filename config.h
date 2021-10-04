#ifndef CONFIG_H
#define CONFIG_H

#define SHMKEY "/jfaeoi349djfw0fks"

int getlicense(void);           //Blocks until a license is available.
int returnlicense(void);        //Increments the number of available licenses.
int initlicense(void);          //Performs any needed initialization of the license object.
int addtolicenses(int);         //Addsnlicenses to the number available.
int removelicenses(int);        //Decrements the number of licenses byn

#endif