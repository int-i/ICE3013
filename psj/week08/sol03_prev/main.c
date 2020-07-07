#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc == 2) {
        DIR* dirp = opendir("./");
        if (dirp == NULL) {
            perror("Fail to open directory");
            exit(EXIT_FAILURE);
        }
        struct dirent* dp;
        while ((dp = readdir(dirp)) != NULL) {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
                int fd = open(dp->d_name, O_RDONLY);
                if (fd == -1) {
                    continue;
                }
                struct stat s;
                fstat(fd, &s);
                char* buf = malloc(sizeof(char) * s.st_size);
                read(fd, buf, s.st_size);
                close(fd);
                fd = open(dp->d_name, O_WRONLY | O_CREAT | O_TRUNC, 00777);
                for (int i = 0; i < s.st_size; i += 1) {
                    if (buf[i] != argv[1][0]) {
                        write(fd, &buf[i], 1);
                    }
                }
                free(buf);
                close(fd);
            }
        }
        closedir(dirp);
    } else {
        fprintf(stderr, "Invalid arguments\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
