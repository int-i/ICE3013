#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = fork();
    printf("hello: %d\n", x);
    int y = fork();
    printf("hello: %d\n", y);
    return 0;
}
