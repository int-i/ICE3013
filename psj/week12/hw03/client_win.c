#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUFFER_SIZE 100
#define SERV_ADDR "165.246.38.152"
#define SERV_PORT 13579

int main(void) {
    printf("Hi, I am the client.\n");

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

    char buf[BUFFER_SIZE];
    printf("Enter a string to send to server: ");
    fgets(buf, BUFFER_SIZE, stdin);
    buf[strlen(buf) - 1] = '\0';
    int bytesSent = send(connectSocket, buf, (int) strlen(buf), 0);
    printf("Bytes Sent: %d\n", bytesSent);

    int bytesReceived = recv(connectSocket, buf, BUFFER_SIZE - 1, 0);
    buf[bytesReceived] = 0;
    printf("Received: %s\n", buf);

    closesocket(connectSocket);
    WSACleanup();
    return 0;
}
