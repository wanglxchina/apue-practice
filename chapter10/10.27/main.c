#include <stdio.h>
#include <errno.h>
#include <sys/signal.h>
#include <unistd.h>
int my_system(const char* cmdstring)
{
    pid_t pid;
    int status;
    struct sigaction ignore,saveintr,savequit;
    sigset_t new_mask,save_mask;
    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    if(sigaction(SIGINT,&ignore,&saveintr) < 0)
    {
        return -1;
    }
    if(sigaction(SIGQUIT,&ignore,&savequit) < 0)
    {
        return -1;
    }

    sigemptyset(&new_mask);
    sigaddset(&new_mask,SIGCHLD);
    if(sigprocmask(SIG_BLOCK,&new_mask,&save_mask) < 0)
    {
        return -1;
    }

    if((pid = fork()) < 0)
    {
        return -1;
    }
    else if(pid == 0)
    {
        sigaction(SIGINT,&saveintr,NULL);
        sigaction(SIGQUIT,&savequit,NULL);
        sigprocmask(SIG_SETMASK,&save_mask,NULL);
        execl("/bin/sh","sh","-c",cmdstring,(char*)0);
        _exit(127);
    }
    else
    {
        while(waitpid(pid,&status,0) < 0)
        {
            if(errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }

    if(sigaction(SIGINT,&saveintr,NULL) < 0)
    {
        return -1;
    }
    if(sigaction(SIGQUIT,&savequit,NULL) < 0)
    {
        return -1;
    }
    if(sigprocmask(SIG_SETMASK,&save_mask,NULL) <0 )
    {
        return -1;
    }
    return(status);

}

void sigint(int signo)
{
    printf("sigint capture\n");
}
int main(int argc,char *argv[])
{
    signal(SIGINT,sigint);
    my_system("ping 127.0.0.1");

    while(1)
    {
        sleep(1);
    }
    return 0;
}