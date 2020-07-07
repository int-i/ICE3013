#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void show_file(char* fname);
void display_content(int x);

int main(int argc, char* argv[]) {
    show_file(argv[1]);
    return 0;
}

void show_file(char* fname) {
    int x;
    x = open(fname, O_RDONLY);
    if (x == -1) {
        perror("Fail to open");
        exit(EXIT_FAILURE);
    }
    display_content(x);
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
