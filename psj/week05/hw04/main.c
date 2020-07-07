#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SUBCHUNK2_SIZE_OFFSET 40

int main(void) {
    int subchunk2_size;

    int fd = open("sw2.wav", O_RDWR);
    lseek(fd, SUBCHUNK2_SIZE_OFFSET, SEEK_SET);
    read(fd, &subchunk2_size, 4);

    int removed_byte_count = subchunk2_size / 2;
    void* zerobuf = malloc(removed_byte_count);
    memset(zerobuf, 0, removed_byte_count);
    write(fd, zerobuf, removed_byte_count);
    free(zerobuf);

    close(fd);
    return 0;
}
