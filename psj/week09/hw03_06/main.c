#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_SENTENCE_LENGTH 100

int main(void) {
    for (int i = 0; i < 5; i += 1) {
        if (fork() == 0) {
            printf("command> ");
            char buf[MAX_SENTENCE_LENGTH + 1];
            fgets(buf, MAX_SENTENCE_LENGTH, stdin);
            buf[strlen(buf) - 1] = '\0';
            char* argv[MAX_SENTENCE_LENGTH];
            int idx = 0;
            argv[idx] = strtok(buf, " ");
            while (argv[idx] != NULL) {
                idx += 1;
                argv[idx] = strtok(NULL, " ");
            }
            execve(argv[0], argv, NULL);
        } else {
            wait(NULL);
        }
    }
    return 0;
}
