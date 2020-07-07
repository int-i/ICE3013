#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_WRITE_COUNT 8

int main(void) {
    int old_fd = open("f2", O_WRONLY | O_CREAT | O_TRUNC, 00777);
    printf("old_fd=%d\n", old_fd);

    close(STDOUT_FILENO);

    int new_fd = dup(old_fd);
    printf("old_fd=%d, new_fd=%d\n", old_fd, new_fd);
    write(STDOUT_FILENO, "hi there", MAX_WRITE_COUNT);

    close(old_fd);
    close(new_fd);
    return 0;
}
