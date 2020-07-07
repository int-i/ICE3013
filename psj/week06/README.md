# Command Line Argument

## Homework

Set up bash startup file: copy .bashrc and .bash_profile into your login directory

```bash
$ pwd
/home/sp22/12191765
$ cp ../../linuxer2/.bashrc .
$ cp ../../linuxer2/.bash_profile .
```

And close your putty window and reopen.
Now the prompt should have been changed to:

```bash
[12191765@linuxer2 ~]$
```

Now you can type program name without "./" prefix.

```bash
$ ex1
```

instead of,

```bash
$ ./ex1
```

The new bash startup files will include the current directory(".") in the PATH environment variable which in turn allows you to type program name withtout "./" prefix to run it. (You have to reopen putty terminal to see the effect!)

### 1. Try following program which doesn't receive command line arguments.

See [HW 1](./hw01/main.c)

```bash
$ gcc -o hw01 hw01.c
$ hw01
hi
```

ANSI C 표준에서는 두 가지의 `main` 사용을 권장하는데 인자가 없는 `main` 함수는 `int main(void)`를 사용한다.

### 2. Try following program that receives one command line argument.

See [HW 2](./hw02/main.c)

```bash
$ gcc -o hw02 hw02.c
$ hw02
hi
1
hw02
```

인자가 있는 `main` 함수는 `int main(int argc, char* argv[])`를 사용한다.
`argc`는 인자 개수, `argv`는 인자 값을 의미한다.

### 3. Try following program that receives two command line arguments.

See [HW 3](./hw03/main.c)

```bash
$ gcc -o hw03 hw03.c
$ hw03
hi
1
hw03
Segmentation fault (core dumped)
$ hw03 hello
hi
2
hw03
hello
$ hw03 hello tuit
hi
3
hw03
hello
```

`argc`는 프로그램명을 포함한 인자 개수로 인자가 아무것도 없을 때 1을 가진다.
`argv`는 문자열의 배열로 인자로 들어온 값을 의미한다.

### 4. A program that receives three command line arguments.

See [HW 4](./hw04/main.c)

```bash
$ gcc -o hw04 hw04.c
$ hw04 hello there here
hi
4
hello
there
here
```

마찬가지로 인자가 3개 들어왔기 때문에 프로그램명을 포함해 `argc`는 4이다.

### 5. A program that receives any number of arguments.

See [HW 5](./hw05/main.c)

```bash
$ gcc -o hw05 hw05.c
$ hw05 x1 x2 x3 x4
argc is 5
argv[0] is hw05
argv[1] is x1
argv[2] is x2
argv[3] is x3
argv[4] is x4
```

프로그램의 인자를 반복문을 이용해 차례대로 출력하고 있다.

### 6. Try following and explain the difference from `echo` command. 

See [HW 6](./hw06/main.c)

```bash
$ gcc –o myecho hw06.c
$ myecho hello
hello
$ echo hello
hello
$ myecho hello hi bye
hello hi bye
$ echo hello hi bye
hello hi bye
$ echo hi > f1
$ cat f1
hi
$ myecho hi > f2
$ cat f2
hi
```

`echo`는 주어진 문자열을 공백과 마지막 개행문자를 포함해 표준출력으로 출력하는 명령어이다.
5번과 다른점은 `argv`를 1번부터 출력하기 때문에 프로그램명은 출력되지 않는다.
또한 `myecho`는 단어사이의 공백 여러 개 있더라도 한번만 출력한다.

### 7. Try following and explain the difference from `cat` command.

See [HW 7](./hw07/main.c)

```bash
$ gcc –o mycat hw07.c
$ cat f1
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
$ mycat f1
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
$ cat f23
cat: f23: No such file or directory
$ mycat f23
error in open: No such file or directory
$ cat hw07.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int x, y;
    char buf[20];

    x = open(argv[1], O_RDONLY);
    if (x == -1) {
        perror("Fail to open");
        exit(EXIT_FAILURE);
    }
    for (;;) {
        y = read(x, buf, 20);
        if (y == 0)
            break;
        write(1, buf, y);
    }
    return 0;
}

$ mycat hw07.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int x, y;
    char buf[20];

    x = open(argv[1], O_RDONLY);
    if (x == -1) {
        perror("Fail to open");
        exit(EXIT_FAILURE);
    }
    for (;;) {
        y = read(x, buf, 20);
        if (y == 0)
            break;
        write(1, buf, y);
    }
    return 0;
}
```

`cat`은 파일을 간단하게 출력할 때도 사용되지만 두 개 이상의 파일을 연결해서 출력할 때도 사용한다.
`mycat`은 하나의 파일의 내용만 출력할 수 있을 뿐, 여러 개의 파일을 출력하지는 못한다.

### 8. Try following: "mycat2". Use functions for your program.

See [HW 8](./hw08/main.c)

```bash
$ gcc –o mycat2 hw08.c
$ mycat2 f1
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
$ mycat2 f23
error in open: No such file or directory
```

파일 내용을 읽어서 출력하는 기능을 `display_content` 함수로 분리해 구현했다.
`main` 함수에서 해당하는 파일이 존재할 경우 `display_content` 함수를 호출해 내용을 출력하고 존재하지 않는다면 오류를 출력한다.

### 9. Try following: "mycat3".

See [HW 9](./hw09/main.c)

```bash
$ gcc –o mycat3 hw09.c
$ mycat3 f1
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
$ mycat3 f23
error in open: No such file or directory
```

주어진 파일 경로에 대한 파일 디스크립터를 구하는 기능을 `show_file` 함수로 분리했다.
`main` 함수에서 프로그램의 첫번째 인자와 함께 `show_file`를 호출한다.
주어진 파일이 존재한다면 이어서 `display_content` 함수를 호출해 파일 내용을 읽어 출력하고, 존재하지 않다면 오류를 출력한다.

### 10. You can debug programs with command line arguments as follows. Debug "mycat3" with gdb. To pass command line arguments to gdb, do `set args arg1 arg2 ...`.

```bash
$ gcc -g -o mycat3 hw09.c
hw09.c: In function ‘main’:
hw09.c:9:14: warning: unused parameter ‘argc’ [-Wunused-parameter]
$ gdb mycat3
GNU gdb (GDB) Fedora (7.5.1-38.fc18)
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/sp22/12191765/lect8/mycat3...done.
(gdb) b main
Breakpoint 1 at 0x40065b: file hw09.c, line 10.
(gdb) set args f1 f2 f3
(gdb) r
Starting program: /home/sp22/12191765/lect8/mycat3 f1 f2 f3

Breakpoint 1, main (argc=4, argv=0x7fffffffe4d8) at hw09.c:10
10          show_file(argv[1]);
Missing separate debuginfos, use: debuginfo-install glibc-2.16-31.fc18.x86_64
(gdb) b 16
Breakpoint 2 at 0x400681: file hw09.c, line 16.
(gdb) c
Continuing.

Breakpoint 2, show_file (fname=0x7fffffffe777 "f1") at hw09.c:16
16          x = open(fname, O_RDONLY);
(gdb) p x
$1 = 0
(gdb) b 27
Breakpoint 3 at 0x4006cb: file hw09.c, line 27.
(gdb) c
Continuing.

Breakpoint 3, display_content (x=7) at hw09.c:28
28              y = read(x, buf, 20);
(gdb) x/20bx buf
0x7fffffffe380: 0x77    0xe7    0xff    0xff    0xff    0x7f    0x00    0x00
0x7fffffffe388: 0x80    0x2e    0xdb    0xad    0x35    0x00    0x00    0x00
0x7fffffffe390: 0x30    0xf4    0x60    0xad
(gdb) c
Continuing.
I have a dream
that
Breakpoint 3, display_content (x=7) at hw09.c:28
28              y = read(x, buf, 20);
(gdb) x/20bx buf
0x7fffffffe380: 0x49    0x20    0x68    0x61    0x76    0x65    0x20    0x61
0x7fffffffe388: 0x20    0x64    0x72    0x65    0x61    0x6d    0x0a    0x74
0x7fffffffe390: 0x68    0x61    0x74    0x20
(gdb) c
Continuing.
one day
this nation
Breakpoint 3, display_content (x=7) at hw09.c:28
28              y = read(x, buf, 20);
(gdb) x/20bx buf
0x7fffffffe380: 0x6f    0x6e    0x65    0x20    0x64    0x61    0x79    0x0a
0x7fffffffe388: 0x74    0x68    0x69    0x73    0x20    0x6e    0x61    0x74
0x7fffffffe390: 0x69    0x6f    0x6e    0x20
(gdb) c
Continuing.
will rise up,
live o
Breakpoint 3, display_content (x=7) at hw09.c:28
28              y = read(x, buf, 20);
(gdb) x/20bx buf
0x7fffffffe380: 0x77    0x69    0x6c    0x6c    0x20    0x72    0x69    0x73
0x7fffffffe388: 0x65    0x20    0x75    0x70    0x2c    0x0a    0x6c    0x69
0x7fffffffe390: 0x76    0x65    0x20    0x6f
(gdb) c
Continuing.
ut the true meaning
Breakpoint 3, display_content (x=7) at hw09.c:28
28              y = read(x, buf, 20);
(gdb) x/20bx buf
0x7fffffffe380: 0x75    0x74    0x20    0x74    0x68    0x65    0x20    0x74
0x7fffffffe388: 0x72    0x75    0x65    0x20    0x6d    0x65    0x61    0x6e
0x7fffffffe390: 0x69    0x6e    0x67    0x20
(gdb) c
Continuing.
of its creed.

Breakpoint 3, display_content (x=7) at hw09.c:28
28              y = read(x, buf, 20);
(gdb) x/20bx buf
0x7fffffffe380: 0x6f    0x66    0x20    0x69    0x74    0x73    0x20    0x63
0x7fffffffe388: 0x72    0x65    0x65    0x64    0x2e    0x0a    0x61    0x6e
0x7fffffffe390: 0x69    0x6e    0x67    0x20
(gdb) c
Continuing.
[Inferior 1 (process 29908) exited normally]
(gdb) q
```

GDB를 사용하기 위해 `-g` 옵션을 전달해 코드를 컴파일 했다.
프로그램을 실행시키기 전에 `set args`를 이용해 `main` 함수로 인자를 전달하고 `main` 함수에 중단점을 걸어두었다.
먼저 파일을 정상적으로 찾는 것을 보이기 위해 16번째 줄에 중단점을 걸어 파일 디스크립터를 정상적으로 반환하는 것을 보였다.
그 후 파일을 읽어가며 `buf`가 변하는 것을 보이기 위해 27번째 줄에 중단점을 걸어 반복문을 실행할 때마다 프로그램이 중단되게 했다.
`x`를 이용해 `buf`의 메모리 값을 출력해, 프로그램이 파일을 읽으며 `buf`가 수정함을 확인할 수 있다.

### 11. Modify "mycat" such that it can handle two input files.

See [HW 11](./hw11/main.c)

```bash
$ gcc -o mycat4 hw11.c
$ cat f1 f2
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
hi
$ mycat4 f1
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
$ mycat4 f1 f2
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
hi
```

먼저 `print_file`로 파일의 내용을 출력하는 함수를 작성했다.
프로그램의 인자가 하나 이상일 때 첫 번째 인자로 `print_file` 함수를, 두 개 이상일 때 추가적으로 두 번째 인자로 `print_file` 함수를 호출하면 파일을 이어서 출력하는 기능을 구현할 수 있다.

### 12. Modify "mycat" such that it can handle any number of files.

See [HW 12](./hw12/main.c)

```bash
$ gcc -std=c99 -o mycat5 hw12.c
$ cat f1 f2 f3 f4
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
hi
hello
hola
$ mycat5 f1 f2 f3
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
hi
hello
$ mycat5 f1 f2 f3 f4
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
hi
hello
hola
```

입력되는 파일의 최대 개수를 미리 알 수 없다면 `argc`를 이용해 인자 개수를 파악하고 반복문을 통해 해결하면 된다.
1부터 `argc - 1`까지 파일이름을 입력받아 `print_file` 함수에 전달하면 입력되는 파일의 내용을 이어 출력하는 기능을 구현할 수 있다.

### 13. Implement "mycp" that works similarly to `cp`.

See [HW 13](./hw13/main.c)

```bash
$ gcc -o mycp hw13.c
$ cat f1
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
$ mycp f1 c1
$ cat c1
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
```

`copy_file`은 파일의 내용을 복사해 새로운 파일을 만드는 함수이다.
읽어올 파일 `in_fd`와 작성할 파일 `out_fd`를 만들고 20씩 읽어 파일을 옮겨쓴다.
더 이상 읽을 내용이 없다면 `read`는 0을 반환하기 때문에 `while` 문은 종료된다.
만약 리눅스에서만 사용을 가정하고 프로그램을 작성한다면, `sendfile` 함수를 이용해 쉽게 파일을 복사할 수 있다.

### 14. Implement "myxxd" that works similarly to `xxd`. Run `myxxd hw12.c`. Compare the result with `xxd hw12.c`.

See [HW 14](./hw14/main.c)

```bash
$ gcc -std=c99 -o myxxd hw14.c
$ cat f5
abc
$ xxd f5
0000000: 6162 630a                                abc.
$ myxxd f5
61 62 63 a
```

`printf`에 `%x`로 문자를 전달하면 16진수 형태로 출력할 수 있다.
파일을 20글자씩 읽어 `buf`에 저장했다. 그리고 `buf`에 들어있는 문자를 한 글자씩 가져와 `printf`에 전달해 16진수로 출력했다.

### 15. Modify "mycat" to handle various options. The second argument is either a file or an option. If it is a file, just display the contents. If it is an option (starting with "-"), perform the following corresponding actions.

See [HW 15](./hw15/main.c)

```bash
$ gcc -std=c99 -o mycat hw15.c
$ cat f1
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
$ mycat f1
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
$ mycat -o f1 f1out
$ cat f1out
I have a dream
that one day
this nation will rise up,
live out the true meaning of its creed.
$ mycat -x f1
49 20 68 61 76 65 20 61 20 64 72 65 61 6d a 74 68 61 74 20 6f 6e 65 20 64 61 79 a 74 68 69 73 20 6e 61 74 69 6f 6e 20 77 69 6c 6c 20 72 69 73 65 20 75 70 2c a 6c 69 76 65 20 6f 75 74 20 74 68 65 20 74 72 75 65 20 6d 65 61 6e 69 6e 67 20 6f 66 20 69 74 73 20 63 72 65 65 64 2e a
$ mycat -p /etc/passwd
name: root, password: x, UID: 0, GID: 0, GECOS: root, directory: /root, shell: /bin/bash
name: bin, password: x, UID: 1, GID: 1, GECOS: bin, directory: /bin, shell: /sbin/nologin
name: daemon, password: x, UID: 2, GID: 2, GECOS: daemon, directory: /sbin, shell: /sbin/nologin
name: adm, password: x, UID: 3, GID: 4, GECOS: adm, directory: /var/adm, shell: /sbin/nologin
name: lp, password: x, UID: 4, GID: 7, GECOS: lp, directory: /var/spool/lpd, shell: /sbin/nologin
...
name: 12194353, password: x, UID: 1933, GID: 1933, GECOS: Student Account, directory: /home/bp12/12194353, shell: /bin/bash
name: 12200107, password: x, UID: 1934, GID: 1934, GECOS: Student Account, directory: /home/bp12/12200107, shell: /bin/bash
name: 12197451, password: x, UID: 1935, GID: 1935, GECOS: Student Account, directory: /home/sp12/12197451, shell: /bin/bash
name: 12200030, password: x, UID: 1936, GID: 1936, GECOS: Student Account, directory: /home/sp12/12200030, shell: /bin/bash
name: 12180246, password: x, UID: 1937, GID: 1937, GECOS: Student Account, directory: /home/bp12/12180246, shell: /bin/bash
$ mycat -d d1
f1
f2
f3
```

프로그램에 추가적인 인자가 들어오는지를 먼저 검사해 인자가 있다면 옵션을 검사하는 조건문으로 보내고, 없다면 인자가 없다는 오류를 출력하게 했다.
옵션의 유무는 첫 번째 인자가 -으로 시작하는 지 검사하면 되는데, 옵션이 있다면 두 번째 문자를 가져와 switch를 이용해 비교하게 했다.
옵션이 업다면 `print_file` 함수를 호출해 파일 내용을 출력한다.

`-d`는 디렉토리 안에 들어있는 폴더를 출력하는 기능으로 `opendir`과 `readdir`을 이용해 구현했다.
`readdir`은 `struct dirent*`를 반환하는데, 이것을 이용해 파일의 이름을 알 수 있다.
현재 디렉토리와 상위 디렉토리를 가리키는 "."과 ".."은 출력하지 않게 예외처리 했다.

`-o`는 파일의 내용을 복사하는 기능으로 위에서 작성한 `copy_file` 함수를 이용해 구현했다.

`-p`는 passwd 형식의 파일을 읽어 사람이 보기 좋게 다듬어 보여주는 기능으로, `fopen`으로 파일을 열어 `fgets`를 이용해 줄 단위로 읽어온다.
`strtok`을 사용해 ":"을 구분자로 문자열을 끊어 읽고 `fieldnames`에 정의된 문자열을 순서대로 합쳐서 출력할 수 있게 했다.

`-x`는 파일을 16진수 형태로 출력하는 기능으로 14번에서 작성한 함수를 재사용해 구현했다.
만약 주어진 옵션이 정의되지 않았다면 프로그램은 오류를 출력하고 종료한다.
