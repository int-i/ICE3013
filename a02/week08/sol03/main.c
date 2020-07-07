#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 3; i += 1) {
        if (fork() == 0) {
            printf("Child(%d)'s PID: %d\n", i, getpid());
            fflush(stdout);
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}
