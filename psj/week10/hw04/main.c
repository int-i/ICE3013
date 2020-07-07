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
        fgets(buf, MAX_SENTENCE_LENGTH, stdin);
        buf[strlen(buf) - 1] = '\0';

        if (strcmp(buf, "exit") == 0) {
            break;
        }

        char* argv[MAX_SENTENCE_LENGTH];
        int argc = 0;
        argv[argc] = strtok(buf, " ");
        while (argv[argc] != NULL) {
            argc += 1;
            argv[argc] = strtok(NULL, " ");
        }

        if (fork() == 0) {
            printf("I am child to execute %s\n", buf);
            if (execve(argv[0], argv, NULL) < 0) {
                perror("Fail to execute");
                exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL);
        }
    }
    return 0;
}
