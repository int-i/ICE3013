#include <signal.h>
#include <stdio.h>

void foo(int signum) {
    printf("I am ok\n");
}

int main(void) {
    signal(SIGHUP, foo);
    signal(SIGINT, foo);
    signal(SIGTERM, foo);
    for (;;);
    return 0;
}
