#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "ap.h"

void * heartbeatTask(void * arg)
{
    int fd = *(int *)arg;
    for(;;)
    {
        sendHeartbeat(fd);
        sleep(1);
    }

    return NULL;
}

int main(void)
{
    int fd = initSerialPort();
    if(fd < 0)
    {
        return 1;
    }

    pthread_t heartbeatThread;
    int result = pthread_create(&heartbeatThread, NULL, heartbeatTask, &fd);
    if(result != 0)
    {
        printf("[AP LOG] Thread 생성 실패\n");
        close(fd);
        return 1;
    }

    for(;;)
    {
        char message[50];
        printf("[AP Command] Command 입력 : ");
        scanf("%s", message);
        sendMessage(fd, message);
    }


}