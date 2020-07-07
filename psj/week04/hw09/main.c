#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 20
#define MAX_FILENAME_LENGTH 20

int main(void) {
    printf("Enter src file name\n");
    char src[MAX_FILENAME_LENGTH];
    fgets(src, MAX_FILENAME_LENGTH, stdin);
    src[strlen(src) - 1] = '\0';

    printf("Enter dest file name\n");
    char dest[MAX_FILENAME_LENGTH];
    fgets(dest, MAX_FILENAME_LENGTH, stdin);
    dest[strlen(dest) - 1] = '\0';

    int fd1 = open(src, O_RDONLY);
    int fd2 = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 00777);
    char buf[BUFFER_SIZE];
    int chunk;
    while ((chunk = read(fd1, buf, BUFFER_SIZE))) {
        write(fd2, buf, chunk);
    }
    close(fd1);
    close(fd2);

    printf("%s is copied into %s successfully.\n", src, dest);
    return 0;
}
