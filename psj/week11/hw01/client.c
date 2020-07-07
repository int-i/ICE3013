#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SERV_TCP_PORT 13579
#define SERV_ADDR "165.246.38.152"

int main(void) {
    int x, y;
    struct sockaddr_in serv_addr;
    char buf[50];
    printf("Hi, I am the client\n");

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_ADDR);
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    //open a tcp socket
    if ((x = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket creation error\n");
        exit(1);
    }
    printf("socket opened successfully. socket num is %d\n", x);

    //connect to the server
    if (connect(x, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("can't connect to the server\n");
        exit(1);
    }
    // send msg to the server
    printf("now i am connected to the server. enter a string to send\n");
    scanf("%s", buf);
    write(x, buf, strlen(buf));
    // read from server
    printf("now reading from server\n");
    y = read(x, buf, 50);
    buf[y] = 0;
    printf("from server: %s\n", buf);
    close(x); // disconect the communication

    return 0;
}
