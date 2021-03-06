#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pid;
    for (int i = 0; i < 5; i += 1) {
        if ((pid = fork()) == 0) { // child
            for (int k = 0; k < 10; k += 1) {
                printf("%d-th child running %d-th iteration(pid: %d)\n", i, k, getpid());
                fflush(stdout); // to make printf work immediately
                sleep(1); // sleep 1 second
            }
        }
    }
    // now parent
    printf("parent exits\n");
    return 0;
}
