#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    if (daemon(0, 1)) {
        perror("daemon");
        exit(EXIT_FAILURE);
    }

    printf("%d\n", getpid());

    fcloseall();

    while (1) sleep(2);

    return 0;
}
