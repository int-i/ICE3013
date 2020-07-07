# Network programming 2

## Homework

### 1. Implement simple FTP server and client. If the client doesn't follow the protocol, the server should stop the communication.

See [HW 1](./hw01/)

Server:

```bash
$ ./server
Hi, I am the FTP server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
client => server: hello
server => client: What file do you want?
client => server: f1
server => client: I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.

client => server: client.c
server => client: #include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
...
    close(sfd);
    return 0;
}


client => server: bye
```

Client:

```bash
$ ./client
Hi, I am the FTP client.
Socket(sfd=3) is created.
client => server: hello
server => client: What file do you want?
client => server: f1
server => client: I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.

client => server: client.c
server => client: #include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
...
    close(sfd);
    return 0;
}


client => server: bye
```

`read`와 `write` 함수를 이용해 Simple FTP를 구현했다.

클라이언트는 프로그램 시작시 자동으로 서버에 "hello"를 전송한다.
서버는 클라이언트에게 "hello"를 수신받으면 "What file do you want?"를 전송한다.

그 다음 파일 이름을 입력 받으면 `open`을 이용해 파일을 열고 내용을 읽어 클라이언트에게 전송한다.

파일 내용이 `BUFFER_SIZE`보다 클 때를 위해 '-1'을 EOF 문자로 설정해 클라이언트는 '-1'이 들어올 때까지 서버에서 문자열을 읽어들인다.

파일이 존재하지 않는다면 "Fail to open the file."을 전송한다.

### 2. Modify your FTP server such that it can handle multiple clients at the same time.

See [HW 2](./hw02/server.c) with [HW 1 Client](./hw01/client.c)

Server:

```bash
$ ./server
Hi, I am the FTP server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
client => server: hello
server => client: What file do you want?
client => server: f1
server => client: I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.

Client socket(cfd=4) is accepted.
client => server: hello
server => client: What file do you want?
client => server: f2
server => client: Fail to open the file.
client => server: bye
client => server: f1
server => client: I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.

client => server: bye
```

Client 1:

```bash
$ ./client
Hi, I am the FTP client.
Socket(sfd=3) is created.
client => server: hello
server => client: What file do you want?
client => server: f1
server => client: I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.

client => server: bye
```

Client 2:

```bash
$ ./client
Hi, I am the FTP client.
Socket(sfd=3) is created.
client => server: hello
server => client: What file do you want?
client => server: f2
server => client: Fail to open the file.
client => server: f1
server => client: I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.

client => server: bye
```

`fork` 함수로 새로운 연결이 생길 때마다 자식 프로세스를 만들어 클라이언트 소켓의 연결을 만들어주었다.

위와 같이 여러 개의 클라이언트가 연결해도 잘 작동한다.

### 3. Write a client in your PC as follows and let it talk to the server program in the lab server. To compile the client program:

1. Make an empty c++ project and copy the code given below.
2. Adjust the server IP and port number
3. Select "project>project property>manifest tools>input and output>include manifest" and set "No".
4. Add "ws2_32.lib" in "project>project property>link>input>additional dependencies"
5. Select "build>Solution" Build
6. You should see "Success 1" at the bottom of the compile window.

See [HW 3](./hw03/client_win.c) with [Week 11 HW 1-1 Server](../week11/hw01_01/server.c)

Server(Linux):

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
receive: Hi, Linux
Hi, Windows
```

Client(Windows 10):

```text
Hi, I am the client.
Enter a string to send to server: Hi, Linux
Bytes Sent: 9
Received: Hi, Windows
```

Windows에서는 시스템 콜 함수를 사용할 수 없다.
따라서 `fopen`과 같은 라이브러리 함수를 사용해야 한다.

`recv`와 `send`는 추가적으로 마지막 인자 `flags`를 받는데 이를 0으로 설정하면 아무 값도 설정하지 않은 것(기본값)을 취급된다.

또한, Windows의 소켓 프로그래밍에서는 `WSAStartup`와 `WSACleanup`을 프로그램 시작과 끝에 호출해야 한다.

### 4. Write an FTP client in your PC and let it talk to the FTP server you made in problem 5). Use this client to download a file from the lab server.

See [HW 4](./hw04/client_win.c) with [HW 2 Server](./hw02/server.c)

Server(Linux):

```bash
$ ./server
Hi, I am the FTP server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
client => server: hello
server => client: What file do you want?
client => server: f1
server => client: I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.

client => server: bye
```

Client(Windows 10):

```text
client => server: hello
server => client: What file do you want?
client => server: f1
server => client: File Downloaded.
client => server: bye
```

Visual Studio 2019에서는 `fopen` 사용 시 컴파일 오류가 나기 때문에 전처리기에 `_CRT_SECURE_NO_WARNINGS` 옵션을 줘서 해결해야 한다.

위에서 정의한 Simple FTP에서는 버퍼보다 큰 파일이 들어올 경우를 대비해 -1을 EOF 문자로 지정해 파일을 읽어오는데, `init_request`에 대한 응답으로 서버에서 읽어오는 값의 마지막 -1을 `recv(connectSocket, buf, 1, 0);`으로 지워줘야한다.

파일을 저장할 때는 `fopen`을 이용해 열고 `fprintf`으로 파일 내용을 작성했다.
