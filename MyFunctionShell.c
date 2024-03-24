#include "MyFunctionShell.h"
#include <stddef.h> // Include this header to define NULL


// Not related to the shell
void blue()
{
    printf("\033[0;34m");
}
void green()
{
    printf("\033[0;32m");
}
void purple()
{
    printf("\033[0;35m");
}
void reset()
{
    printf("\033[0m");
}
void printLogo(char *logo[])
{
    int i = 0;
    while (logo[i] != NULL)
    {
        if (i == 0)
        {
            blue();
        }
        if (i == 17)
        {
            purple();
        }
        if (i == 20)
        {
            blue();
        }
        if (i == 23)
        {
            reset();
        }
        printf("%s\n", logo[i]); // Print each line followed by a newline
        i++;
    }
}
void welcome()
{
    char *logo[] = {
        "     ________________________________________________",
        "    /                                                \\",
        "   |    _________________________________________     |",
        "   |   |                                         |    |",
        "   |   |  me@h-MBP & Welcome to Simple Shell     |    |",
        "   |   |                                         |    |",
        "   |   |  Version 1.0                            |    |",
        "   |   |                                         |    |",
        "   |   |  https://github.com/barakgoren          |    |",
        "   |   |                                         |    |",
        "   |   |  Have fun! █                            |    |",
        "   |   |                                         |    |",
        "   |   |_________________________________________|    |",
        "   |                                                  |",
        "    \\_________________________________________________/",
        "           \\___________________________________/",
        "        ___________________________________________",
        "     _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_",
        "  _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_",
        "_-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.___. .---.-.-.`-_",
        ":-------------------------------------------------------------------:",
        "`---._.-------------------------------------------------------------._.---'",
        NULL};
    printLogo(logo);
}

// Related to the shell
char *myStrtok(char *str, const char *delim)
{
    static char *next_token = NULL; // Static pointer to maintain state between calls

    // If str is not NULL, we are starting a new tokenization
    if (str != NULL)
    {
        next_token = str;
    }

    // If next_token is NULL, there are no more tokens
    if (next_token == NULL)
    {
        return NULL;
    }

    // Skip leading delimiters
    next_token += strspn(next_token, delim);

    // If we reach the end of the string, return NULL
    if (*next_token == '\0')
    {
        return NULL;
    }

    // Find the end of the token
    char *end = next_token + strcspn(next_token, delim);

    // If we found a delimiter, null-terminate the token and update next_token
    if (*end != '\0')
    {
        *end = '\0';
        end++;
    }

    // Save the start of the current token
    char *current_token = next_token;

    // Update next_token for the next call
    next_token = end;

    // Return the current token
    return current_token;
}
char *recoverString(char **arguments, char *delim)
{
    char *recoverString = arguments[0];
    recoverString++;

    for (char **p = arguments; *p != NULL; p++)
    {
        char *s = *p;
        if (*(p + 1) == NULL)
        {
            while (*s != '"')
            {
                s++;
            }
            *s = '\0';
        }
        while (1)
        {
            if (*s == '\0')
            {
                *s = *delim;
                break;
            }
            s++;
        }
    }
    recoverString[strlen(recoverString) - 1] = '\0';
    return recoverString;
}
char *inputFromUser()
{
    static int commandsSize = 0;
    static char **commands;
    if (commands == NULL)
    {
        commands = (char **)malloc((commandsSize + 1) * sizeof(char *));
    }
    else
    {
        commands = (char **)realloc(commands, (commandsSize + 1) * sizeof(char *));
    }
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
    *(commands + commandsSize) = str;
    commandsSize++;

    return str;
}
char **splitString(char *str)
{

    char *subStr;
    subStr = myStrtok(str, " ");
    int argumentSize = 2;
    int index = 0;
    char **argumentArray = (char **)malloc(argumentSize * sizeof(char *));
    *(argumentArray + index) = subStr;
    while ((subStr = myStrtok(NULL, " ")) != NULL)
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
    char hostName[256];

    if (gethostname(hostName, sizeof(hostName)) == -1){
        puts("Error");
        return;
    }
    
    if (getcwd(location, sizeof(location)) == NULL)
    {
        puts("Error");
        return;
    }
    printf("%s", "\033[33mBarak's-Shell$-\033[0m\0");
    printf("\033[0;34m");
    printf("%s",hostName);
    printf("%s$ ", location);
    printf("\033[0m");
}

void logout(char *str, char **args)
{
    puts("logout");
    free(str);
    free(args);
    exit(0);
}
void echo(char **arguments)

{
}
void cd(char *path)
{
    if (chdir(path) != 0)
    {
        printf("Error: No such file or directory '%s'\n", path);
    }
}
void cp(char **arguments)
{
    char ch;
    FILE *src, *des;
    if ((src = fopen(arguments[1], "r")) == NULL)
    {
        puts("Erorr");
        return;
    }
    if ((des = fopen(arguments[2], "w")) == NULL)
    {
        puts("Erorr");
        fclose(src);
        return;
    }

    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, des);
    }
    fclose(src);
    fclose(des);
}
void get_dir()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./")) == NULL)
    {
        /* could not open directory */
        perror("");
        return;
    }
    /* print all the files and directories within directory */
    while ((ent = readdir(dir)) != NULL)
    {
        printf("%s ", ent->d_name);
    }
    puts("");
    closedir(dir);
}
void delete(char **arg)
{
    if (unlink(arg[1]) != 0)
        printf("-myShell: unlink: %s: No such file or directory\n", arg[1]);
}
void systemCall(char **arg)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("fork err\n");
        return;
    }
    if (pid == 0 && execvp(arg[0], arg) == -1)
        exit(1);
}
void mypipe(char **argv1, char **argv2)
{
    int fildes[2];
    if (fork() == 0)
    {
        pipe(fildes);
        if (fork() == 0)
        {
            /* first component of command line */
            close(STDOUT_FILENO);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            /* stdout now goes to pipe */
            /* child process does command */
            execvp(argv1[0], argv1);
        }
        /* 2nd command component of command line */
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        /* standard input now comes from pipe */
        execvp(argv2[0], argv2);
    }
}