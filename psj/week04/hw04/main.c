#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x, y;
    char buf[20];
    x = open("f2", O_RDONLY, 00777); // open f2 for reading
    for (;;) {
        y = read(x, buf, 1); // read next byte
        if (y == 0)
            break; // we read all, exit the loop
        printf("%x %d %c\n", buf[0], buf[0], buf[0]); // display
    }
    return 0;
}
