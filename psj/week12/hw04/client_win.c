#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUFFER_SIZE 100
#define SERV_ADDR "165.246.38.152"
#define SERV_PORT 13579

int main() {
    WORD wVersionRequired = MAKEWORD(2, 2);
    WSADATA wsaData;

    int result = WSAStartup(wVersionRequired, &wsaData);
    if (result != 0) {
        printf("WSAStartup failed with error: %d\n", result);
        return 1;
    }

    SOCKADDR_IN servAddr;
    ZeroMemory(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_ADDR, &servAddr.sin_addr);

    SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    if (connect(connectSocket, (SOCKADDR*) &servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
        printf("Unable to connect to server!\n");
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    char* init_request = "hello";
    send(connectSocket, init_request, (int) strlen(init_request), 0);
    printf("client => server: hello\n");

    char buf[BUFFER_SIZE];
    int chunk = recv(connectSocket, buf, BUFFER_SIZE - 1, 0);
    buf[chunk] = '\0';
    printf("server => client: %s\n", buf);
    recv(connectSocket, buf, 1, 0); // consume EOF character

    while (1) {
        printf("client => server: ");
        fgets(buf, BUFFER_SIZE - 1, stdin);
        buf[strlen(buf) - 1] = '\0';
        send(connectSocket, buf, strlen(buf), 0);

        if (strcmp(buf, "bye") == 0) {
            break;
        }

        FILE* stream = fopen(buf, "w");
        while (1) {
            chunk = recv(connectSocket, buf, BUFFER_SIZE - 1, 0);
            if (buf[chunk - 1] == -1) {
                buf[chunk - 1] = '\0';
                fprintf(stream, "%s", buf);
                break;
            } else {
                buf[chunk] = '\0';
                fprintf(stream, "%s", buf);
            }
        }
        fclose(stream);
        printf("server => client: File Downloaded.\n");
    }

    closesocket(connectSocket);
    WSACleanup();
    return 0;
}
