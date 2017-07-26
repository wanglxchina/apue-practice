#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <syscall.h> //__NR_gettid
#include <errno.h>
#include <pthread.h>
#define gettid() syscall(__NR_gettid)
void sig_func(int sig_no)
{
    printf("%s pid is %d:%d\n",__func__,getpid(),gettid());
}
void sig_func2(int sig_no)
{
    printf("%s pid is %d:%d#####\n",__func__,getpid(),gettid());
}
int g_flag = 0;
void* thread_1(void* param)
{
    printf("%s pid is %d:%d\n",__func__,getpid(),gettid());
     if(signal(SIGINT,sig_func2) == SIG_ERR)
    {
        printf("signal errno:%d\n",errno);
    }
    printf("%s after signal\n",__func__);
     int i = 10;
    while(i-- > 0)
    {
        usleep(500*1000);
        printf("%d\n",i);
    }
    pause();
    printf("%s exit\n",__func__);
    return NULL;
}

void* thread_2(void* param)
{
    printf("%s pid is %d:%d\n",__func__,getpid(),gettid());
     if(signal(SIGINT,sig_func) == SIG_ERR)
    {
        printf("signal errno:%d\n",errno);
    }
    printf("%s after signal\n",__func__);
     int i = 10;
    while(i-- > 0)
    {
        usleep(500*1000);
        printf("%d\n",i);
    }
    pause();
    printf("%s exit\n",__func__);
    return NULL;
}


int main(int argc,char *argv[])
{
    sigset_t newmask,oldmask;

    sigemptyset(&newmask);
    sigaddset(&newmask,SIGINT);
    sigaddset(&newmask,SIGQUIT);
    pthread_t thread_id;
    pthread_create(&thread_id,NULL,thread_1,NULL);
    pthread_create(&thread_id,NULL,thread_2,NULL);
    printf("%s pid is %d:%d\n",__func__,getpid(),gettid());
    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) <0)
    {
        printf("SIG_BLOCK error\n");
    }
    int i = 10;
    while(i-- > 0)
    {
        usleep(500*1000);
        printf("%d\n",i);
    }
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL) <0)
    {
        printf("SIG_BLOCK error\n");
    }
    /*if(signal(SIGINT,sig_func) == SIG_ERR)
    {
        printf("signal errno:%d\n",errno);
    }
    printf("%s after signal\n",__func__);*/
    pause();
    printf("%s exit\n",__func__);
    return 0;
}