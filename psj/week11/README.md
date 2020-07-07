# Network programming 1

## Homework

Copy "client.c" and "server.c" from linuxer1(151 server) or linnuxer2(152 server) using cp command as follows. Do not type by yourself the client and server code in this lecture note which is not accurate.

```bash
$ pwd
/home/sp22/12191765
$ cp ../../linuxer2/cli.c client.c
$ cp ../../linuxer2/serv.c server.c
```

### 1. Adjust port and IP address for both "client.c" and "server.c". `SERV_ADDR` in "client.c" and "server.c" should be the IP address of the linux server you are using. "client.c" will use this `SERV_ADDR` to access the server while "server.c" will use this `SERV_ADDR` to set its own IP address. Pick a port number in the range of [10000..65535]. You need two putty windows: one for the server and the other for the client. Run the server first and then the client.

Sometimes, you have binding failure when running the server. It happens because the server port number is blocked temporarily. Wait for 10 seconds and retry or use a different port number.

See [HW 1](./hw01/)

Server:

```bash
$ ./server
Hi, I am the server
socket opened successfully. socket num is 3
binding passed
we passed accept. new socket num is 4
now reading from client
we got Hello! from cli
enter a string to send to client
Hi!!
```

Client:

```bash
$ ./client
Hi, I am the client
socket opened successfully. socket num is 3
now i am connected to the server. enter a string to send
Hello!
now reading from server
from server: Hi!!
```

`struct sockaddr_in`는 소켓의 주소를 담는 구조체이다. `struct sockaddr`는 IP와 Port 주소가 조합되어 사용하기 불편하므로, `struct sockaddr_in`를 사용한다.

`PF_INET`는 프로토콜 패밀리 인터넷의 약자로 주소 체계를 구분하기 위한 값이다.
`AF` 접두사는 `PF`와 동일하지만 가독성을 위해 추상적인 통신 구조체 변수로써 사용한다.

`inet_addr(cp)`는 문자열로 표현된 IP 주소를 네트워크 바이트 정렬 방식의 4바이트 정수로 변환한다.

`inet_aton(cp, inp)`는 문자열로 표현된 IP 주소를 네트워크 바이트 정렬 방식의 4바이트 정수로 변환하고 직접 구조체에 할당한다.
변환에 실패하면 0을 반환한다.

`htons(hostshort)`은 데이터를 네트워크 바이트 정렬 방식의 2바이트 정수로 변환한다.

`socket(domain, type, protocol)`은 소켓 파일 디스크립터를 생성한다. `protocol`이 0이면 자동으로 프로토콜을 지정해준다.
생성에 실패하면 -1을 반환한다.

`connect(sockfd, addr, addrlen)`은 소켓에 주소를 연결한다.
연결에 실패하면 -1을 반환한다.

사용한 소켓 파일 디스크립터는 `close`로 닫아준다.

### 1-1. Modify "client.c" and "server.c" such that they can talk in sentence (not just in word as in the current implementation).

See [HW 1-1](./hw01_01/)

Server:

```bash
$ ./server
Hi, I am the server
socket opened successfully. socket num is 3
binding passed
we passed accept. new socket num is 4
now reading from client
we got Hello, World! from cli
enter a string to send to client
Yes my master
```

Client:

```bash
$ ./client
Hi, I am the client
socket opened successfully. socket num is 3
now i am connected to the server. enter a string to send
Hello, World!
now reading from server
from server: Yes my master
```

`scanf`를 `fgets`로 바꿔 공백이 포함된 문장도 입력받을 수 있게 한다.

### 2. Modify "client.c" and "server.c" such that they can keep talking until the client sends "bye". Use a finite loop.

See [HW 2](./hw02/)

Server:

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
receive: Hello
Hi
receive: goodbye
bye
```

Client:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
Hello
receive: Hi
goodbye
```

`while(1)`을 이용해 무한 반복문을 만들고 `strcmp`으로 "bye"가 입력되면 반복문을 탈출할 수 있게 했다.

### 2-1. Try to talk with the other student. Note that one of you would be the client and the other the server. `SERV_ADDR` and `SERV_TCP_PORT` in "client.c" should match to those in "server.c" of the other student. (If you prefer to work alone, modify your "client.c" such that it connects to 165.246.38.136 with port number 19924. The server program at 165.246.38.136:19924 will simply echo whatever message you send. You stop the chatting with "bye".)

My Shell:

```bash
$ ./server
Hi, I am the server
socket opened successfully. socket num is 3
binding passed
we passed accept. new socket num is 4
now reading from client
we got SeungJae hi from cli
enter a string to send to client
zzz
now reading from client
we got kkk good job from cli
enter a string to send to client
Hello, World
now reading from client
we got bye from cli
```

다른 컴퓨터의 사용자와도 통신이 잘 된다.

### 2-2. Modify "client.c" such that it connects to Inha web server and read the web page. Inha web server domain name is "www.inha.ac.kr" and port number is 80. You can find the IP address for "www.inha.ac.kr" with ping command. To receive the web page from a web server use GET command:

See [HW 2-2](./hw02_02/client.c)

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
HTTP/1.1 200 OK
Date: Wed, 27 May 2020 00:59:08 GMT
Server: Apache
Set-Cookie: JSESSIONID=94C2F18E0406B12607296F4C327D8E57; Path=/; HttpOnly
Cache-Control: no-cache
Pragma: no-cache
Expires: Thu, 01 Jan 1970 00:00:00 GMT
Content-Length: 1874
Content-Type: text/html;charset=utf-8

<!doctype html>
<html lang="en">
        <head>
                <meta charset="utf-8">
                <meta name="title" content="인하대학교">
                <meta name="keywords" content="인하, 인하대, 인하대학교, INHA, INHA UNIVERSITY, 인하공대, 공대, 공과대학, 인하대병원, 사립대, 4년제, 仁河大, 인천, 하와이, 입학, 입시, 입학정보, 주안역, 정석학술정보관, 도서관, 인하대 후문, 인하홍보동영상">
                <meta name="description" content="인천 미추홀구 인하로 100에 위치한 4년제 사립대학으로, 1954년 인하공과대학으로 설립되어 현재프런티어 학부대학ㆍ공과대학ㆍ자연과학대학ㆍ경영대학ㆍ사범대학ㆍ사회과학대학ㆍ문과대학ㆍ의과대학ㆍ미래융합대학ㆍ예술체육학부ㆍ국제학부 등 11개 단과대학(학부)에 70여 개 학과(부)가 운영되고 있다.">
                <meta property="og:type" content="website">
                <meta property="og:title" content="인하대학교">
                <meta property="og:url" content="http://www.inha.ac.kr">
                <meta property="og:description" content="인천 미추홀구 인하로 100에 위치한 4년제 사립대학으로, 1954년 인하공과대학으로 설립되어 현재프런티어 학부대학ㆍ공과대학ㆍ자연과학대학ㆍ경영대학ㆍ사범대학ㆍ사회과학대학ㆍ문과대학ㆍ의과대학ㆍ미래융합대학ㆍ예술체육학부ㆍ국제학부 등 11개 단과대학(학부)에 70여 개 학과(부)가 운영되고 있다.">
                <meta property="og:image" content="http://www.inha.ac.kr/sites/kr/images/logo.png">
                <meta property="og:image:width" content="150">
                <meta property="og:image:height" content="42">
                <title>site move</title>

                        <meta http-equiv="refresh" content="0;url=/house_study/intro.html">



        </head>
        <body></body>
</html>
```

[What Is My IP Address](https://whatismyipaddress.com/hostname-ip)으로 확인해본 결과, "www.inha.ac.kr"의 IP 주소는 165.246.13.108이다.

기존의 `SERV_ADDR`를 165.246.13.108으로 바꾸고 `SERV_PORT`는 HTTP의 포트 주소인 80으로 지정했다.

"GET / HTTP/1.1\r\nHOST: www.inha.ac.kr\r\n\r\n"를 서버로 전송하고 서버의 응답을 사용자에게 출력하게 했다.

`recv` 함수는 `read`와 같이 소켓 파일 디스크립터로부터 버퍼를 읽어오는 역할을 하지만 연결이 종료되면 0을 반환한다.

### 3. Modify the code such that the client and the server can talk in any order. Use a finite loop to avoid infinite number of processes.

See [HW 3](./hw03/)

Server:

```bash
$ ./server
Hi, I am the server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
Hello, client!
receive: Hi, server!
receive: How are you?
I am fine.
bye
Killed
```

Client:

```bash
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
receive: Hello, client!
Hi, server!
How are you?
receive: I am fine.
```

`fork` 함수를 이용해 서버에서 값을 받아오는 프로세스와 서버에 값을 보내는 프로세스로 나누었다.

"bye"가 입력으로 들어오면 다른 프로세스도 `kill`을 이용해 강제로 종료할 수 있게 했다.
