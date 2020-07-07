#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 20

void print_file(char* filename);

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        print_file(argv[1]);
    }
    if (argc >= 3) {
        print_file(argv[2]);
    }
    return 0;
}

void print_file(char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Fail to open");
        exit(EXIT_FAILURE);
    }
    char buf[BUFFER_SIZE];
    int chunk;
    while ((chunk = read(fd, buf, BUFFER_SIZE))) {
        write(STDOUT_FILENO, buf, chunk);
    }
    close(fd);
}
