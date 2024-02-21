#include "MyFunctionShell.h"
#include "MyShell.h"

void wellcome()
{
    puts("Hello MyShell");
}

char *mergeStrings(char **strings)
{
    // Calculate the total length of all the strings
    int totalLength = 0;
    for (int i = 0; strings[i] != NULL; i++)
    {
        totalLength += strlen(strings[i]);
    }

    // Allocate a new string to hold all the strings
    char *merged = malloc(totalLength + 1);
    if (merged == NULL)
    {
        return NULL;
    }

    // Copy each string into the new string
    char *dest = merged;
    for (int i = 0; strings[i] != NULL; i++)
    {
        char *src = strings[i];
        if (i == 0)
            src++;
        while (*src != '\0')
        {
            *dest = *src;
            dest++;
            src++;
        }
        *dest = ' ';
        dest++;
    }

    *(merged + totalLength - 1) = '\0';


    return merged;
}

int main()
{
    wellcome();
    while (1)
    {
        getLocation();
        char *str = inputFromUser();
        if (strcmp(str, "exit") == 0)
            logout(str);

        char **argumnts = splitString(str);
        if (strcmp(str, "echo") == 0)
            echo(argumnts);
        if (strcmp(str, "cd") == 0)
        {
            if (*argumnts[1] == '"')
            {
                char *path = mergeStrings(argumnts + 1);
                printf("%s\n", path);
            } else {
                printf("%s\n", argumnts[1]);
            }
        }

        free(str);
        free(argumnts);
    }

    return 0;
}