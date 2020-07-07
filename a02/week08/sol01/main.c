#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int main(int argc, char* argv[]) {
    if (argc == 3) {
        int in_fd = open(argv[1], O_RDONLY);
        int out_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
        if (in_fd == -1 || out_fd == -1) {
            perror("Fail to open");
            exit(EXIT_FAILURE);
        }
        char buf[BUFFER_SIZE];
        int chunk;
        while ((chunk = read(in_fd, buf, BUFFER_SIZE)) > 0) {
            write(out_fd, buf, chunk);
        }
        close(in_fd);
        close(out_fd);
    } else {
        fprintf(stderr, "Invalid arguments\n");
    }
    return 0;
}
