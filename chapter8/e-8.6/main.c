#include <unistd.h>
#include <stdio.h>
#ifdef SOLARIS
#define PSCMD "ps -a -o pid,ppid,s,tty,comm"
#else
#define PSCMD "ps -o pid,ppid,state,tty,command"
#endif
int main(int argc,char *argv[])
{
    pid_t pid;
    if((pid = fork()) < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
       exit(0);
    }

    sleep(4);
    system("ps -alf ");

    exit(0);
}
