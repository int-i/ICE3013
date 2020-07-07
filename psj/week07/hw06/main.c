#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = fork();
    if (x == 0) {
        printf("hello: %d\n", x);
    } else {
        printf("hi: %d \n", x);
    }
    return 0;
}
