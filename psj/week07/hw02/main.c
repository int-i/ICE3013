#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x = fork();
    printf("hello\n");
    for (;;);
    return 0;
}
