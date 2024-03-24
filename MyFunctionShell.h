#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>


// Not related to the shell
void blue();
void green();
void purple();
void reset();
void printLogo(char *[]);
void welcome();

// Related to the shell
char* myStrtok(char*, const char*);
char* recoverString(char**, char*);
char* inputFromUser();
char** splitString(char*);
void getLocation();
void logout(char*, char**);
void echo(char **arguments);
void cd(char *path);
void cp(char **arguments);
void get_dir();
void delete(char **arguments);
void mypipe(char **argv1, char **argv2);
void systemCall(char **arg);
