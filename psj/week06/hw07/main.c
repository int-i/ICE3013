#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int x, y;
    char buf[20];

    x = open(argv[1], O_RDONLY);
    if (x == -1) {
        perror("Fail to open");
        exit(EXIT_FAILURE);
    }
    for (;;) {
        y = read(x, buf, 20);
        if (y == 0)
            break;
        write(1, buf, y);
    }
    return 0;
}
