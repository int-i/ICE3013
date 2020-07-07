#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUBCHUNK2_SIZE_OFFSET 40
#define DATA_OFFSET 44

int main(void) {
    int subchunk2_size;

    int fd = open("sw2.wav", O_RDWR);
    lseek(fd, SUBCHUNK2_SIZE_OFFSET, SEEK_SET);
    read(fd, &subchunk2_size, 4);

    int replaced_byte_count = subchunk2_size / 2;
    lseek(fd, replaced_byte_count, SEEK_CUR);
    void* buf = malloc(replaced_byte_count);
    read(fd, buf, replaced_byte_count);

    lseek(fd, DATA_OFFSET, SEEK_SET);
    write(fd, buf, replaced_byte_count);
    free(buf);

    close(fd);
    return 0;
}
