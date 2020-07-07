#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = fork();
    int y = fork();
    printf("hello: %d %d\n", x, y);
    return 0;
}
