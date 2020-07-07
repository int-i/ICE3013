#include <stdio.h>
#include <string.h>

int main(void) {
    char *x, *y, *z;
    x = "hello";
    y = "hi";
    z = "bye";
    printf("%s %s %s\n", x, y, z);
    printf("%p %p %p\n", x, y, z);
    return 0;
}
