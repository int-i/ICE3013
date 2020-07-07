# Select

## Homework

### 1. Copy "cliping.c" and "servping.c" into your directory, modify IP and port number appropriately, and compile them. Run the server first and run client 3 times each in different window. Check if the server can handle multiple clients at the same time.

See [HW 1](./hw01/)

```bash
$ pwd
/home/sp22/12191765
$ cp ../../linuxer2/cliping.c client.c
$ cp ../../linuxer2/servping.c server.c
```

Server:

```bash
$ ./server
Hi, I am the server
socket opened successfully. socket num is 3
binding passed
new cli at socket 4
new cli at socket 5
new cli at socket 6
received ping from socket 4
sent pong to socket 4
received ping from socket 5
sent pong to socket 5
received ping from socket 6
sent pong to socket 6
received pang from socket 4
sent pung to socket 4
received pang from socket 5
sent pung to socket 5
received pang from socket 6
sent pung to socket 6
```

Client (1-3):

```bash
$ ./client
Hi, I am the client
socket opened successfully. socket num is 3
enter ping
ping
pong
enter pang
pang
pung
```

"linuxer2" 폴더의 코드를 복사해 실행시켰다.
`select`를 이용해 서버를 구현하면 `fork`의 프로세스 생성 시간을 없앨 수 있고 PID를 이용한 자식 프로세스 통신을 하지 않아도 된다.

`select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)`의 `nfds`은 감시할 파일 디스크립터의 최대 값보다 1 큰 수를 넣으면 되고, `readfds`는 읽을 데이터가 있는 지 검사하기 위한 파일 디스크립터 목록이다.
나머지 인자는 이 예제에서 사용하지 않기 때문에 `NULL`로 두었다.

`select`은 인자로 주어진 `fd_set`을 수정하기 때문에 원본을 따로 복사해둬야 한다.

### 2. The server in Problem 1) cannot give error message to clients even when the client doesn't follow the protocol. Run server and run client and let the client send "pang" instead of "ping" as the first message. The server gives "pung" instead of error message as below. Modify "server.c" so that it can send error message when the client sends something other than "ping" for the first message. But make sure the server still sends "pung" when the client sends "pang" as the second message.

See [HW 2](./hw02/)

Server:

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
receive(cfd=4): ping
send(cfd=4): pong
Client socket(cfd=5) is accepted.
receive(cfd=5): pang
Invalid input to protocol.
receive(cfd=4): pang
send(cfd=4): pung
Client socket(cfd=4) is closed.
receive(cfd=5): pang
send(cfd=5): pung
Client socket(cfd=5) is closed.
```

Client 1:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
Enter ping: ping
receive: pong
Enter pang: pang
receive: pung
```

Client 2:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
Enter ping: pang
receive: Invalid input to protocol.
Enter pang: pang
receive: pung
```

`recv_counts` 배열을 선언해 각 클라이언트로부터 몇 번 내용을 받았는 지 기록했다.
`handle_protocol`에 `recv_count`을 넘겨줘 조건문으로 값이 몇 번째로 들어왔는 지를 판단할 수 있다.

`recv_count == 2`이면 클라이언트의 마지막 값이 들어온 것이므로 연결을 종료한다.

클라이언트로부터 들어온 값과 순서가 일치하지 않으면 "Invalid input to protocol."을 출력한다.

### 2-1. Modify the server such that it disconnects the connection if the client doesn't follow the protocol. You need to keep track of the state of each client to do this. (The client will act strange when the server disconnects it. You don't have to change the client code for this since we don't care about what happens to the client when it does not follow the protocol.)

See [HW 2-1](./hw02_01/server.c/)

Server:

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
receive(cfd=4): ping
send(cfd=4): pong
Client socket(cfd=5) is accepted.
receive(cfd=5): pang
Invalid input to protocol.
Client socket(cfd=5) is closed.
receive(cfd=4): pang
send(cfd=4): pung
Client socket(cfd=4) is closed.
```

Client 1:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
Enter ping: ping
receive: pong
Enter pang: pang
receive: pung
```

Client 2:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
Enter ping: pang
receive: Invalid input to protocol.
Enter pang: pang
receive:
```

프로토콜이 올바르지 않으면 연결을 종료한다.
`else`문을 이용해 구현했다.

클라이언트에서는 연결 종료를 처리하는 구문을 구현하지 않았기 때문에 Client 2와 같이 소켓 연결이 종료되었더라도 `fgets`로 사용자에게 계속 입력 받는다.

### 3. Modify the protocol such that the server expects a final "ping" again from the client. Make sure the server give error message and disconnect the client if the client doesn't follow the protocol.

See [HW 3](./hw03/)

Server:

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
client(cfd=4) => server: ping
server => client(cfd=4): pong
Client socket(cfd=5) is accepted.
client(cfd=5) => server: ping
server => client(cfd=5): pong
client(cfd=4) => server: pang
server => client(cfd=4): pung
client(cfd=5) => server: ping
Invalid input to protocol.
Client socket(cfd=5) is closed.
client(cfd=4) => server: ping
server => client(cfd=4): Process completed.
Client socket(cfd=4) is closed.
```

Client 1:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: (Enter ping) ping
server => client: pong
client => server: (Enter pang) pang
server => client: pung
client => server: (Enter ping) ping
server => client: Process completed.
```

Client 2:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: (Enter ping) ping
server => client: pong
client => server: (Enter pang) ping
server => client: Invalid Input
Error occurred by the protocol.
```

[2-1의 서버 코드](./hw02_01/server.c)에서 `recv_count == 3`일 때 "ping"을 받는지 확인하는 코드를 추가했다.

클라이언트에서도 마지막 "ping"을 입력하기 위한 `fgets`와 프로토콜로 인해 소켓 연결이 끊어졌을 때를 위해 예외를 처리하는 코드를 추가했다.
위의 클라이언트 2와 같이 프로토콜과 다른 입력이 들어오면 연결이 끊어지면서 "client" 프로그램도 종료된다.

### 4. Modify the protocol such that the server relays a message from a client to all other clients after the "ping-pong-pang-pung" sequence is completed. The clients should fork itself after the "ping-pong-pang-pung" sequence so that the parent part keeps reading while the child part keeps writing. The server does not fork since it doesn't do the chatting by itself; it just relays a message from one client to all other clients. The server checks `states[]` array to see which socket is ready to receive message.

See [HW 4](./hw04/)

Server:

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
Client socket(cfd=5) is accepted.
client(cfd=4) => server: ping
server => client(cfd=4): pong
client(cfd=4) => server: pang
server => client(cfd=4): pung. Process completed. Start chatting.
client(cfd=5) => server: ping
server => client(cfd=5): pong
client(cfd=5) => server: pang
server => client(cfd=5): pung. Process completed. Start chatting.
client(cfd=4) => server: Hello
server => client(cfd=5): Hello
client(cfd=5) => server: Hi
server => client(cfd=4): Hi
client(cfd=4) => server: Nice to meet you
server => client(cfd=5): Nice to meet you
client(cfd=5) => server: Okay, bye
server => client(cfd=4): Okay, bye
```

Client 1:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: (Enter ping) ping
server => client: pong
client => server: (Enter pang) pang
server => client: pung. Process completed. Start chatting.
client => server: (Chat) Hello
client => server: (Chat) server => client: Hi
Nice to meet you
client => server: (Chat) server => client: Okay, bye
```

Client 2:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: (Enter ping) ping
server => client: pong
client => server: (Enter pang) pang
server => client: pung. Process completed. Start chatting.
client => server: (Chat) server => client: Hello
Hi
client => server: (Chat) server => client: Nice to meet you
Okay, bye
client => server: (Chat)
```

3번 문제에서 채팅 기능을 추가했다.
`state`가 `STATE_CHAT`이고 `buf`에 메세지가 존재한다면 반복문을 이용해 `state`가 `STATE_CHAT`인 다른 파일 디스크립터를 찾는다.
찾은 파일 디스크립터에 `write`로 `buf`의 내용을 전송한다.
이때, `fd != other_fd`으로 메세지를 처음 보낸 사람에게는 다시 보내지 않도록 주의해야 된다.

### 5. Modify your code in Problem 4) such that the server attaches the client's name and age in the message. For this purpose, the server should ask name and age for each client and store them in `clients[]` array which is an array of `client` structure to store name and age of each client. `clients[x]` will remember the client information whose socket number is `x`.

See [HW 5](./hw05/)

Server:

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
Client socket(cfd=5) is accepted.
client(cfd=4) => server: ping
server => client(cfd=4): pong
client(cfd=4) => server: pang
server => client(cfd=4): pung. Enter your name.
client(cfd=4) => server: aaa
server => client(cfd=4): Enter your age.
client(cfd=4) => server: 10
server => client(cfd=4): Process completed. Start chatting.
client(cfd=5) => server: ping
server => client(cfd=5): pong
client(cfd=5) => server: pang
server => client(cfd=5): pung. Enter your name.
client(cfd=5) => server: bbb
server => client(cfd=5): Enter your age.
client(cfd=5) => server: 20
server => client(cfd=5): Process completed. Start chatting.
client(cfd=4) => server: Hello
server => client(cfd=5): Hello
client(cfd=5) => server: Hi
server => client(cfd=4): Hi
client(cfd=4) => server: How are you?
server => client(cfd=5): How are you?
client(cfd=5) => server: I'm fine.
server => client(cfd=4): I'm fine.
```

Client 1:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: (Enter ping) ping
server => client: pong
client => server: (Enter pang) pang
server => client: pung. Enter your name.
client => server: (Enter your name) aaa
server => client: Enter your age.
client => server: (Enter your age) 10
server => client: Process completed. Start chatting.
client => server: (Chat) Hello
client => server: (Chat) server => client: Hi
How are you?
client => server: (Chat) server => client: I'm fine.
```

Client 2:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: (Enter ping) ping
server => client: pong
client => server: (Enter pang) pang
server => client: pung. Enter your name.
client => server: (Enter your name) bbb
server => client: Enter your age.
client => server: (Enter your age) 20
server => client: Process completed. Start chatting.
client => server: (Chat) server => client: Hello
Hi
client => server: (Chat) server => client: How are you?
I'm fine.
client => server: (Chat)
```

클라이언트의 이름과 나이를 저장하는 `client` 구조체를 선언하고 `handle_protocol`에 클라이언트를 저장해둔 배열을 전달한다.

`state`가 `STATE_ASK_NAME`이면 `clients[fd]`에 입력받은 이름을 저장하고, `STATE_ASK_AGE`이면 입력받은 나이를 저장한다.
4번과 동일하게 `state`가 `STATE_CHAT`이면 입력받은 문자열을 `state`가 `STATE_CHAT`인 다른 클라이언트에게 전송한다.

### 6. Modify your code in Problem 5) such that the client can now specify which client it wants to chat with. Add `partner` to `client` strucure to remember the socket number of the chatting partner. The server should ask which partner the clients wants to talk with and remember the partner's socket number in the `client` structure. Assume if client A points to client B as a partner, client B also points to client A as a partner.

See [HW 6](./hw06/)

Server:

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
Client socket(cfd=5) is accepted.
client(cfd=4) => server: ping
server => client(cfd=4): pong
client(cfd=4) => server: pang
server => client(cfd=4): pung. Enter your name.
client(cfd=4) => server: aaa
server => client(cfd=4): Enter your age.
client(cfd=4) => server: 10
server => client(cfd=4): Enter your partner.
client(cfd=5) => server: ping
server => client(cfd=5): pong
client(cfd=5) => server: pang
server => client(cfd=5): pung. Enter your name.
client(cfd=5) => server: bbb
server => client(cfd=5): Enter your age.
client(cfd=5) => server: 20
server => client(cfd=5): Enter your partner.
client(cfd=4) => server: bbb
server => client(cfd=4): Process completed. Start chatting.
client(cfd=5) => server: aaa
server => client(cfd=5): Process completed. Start chatting.
client(cfd=4) => server: Hello
server => client(cfd=5): Hello
client(cfd=5) => server: Hi
server => client(cfd=4): Hi
client(cfd=4) => server: Bye
server => client(cfd=5): Bye
client(cfd=5) => server: Bye Bye
server => client(cfd=4): Bye Bye
```

Client 1:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: (Enter ping) ping
server => client: pong
client => server: (Enter pang) pang
server => client: pung. Enter your name.
client => server: (Enter your name) aaa
server => client: Enter your age.
client => server: (Enter your age) 10
server => client: Enter your partner.
client => server: (Enter your partner) bbb
server => client: Process completed. Start chatting.
client => server: (Chat) Hello
client => server: (Chat) server => client: Hi (bbb to aaa)
Bye
client => server: (Chat) server => client: Bye Bye (bbb to aaa)
```

Client 2:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: (Enter ping) ping
server => client: pong
client => server: (Enter pang) pang
server => client: pung. Enter your name.
client => server: (Enter your name) bbb
server => client: Enter your age.
client => server: (Enter your age) 20
server => client: Enter your partner.
client => server: (Enter your partner) aaa
server => client: Process completed. Start chatting.
client => server: (Chat) server => client: Hello (aaa to bbb)
Hi
client => server: (Chat) server => client: Bye (aaa to bbb)
Bye Bye
client => server: (Chat)
```

`client` 구조체에 `partner` 속성을 추가했다.

`state`가 `STATE_ASK_PARTNER`고 `buf`에 내용이 존재한다면, 반복문으로 `state`가 `STATE_ASK_NAME` 이상인 클라이언트에 대해 이름을 검사해 `partner`에 클라이언트의 파일 디스크립터를 저장한다.
`STATE_CHAT`에서는 기존의 모든 클라이언트에 메세지를 전송하는 것에서 `partner`에게만 메세지를 전송하게 바꾸었다.

### 7. Implement a chatting server. The state of the client during the protocol is as follows. At any moment multiple pair of clients should be able to talk at the same time.

1. state 1: The server is expecting "hello" for this client. When "hello" arrives, the server sends "name?"
2. state 2: The server is expecting client ID from this client. The server rembers this client's ID in `clients[x].name`, where `x` is the socket number of this client. The server asks "ready?".
3. state 3: The server is expecting "yes" from this client. The server sends all client name whose state is greater than or equal to 3.
4. state 4: The server is expecting the chatting partner's ID from this client. The server remembers partner socket number in `clients[x].partner`. Send "go" to the client.
5. state 5: The client is now in chatting session. The server is expecting some chat message from this client. The server sends this message to `clients[x].partner`.

See [HW 7](./hw07/)

Server:

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
client(cfd=4) => server: hello
server => client(cfd=4): name?
Client socket(cfd=5) is accepted.
client(cfd=5) => server: hello
server => client(cfd=5): name?
client(cfd=4) => server: aaa
server => client(cfd=4): ready?
client(cfd=5) => server: bbb
server => client(cfd=5): ready?
client(cfd=4) => server: yes
server => client(cfd=4): client list(bbb)
client(cfd=5) => server: yes
server => client(cfd=5): client list(aaa)
client(cfd=4) => server: bbb
server => client(cfd=4): go
client(cfd=5) => server: aaa
server => client(cfd=5): go
client(cfd=4) => server: Hi
server => client(cfd=5): Hi
client(cfd=5) => server: Hello
server => client(cfd=4): Hello
client(cfd=4) => server: Bye
server => client(cfd=5): Bye
client(cfd=5) => server: Bye!
server => client(cfd=4): Bye!
```

Client 1:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: helloserver => client: name?
client => server: (Enter your name) aaa
server => client: ready?
client => server: (Enter yes) yes
server => client: client list(bbb)
client => server: (Enter your partner) bbb
server => client: go
client => server: (Chat) Hi
client => server: (Chat) server => client: Hello
Bye
client => server: (Chat) server => client: Bye!
```

Client 2:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: helloserver => client: name?
client => server: (Enter your name) bbb
server => client: ready?
client => server: (Enter yes) yes
server => client: client list(aaa)
client => server: (Enter your partner) aaa
server => client: go
client => server: (Chat) server => client: Hi
Hello
client => server: (Chat) server => client: Bye
Bye!
client => server: (Chat)
```

`state`에 저장되는 값을 `#define`으로 상수로 지정했다.

`state`가 `STATE_INIT`이고 "hello"를 받으면 "name?"을 전송한다.
`state`를 1 증가시킨다.

`state`가 `STATE_ASK_NAME`이고 메세지를 받으면 `clients[fd].name`에 입력받은 이름을 저장하고 "ready?"를 전송한다.
`state`를 1 증가시킨다.

`state`가 `STATE_READY`이고 "yes"를 받으면 반복문으로 `state`가 `STATE_ASK_NAME` 이후인 클라이언트의 이름을 전송한다.
`state`를 1 증가시킨다.

`state`가 `STATE_ASK_PARTNER`이고 메세지를 받으면 반복문으로 입력받은 이름과 같은 이름을 가진 클라이언트를 확인한다.
클라이언트가 있다면 `clients[fd].partner`에 클라이언트의 파일 디스크립터를 저장하고 `state`를 1 증가시킨다.

`state`가 `STATE_CHAT`이면 채팅이 가능한 상태로 수신 받은 메세지를 클라이언트의 `partner`에 전송한다.

만약 클라이언트가 프로토콜을 따르지 않으면 "Invalid input to protocol."을 전송한다.
