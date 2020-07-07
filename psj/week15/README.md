# Final Exam

## Practice

### 1. Implement following simple ftp protocol server with `select`. Make sure the server can handle multiple clients at the same time. Do not use `fork` either in the server or in the client. Copy and paste the full source code, output capture, and brief explanation whether it is working or not (and if not where it is not working).

Server:

```bash
$ ./server
Hi, I am the FTP server.
Server socket(sfd=3) is created.
Client socket(cfd=4) is accepted.
client(cfd=4) => server: hello
server => client(cfd=4): file name?
client(cfd=4) => server: f1
server => client(cfd=4): ready?
Client socket(cfd=5) is accepted.
client(cfd=5) => server: hello
server => client(cfd=5): file name?
client(cfd=5) => server: f1
server => client(cfd=5): ready?
client(cfd=4) => server: yes
server => client(cfd=4): I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.

Client socket(cfd=4) is closed.
client(cfd=5) => server: yes
server => client(cfd=5): Implement following simple ftp protocol server with select. Make sure the server can handle multiple clients at the same time. Do not use fork either in the server or in the client. Copy and paste the full source code, output capture, and brief explanation whether it is working or not (and if not where it is not working).


Client socket(cfd=5) is closed.
```

Client 1:

```bash
$ ls
client client.c
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: hello
server => client: file name?
client => server: (Enter file name) f1
server => client: ready?
client => server: (Enter yes) yes
server => client: I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.

$ ls
client client.c f1
$ f1
I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.
```

Client 2:

```bash
$ ls
client
$ ./client
Hi, I am the client.
Socket(sfd=3) is created.
client => server: hello
server => client: file name?
client => server: (Enter file name) f2
server => client: ready?
client => server: (Enter yes) yes
server => client: Implement following simple ftp protocol server with select. Make sure the server can handle multiple clients at the same time. Do not use fork either in the server or in the client. Copy and paste the full source code, output capture, and brief explanation whether it is working or not (and if not where it is not working).


$ ls
client f2
$ cat f2
Implement following simple ftp protocol server with select. Make sure the server can handle multiple clients at the same time. Do not use fork either in the server or in the client. Copy and paste the full source code, output capture, and brief explanation whether it is working or not (and if not where it is not working).
```

See [Sol. 1](./sol01/)
