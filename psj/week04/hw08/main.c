#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int main(void) {
    int fd1 = open("hw4", O_RDONLY);
    int fd2 = open("cphw4", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    char buf[BUFFER_SIZE];
    int chunk;
    while ((chunk = read(fd1, buf, BUFFER_SIZE))) {
        write(fd2, buf, chunk);
    }
    close(fd1);
    close(fd2);
    return 0;
}
