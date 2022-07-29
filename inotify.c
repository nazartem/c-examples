#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/inotify.h>
#include "log.h"

#define EPOLL_RUN_TIMEOUT       -1
#define MAX_EPOLL_EVENTS        10
#define MAX_INOTIFY_BUF_SIZE    1024

int main(int argc, char **argv)
{
    int result;
    // inotify для отслеживания изменения /home/nazaryap/Dev/C/Test/
    int inotifyFD = inotify_init();
    if(inotifyFD < 0)
    {
        LOG("Couldn't initialize inotify\n");
    }

    int inotifyWatch = inotify_add_watch(inotifyFD, "/home/nazaryap/Dev/C/Test/", IN_MODIFY);
    if (inotifyWatch < 0)
    {
        printf("Couldn't add watch to /home/nazaryap/Dev/C/Test/");
    }
    char inotifyBuf[1024];

    // epoll для отслеживания срабатывания inotify
    struct epoll_event epollConfig;
    struct epoll_event epollEvent[MAX_EPOLL_EVENTS];
    int epollFD = epoll_create(sizeof(inotifyFD));

    epollConfig.events = EPOLLIN | EPOLLET | EPOLLOUT;
    epollConfig.data.fd = inotifyFD;
    // add our listening socket into epoll
    result = epoll_ctl(epollFD, EPOLL_CTL_ADD, inotifyFD, &epollConfig);
    if(result < 0)
    {
        LOG("Error while inotify epoll regisration\n");
    }


    while (1)
    {
        result = epoll_wait(epollFD, epollEvent, MAX_EPOLL_EVENTS, EPOLL_RUN_TIMEOUT);
        read(inotifyFD, &inotifyBuf, MAX_INOTIFY_BUF_SIZE);
        LOG("config modified!\n");
    }
    return 0;
}
