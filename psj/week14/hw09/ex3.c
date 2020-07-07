#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void wait_parent() {
    wait(NULL);
}

int main(void) {
    signal(SIGCHLD, wait_parent);
    if (fork() == 0) {
        for (;;);
    } else {
        if (fork() == 0) {
            for (;;);
        }
    }
    for (;;);
    return 0;
}
