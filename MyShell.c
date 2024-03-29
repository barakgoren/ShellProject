#include "MyFunctionShell.h"
#include "MyShell.h"
#include <stdio.h>

int main()
{
    welcome();
    while (1)
    {
        int piping = 0;
        getLocation();
        char *str = inputFromUser();
        char **argumnts = splitString(str);
        if (strcmp(argumnts[0], "exit") == 0)
        {
            logout(str, argumnts);
        }
        if (strcmp(str, "echo") == 0)
        {
            // Check if there is a '>>' or '>' in the arguments
            for (char **p = argumnts + 1; *p != NULL; p++)
            {
                if (strcmp(*p, ">>") == 0)
                {
                    echoappend(argumnts);
                }
                else if (strcmp(*p, ">") == 0)
                {
                    echorite(argumnts);
                }
            }
        }
        else if (strcmp(str, "cd") == 0)
        {
            // Check if the path is in quotes (which means it has spaces in it)
            if (*argumnts[1] == '"')
            {
                char *path = recoverString(argumnts + 1, " ");
                cd(path);
            }
            else
            {
                cd(argumnts[1]);
            }
        }
        else if (strcmp(str, "cp") == 0)
            cp(argumnts);
        else if (strcmp(str, "delete") == 0)
            delete (argumnts);
        else if (strcmp(str, "dir") == 0)
            get_dir();
        else if (strcmp(str, "mv") == 0)
        {
            char *finalPathSrc = argumnts[1];
            char *finalPathDes = argumnts[2];
            // Check if the path of the src is in quotes (which means it has spaces in it)
            if (*argumnts[1] == '"')
            {
                finalPathSrc = recoverString(argumnts + 1, " ");
            }
            // Check if there is another path in quotes (which means it has spaces in it)
            int count = 2;
            for (char **p = argumnts + 2; *p != NULL; p++)
            {
                if (**p == '"')
                {
                    finalPathDes = recoverString(argumnts + count, " ");
                    break;
                }
                if (*(p + 1) == NULL)
                {
                    finalPathDes = *p;
                }
                count++;
            }

            if (rename(finalPathSrc, finalPathDes) == 0)
            {
                printf("File moved successfully\n");
            }
            else
            {
                printf("Error: File not moved\n");
            }
        }
        else if (piping)
        {
            char *argv1[] = {argumnts[0], NULL};
            char *argv2[] = {argumnts[2], argumnts[3], NULL};
            mypipe(argv1, argv2);
            wait(NULL);
        }
        else if(strcmp(str, "read") == 0)
        {
            myRead(argumnts);
        }
        else if(strcmp(str, "wc") == 0)
        {
            wordCount(argumnts);
        }
        else
        {
            int status;
            systemCall(argumnts);
            wait(&status);

            if (WIFEXITED(status))
            {
                int exit_status = WEXITSTATUS(status);
                if (exit_status == 0)
                {
                    printf("The process exited normally with status 0\n");
                }
                else
                {
                    printf("Unknown command: %s\n", argumnts[0]);
                }
            }
            else
            {
                printf("The process did not exit normally\n");
            }
        }
    }

    return 0;
}