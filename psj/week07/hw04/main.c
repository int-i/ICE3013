#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = fork();
    printf("hello: %d\n", x);
    for (;;);
    return 0;
}
