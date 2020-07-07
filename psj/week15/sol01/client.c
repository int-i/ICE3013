#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define MAX_FILENAME_LENGTH 100
#define SERV_ADDR "165.246.38.152"
#define SERV_PORT 13579

int main(void) {
    printf("Hi, I am the FTP client.\n");

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    if (inet_aton(SERV_ADDR, &serv_addr.sin_addr) == 0) {
        fprintf(stderr, "Invalid Address\n");
        exit(EXIT_FAILURE);
    }

    int sfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("Fail to create");
        exit(EXIT_FAILURE);
    }
    printf("Socket(sfd=%d) is created.\n", sfd);

    if (connect(sfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        perror("Fail to connect");
        exit(EXIT_FAILURE);
    }

    printf("client => server: hello\n");
    write(sfd, "hello", 5);

    char buf[BUFFER_SIZE];
    int chunk = read(sfd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("server => client: %s\n", buf);

    if (strcmp(buf, "file name?") != 0) {
        fprintf(stderr, "Error occurred by the protocol.\n");
        close(sfd);
        exit(EXIT_FAILURE);
    }

    char filename[MAX_FILENAME_LENGTH];
    printf("client => server: (Enter file name) ");
    fgets(buf, BUFFER_SIZE - 1, stdin);
    buf[strlen(buf) - 1] = '\0';
    strcpy(filename, buf);
    write(sfd, buf, strlen(buf));

    chunk = read(sfd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("server => client: %s\n", buf);

    if (strcmp(buf, "ready?") != 0) {
        fprintf(stderr, "Error occurred by the protocol.\n");
        close(sfd);
        exit(EXIT_FAILURE);
    }

    printf("client => server: (Enter yes) ");
    fgets(buf, BUFFER_SIZE - 1, stdin);
    write(sfd, buf, strlen(buf) - 1);

    int res_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 00777);
    if (res_fd == -1) {
        fprintf(stderr, "Fail to open the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("server => client: ");
    fflush(stdout);
    while (1) {
        chunk = read(sfd, buf, BUFFER_SIZE);
        if (buf[chunk - 1] == -1) {
            write(res_fd, buf, chunk - 1);
            write(STDOUT_FILENO, buf, chunk - 1);
            break;
        } else {
            write(res_fd, buf, chunk);
            write(STDOUT_FILENO, buf, chunk);
        }
    }
    printf("\n");

    close(res_fd);

    close(sfd);
    return 0;
}
