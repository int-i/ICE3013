#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 50
#define MAX_READ_COUNT 5

int main(void) {
    int old_fd = open("f1", O_RDONLY);
    int new_fd = dup(old_fd);

    printf("old_fd=%d, new_fd=%d\n", old_fd, new_fd);

    char buf[BUFFER_SIZE];
    int chunk = read(old_fd, buf, MAX_READ_COUNT);
    buf[chunk] = '\0';
    printf("buf=%s\n", buf);
    chunk = read(new_fd, buf, MAX_READ_COUNT);
    buf[chunk] = '\0';
    printf("buf=%s\n", buf);

    close(old_fd);
    close(new_fd);
    return 0;
}
