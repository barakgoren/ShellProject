#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

void getLocation() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s: ", cwd);
    } else {
        perror("getcwd() error");
    }
}

void logout() {
    printf("Goodbye!\n");
    exit(0);
}

int main()
{
    while (1)
    {
        char ch;
        int size = 0;
        char *start = (char *)malloc((size + 1) * sizeof(char));
        getLocation();
        while ((ch = getchar()) != '\n')
        {
            *(start + size) = ch;
            size++;
            start = (char *)realloc(start, size + 1);
        }
        *(start + size) = '\0';
        // input string

        char *subStr;
        subStr = strtok(start, " ");

        int argumentSize = 0;
        char **pArrWithMalloc = (char **)malloc(argumentSize + 1 * sizeof(char *));
        *(pArrWithMalloc + argumentSize) = subStr;
        while ((subStr = strtok(NULL, " ")) != NULL)
        {
            argumentSize++;
            pArrWithMalloc = (char **)realloc(pArrWithMalloc, argumentSize + 1 * sizeof(char *));
            *(pArrWithMalloc + argumentSize) = subStr;
        }
        for (int i = 0; i <= argumentSize; i++)
        {
            puts(pArrWithMalloc[i]);
        }
        
    }

    return 0;
}