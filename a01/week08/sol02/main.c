#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUBCHUNK2_SIZE_OFFSET 40

int main(int argc, char* argv[]) {
    if (argc == 2) {
        int fd = open(argv[1], O_RDWR);
        if(fd==-1) {
            perror("Fail to open");
            exit(EXIT_FAILURE);
        }

        int subchunk2_size;
        lseek(fd, SUBCHUNK2_SIZE_OFFSET, SEEK_SET);
        read(fd, &subchunk2_size, 4);

        int replaced_byte_count = subchunk2_size / 2 - 2500;
        void* buf = malloc(replaced_byte_count);
        read(fd, buf, replaced_byte_count);

        write(fd, buf, replaced_byte_count);
        free(buf);

        close(fd);
    } else {
        fprintf(stderr, "Invalid arguments\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
