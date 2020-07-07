#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define LISTEN_BACKLOG 5
#define MAX_FD_COUNT 50
#define SERV_ADDR "165.246.38.152"
#define SERV_PORT 13579

void handle_protocol(int fd, fd_set* set, int recv_count);

int main(void) {
    printf("Hi, I am the server.\n");

    struct sockaddr_in serv_addr, cli_addr;
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
    printf("Server socket(sfd=%d) is created.\n", sfd);

    if (bind(sfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        perror("Fail to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sfd, LISTEN_BACKLOG) == -1) {
        perror("Fail to listen");
        exit(EXIT_FAILURE);
    }

    socklen_t cli_addr_len = sizeof(cli_addr);

    fd_set read_fds, temp_fds;
    FD_ZERO(&read_fds);
    FD_SET(sfd, &read_fds);

    int recv_counts[MAX_FD_COUNT] = { 0 };

    while (1) {
        temp_fds = read_fds;
        select(MAX_FD_COUNT, &temp_fds, NULL, NULL, NULL);
        for (int fd = 0; fd < MAX_FD_COUNT; fd += 1) {
            if (FD_ISSET(fd, &temp_fds)) {
                if (fd == sfd) {
                    int cfd = accept(sfd, (struct sockaddr*) &cli_addr, &cli_addr_len);
                    if (cfd == -1) {
                        perror("Fail to accept");
                        exit(EXIT_FAILURE);
                    }
                    printf("Client socket(cfd=%d) is accepted.\n", cfd);
                    FD_SET(cfd, &read_fds);
                } else {
                    recv_counts[fd] += 1;
                    handle_protocol(fd, &read_fds, recv_counts[fd]);
                }
            }
        }
    }
    return 0;
}

void handle_protocol(int fd, fd_set* set, int recv_count) {
    char buf[BUFFER_SIZE];
    int chunk = read(fd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("receive(cfd=%d): %s\n", fd, buf);

    if (strcmp(buf, "ping") == 0 && recv_count == 1) {
        write(fd, "pong", 4);
        printf("send(cfd=%d): pong\n", fd);
    } else if (strcmp(buf, "pang") == 0 && recv_count == 2) {
        write(fd, "pung", 4);
        printf("send(cfd=%d): pung\n", fd);
    } else {
        write(fd, "Invalid input to protocol.", 26);
        fprintf(stderr, "Invalid input to protocol.\n");
    }

    if (recv_count == 2) {
        printf("Client socket(cfd=%d) is closed.\n", fd);
        close(fd);
        FD_CLR(fd, set);
    }
}
