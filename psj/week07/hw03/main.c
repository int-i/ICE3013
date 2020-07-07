#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = fork();
    printf("hello. my pid is %d\n", getpid());
    printf("and my parent pid is %d\n", getppid());
    for (;;);
    return 0;
}
