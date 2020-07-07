#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILENAME_LENGTH 20

int main() {
    printf("Enter file name to split\n");
    char filename[MAX_FILENAME_LENGTH];
    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    size_t len = strlen(filename);
    filename[len - 1] = '\0';

    int fd = open(filename, O_RDONLY);

    struct stat sb;
    fstat(fd, &sb);
    long long total_size = sb.st_size;
    long long segment_size = total_size / 3;

    printf("%s is split into ", filename);
    char* buf = (char*) malloc(sizeof(char) * segment_size);
    int chunk;
    for (int i = 1; i <= 3; i += 1) {
        filename[len - 1] = (char) (i + '0');
        int segment_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00777);
        if (i != 3) {
            chunk = read(fd, buf, segment_size);
            printf("%s, ", filename);
        } else {
            chunk = read(fd, buf, total_size - segment_size * 2);
            printf("and %s.\n", filename);
        }
        write(segment_fd, buf, chunk);
        close(segment_fd);
    }

    close(fd);
    return 0;
}
