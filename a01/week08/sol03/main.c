#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    if (fork() == 0) {
        printf("child: %d\n", getpid());
        fflush(stdout);
    } else {
        int status;
        wait(&status);
        printf("parent: %d\n", getpid());
        fflush(stdout);
    }
    return 0;
}
