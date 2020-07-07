#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define SERV_ADDR "165.246.38.152"
#define SERV_PORT 13579

int main(void) {
    printf("Hi, I am the client.\n");

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

    char buf[BUFFER_SIZE];
    printf("client => server: (Enter ping) ");
    fgets(buf, BUFFER_SIZE - 1, stdin);
    write(sfd, buf, strlen(buf) - 1);

    int chunk = read(sfd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("server => client: %s\n", buf);

    if (strcmp(buf, "pong") != 0) {
        fprintf(stderr, "Error occurred by the protocol.\n");
        close(sfd);
        exit(EXIT_FAILURE);
    }

    printf("client => server: (Enter pang) ");
    fgets(buf, BUFFER_SIZE - 1, stdin);
    write(sfd, buf, strlen(buf) - 1);

    chunk = read(sfd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("server => client: %s\n", buf);

    if (strcmp(buf, "pung. Enter your name.") != 0) {
        fprintf(stderr, "Error occurred by the protocol.\n");
        close(sfd);
        exit(EXIT_FAILURE);
    }

    printf("client => server: (Enter your name) ");
    fgets(buf, BUFFER_SIZE - 1, stdin);
    write(sfd, buf, strlen(buf) - 1);

    chunk = read(sfd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("server => client: %s\n", buf);

    if (strcmp(buf, "Enter your age.") != 0) {
        fprintf(stderr, "Error occurred by the protocol.\n");
        close(sfd);
        exit(EXIT_FAILURE);
    }

    printf("client => server: (Enter your age) ");
    fgets(buf, BUFFER_SIZE - 1, stdin);
    write(sfd, buf, strlen(buf) - 1);

    chunk = read(sfd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("server => client: %s\n", buf);

    if (strcmp(buf, "Enter your partner.") != 0) {
        fprintf(stderr, "Error occurred by the protocol.\n");
        close(sfd);
        exit(EXIT_FAILURE);
    }

    printf("client => server: (Enter your partner) ");
    fgets(buf, BUFFER_SIZE - 1, stdin);
    write(sfd, buf, strlen(buf) - 1);

    chunk = read(sfd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("server => client: %s\n", buf);

    if (strcmp(buf, "Process completed. Start chatting.") != 0) {
        fprintf(stderr, "Error occurred by the protocol.\n");
        close(sfd);
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) {
        while (1) {
            chunk = read(sfd, buf, BUFFER_SIZE - 1);
            if (chunk > 0) {
                buf[chunk] = '\0';
                printf("server => client: %s\n", buf);
            }
        }
    } else {
        while (1) {
            printf("client => server: (Chat) ");
            fgets(buf, BUFFER_SIZE - 1, stdin);
            write(sfd, buf, strlen(buf) - 1);
        }
    }

    close(sfd);
    return 0;
}
