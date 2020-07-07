#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x, y;
    x = getpid();
    y = getppid();
    printf("PID:%d, PPID:%d\n", x, y);
    for (;;); // to make this process alive
    return 0;
}
