#include <stdio.h>
#include <unistd.h>

int main(void) {
    execve("./ex01", NULL, NULL);
    printf("I am ex02\n");
    return 0;
}
