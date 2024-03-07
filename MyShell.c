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
        if (strcmp(str, "exit") == 0)
            logout(str);
        char **argumnts = splitString(str);
        if (strcmp(str, "echo") == 0)
            echo(argumnts);
        else if (strcmp(str, "cd") == 0)
        {
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
        else if (piping)
        {
            char *argv1[] = {argumnts[0], NULL};
            char *argv2[] = {argumnts[2], argumnts[3], NULL};
            mypipe(argv1, argv2);
            wait(NULL);
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