#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define SERV_ADDR "165.246.13.108" // www.inha.ac.kr
#define SERV_PORT 80

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

    char* request = "GET / HTTP/1.1\r\nHOST: www.inha.ac.kr\r\n\r\n";
    write(sfd, request, strlen(request));

    char buf[BUFFER_SIZE];
    int chunk;
    while ((chunk = recv(sfd, buf, BUFFER_SIZE - 1, 0)) > 0) {
        buf[chunk] = '\0';
        printf("%s", buf);
    }

    close(sfd);
    return 0;
}
