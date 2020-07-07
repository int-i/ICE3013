#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    if (fork() == 0) {
        char* argv[] = {
            "/bin/ls",
            "-l",
            NULL
        };
        execve(argv[0], argv, NULL);
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL);
        printf("job done\n");
    }
    return 0;
}
