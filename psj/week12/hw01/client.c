#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 100
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

    char* init_request = "hello";
    write(sfd, init_request, strlen(init_request));
    printf("client => server: hello\n");

    while (1) {
        char buf[BUFFER_SIZE];
        int chunk;

        printf("server => client: ");
        fflush(stdout);
        while (1) {
            chunk = read(sfd, buf, BUFFER_SIZE);
            if (buf[chunk - 1] == -1) {
                write(STDOUT_FILENO, buf, chunk - 1);
                break;
            } else {
                write(STDOUT_FILENO, buf, chunk);
            }
        }
        printf("\n");

        printf("client => server: ");
        fgets(buf, BUFFER_SIZE - 1, stdin);
        buf[strlen(buf) - 1] = '\0';
        write(sfd, buf, strlen(buf));

        if (strcmp(buf, "bye") == 0) {
            break;
        }
    }

    close(sfd);
    return 0;
}
