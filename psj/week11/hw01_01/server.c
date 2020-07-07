#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define LISTEN_BACKLOG 5
#define SERV_ADDR "165.246.38.152"
#define SERV_PORT 13579

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
    int cfd = accept(sfd, (struct sockaddr*) &cli_addr, &cli_addr_len);
    if (cfd == -1) {
        perror("Fail to accept");
        exit(EXIT_FAILURE);
    }
    printf("Client socket(cfd=%d) is accepted.\n", cfd);

    char buf[BUFFER_SIZE];
    int chunk = read(cfd, buf, BUFFER_SIZE - 1);
    buf[chunk] = '\0';
    printf("receive: %s\n", buf);

    fgets(buf, BUFFER_SIZE - 1, stdin);
    buf[strlen(buf) - 1] = '\0';
    write(cfd, buf, strlen(buf));

    close(cfd);
    close(sfd);
    return 0;
}
