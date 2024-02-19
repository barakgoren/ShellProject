#include "MyFunctionShell.h"
#include "MyShell.h"

void wellcome()
{
    puts("Hello MyShell");
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
            cd(argumnts[1]);

        free(str);
        free(argumnts);
    }

    return 0;
}