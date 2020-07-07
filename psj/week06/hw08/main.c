#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void display_content(int x);

int main(int argc, char* argv[]) {
    int x;
    x = open(argv[1], O_RDONLY);
    if (x == -1) {
        perror("Fail to open");
        exit(EXIT_FAILURE);
    }
    display_content(x);
    return 0;
}

void display_content(int x) {
    char buf[20];
    int y;
    for (;;) {
        y = read(x, buf, 20);
        if (y == 0)
            break;
        write(1, buf, y);
    }
}
