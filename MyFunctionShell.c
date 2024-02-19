#include "MyFunctionShell.h"

char *inputFromUser()
{
    char ch;
    int size = 0;
    char *str = (char *)malloc((size + 1) * sizeof(char));
    // stdin = hello hello\n
    while ((ch = getchar()) != '\n')
    {
        *(str + size) = ch;
        size++;
        str = (char *)realloc(str, size + 1);
    }
    *(str + size) = '\0';
    return str;
}
char **splitString(char *str)
{

    char *subStr;
    subStr = strtok(str, " ");
    int argumentSize = 2;
    int index = 0;
    char **argumentArray = (char **)malloc(argumentSize * sizeof(char *));
    *(argumentArray + index) = subStr;
    while ((subStr = strtok(NULL, " ")) != NULL)
    {
        index++;
        argumentSize++;
        argumentArray = (char **)realloc(argumentArray, argumentSize * sizeof(char *));
        *(argumentArray + index) = subStr;
    }
    *(argumentArray + index + 1) = NULL;

    return argumentArray;
}
void getLocation()
{
    char location[256];
    if (getcwd(location, sizeof(location)) == NULL)
    {
        puts("Error");
        return;
    }
    printf("%s", "\033[33mBarak-MBP:Barak's-Shell$-\033[0m\0");
    printf("\033[0;34m");
    printf("%s$ ", location);
    printf("\033[0m");
}

void logout(char* str)
{
    puts("logout");
    free(str);
    exit(0);
}
void echo(char **arguments)

{

    
}
void cd(char *path)
{
    if (chdir(path) != 0)
    {
        puts("Error: No such file or directory");
    }
}
void cp()
{
}
void get_dir()
{
}