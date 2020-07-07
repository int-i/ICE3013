#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_SENTENCE_LENGTH 100

int main(void) {
    while (1) {
        char buf[MAX_SENTENCE_LENGTH];
        printf("$ ");
        scanf("%s", buf);

        if (strcmp(buf, "exit") == 0) {
            break;
        }

        char* argv[] = {
            buf,
            NULL
        };

        if (fork() == 0) {
            printf("I am child to execute %s\n", buf);
            if (execve(buf, argv, NULL) < 0) {
                perror("Fail to execute");
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            wait(&status);
        }
    }
    return 0;
}
