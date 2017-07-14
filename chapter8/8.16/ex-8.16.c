#include <sys/wait.h>
#include <unistd.h> //execle execlp
#include <stdio.h>  //printf
#include <stdlib.h> // exit
char *env_init[] = { "USER=unknown","PATH=/tmp",NULL};
int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
        if(execle("/home/kamui/bin/echoall","echoall","myarg1","MY ARG2",(char*)0,env_init) < 0)
        {
            printf("execle error\n");
        }
    }

    if(waitpid(pid,NULL,0) < 0)
    {
        printf("waitpid error\n");
    }
    printf("\n\n");
    if((pid = fork()) < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
        if(execlp("echoall","echoall","only 1 arg",(char*)0) < 0)
        {
            printf("excelp error\n");
        }
    }
    exit(0);
}
