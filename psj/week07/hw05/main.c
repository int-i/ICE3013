#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = fork();
    printf("hello: %d\n", x);
    for (;;); // make the parent and child alive
    return 0;
}
