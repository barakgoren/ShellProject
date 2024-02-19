#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

char* inputFromUser();
char** splitString(char*);
void getLocation();
void logout(char*);
void echo(char **arguments);
void cd(char *path);
void cp();
void get_dir();