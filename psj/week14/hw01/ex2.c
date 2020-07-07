#include <signal.h>
#include <stdio.h>

void foo(int signum) {
    printf("I am ok\n");
}

int main(void) {
    signal(SIGINT, foo);
    for (;;);
    return 0;
}
