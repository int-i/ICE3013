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
#define STATE_UNDEFINED 0
#define STATE_INIT 1
#define STATE_PROTOCOL 2
#define STATE_CHAT 3

void handle_protocol(int fd, fd_set* set, int* states);

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

    int states[MAX_FD_COUNT] = { STATE_UNDEFINED };

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
                    states[cfd] = STATE_INIT;
                    printf("Client socket(cfd=%d) is accepted.\n", cfd);
                    FD_SET(cfd, &read_fds);
                } else {
                    handle_protocol(fd, &read_fds, states);
                }
            }
        }
    }
    return 0;
}

void handle_protocol(int fd, fd_set* set, int* states) {
    char buf[BUFFER_SIZE];
    int chunk = read(fd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("client(cfd=%d) => server: %s\n", fd, buf);

    int state = states[fd];
    if (state == STATE_INIT && strcmp(buf, "ping") == 0) {
        write(fd, "pong", 4);
        printf("server => client(cfd=%d): pong\n", fd);
        states[fd] += 1;
    } else if (state == STATE_PROTOCOL && strcmp(buf, "pang") == 0) {
        write(fd, "pung. Process completed. Start chatting.", 40);
        printf("server => client(cfd=%d): pung. Process completed. Start chatting.\n", fd);
        states[fd] += 1;
    } else if (state == STATE_CHAT && strlen(buf) > 0) {
        for (int other_fd = 0; other_fd < MAX_FD_COUNT; other_fd += 1) {
            if (fd != other_fd && states[other_fd] == STATE_CHAT) {
                write(other_fd, buf, strlen(buf));
                printf("server => client(cfd=%d): %s\n", other_fd, buf);
            }
        }
    } else {
        write(fd, "Invalid input to protocol.", 26);
        fprintf(stderr, "Invalid input to protocol.\n");
        printf("Client socket(cfd=%d) is closed.\n", fd);
        close(fd);
        FD_CLR(fd, set);
    }
}
