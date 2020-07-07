# File 1

## Homework

### 1. Make a file, "f1", and fill it with more than 20 bytes.

```bash
$ vi f1
```

```text
I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.
```

### 2. Try the code in example 0 to 3.

#### Example 0. Reading 20 bytes from file "fi" and display them in the terminal using `printf`.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x, y;
    char buf[50];
    x = open("f1", O_RDONLY, 00777); // open f1 in the current directory
    y = read(x, buf, 20); // read max 20 bytes. return actual number of bytes read in y.
    buf[y] = 0; // make buf a string
    printf("%s\n", buf); // and display
    return 0;
}
```

```text
I have a dream
that
```

`buf`의 크기가 20이라 20자만 출력되었다.

#### Example 1. Reading 20 bytes from file "f1" and display them in the terminal using write.

```c
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int x, y;
    char buf[50];
    x = open("f1", O_RDONLY, 00777); // open f1 in the current directory
    y = read(x, buf, 20); // read max 20 bytes. return actual number of bytes read in y.
    write(1, buf, y); // write y bytes in buf to the terminal.
    return 0;
}
```

```text
I have a dream
that
```

위와 마찬가지로 `buf`의 크기가 20이라 20자만 출력되었다.
`write`의 첫 번째 인자 `1`은 `STDOUT_FILENO`의 값이다.

#### Example 2. Copying 20 bytes from file "f1" to "f2". Check "f2" with `cat f2`.

```c
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int x1, x2, y;
    char buf[50];
    x1 = open("f1", O_RDONLY, 00777); // open f1 for reading
    x2 = open("f2", O_RDWR | O_CREAT | O_TRUNC, 00777); // open f2 for writing
    y = read(x1, buf, 20); // read max 20 bytes. return actual number of bytes read in y.
    write(x2, buf, y); // write y bytes in buf to f2
    return 0;
}
```

```bash
$ cat f2
I have a dream
that
```

크기가 20인 `buf`에 "f1" 내용을 담아서 "f2"에 복사했다.
`open`은 file descriptor를 반환한다.
`read`로 파일을 읽어올 수 있고 `write` 파일을 저장할 수 있다.

#### Example 3. Same as above, but copy all data from "f1" to "f2". Check "f2" with `cat f2`.

```c
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int x1, x2, y;
    char buf[50];
    x1 = open("f1", O_RDONLY, 00777); // open f1 for reading
    x2 = open("f2", O_RDWR | O_CREAT | O_TRUNC, 00777); // open f2 for writing
    for (;;) {
        y = read(x1, buf, 20); // read max 20 bytes from f1
        if (y == 0)
            break; // if end-of-file, get out
        write(x2, buf, y); // write to f2
    }
    return 0;
}
```

```bash
$ cat f2
I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.
```

위와 비슷하지만, `y`가 0이 될 때까지 읽어서 파일의 모든 내용을 복사할 수 있다.

### 3. Find the byte size of "f2" with `ls –l f2`. Use `xxd` to find out the actual data stored in "f2".

```bash
$ ls –l f2
-rwxrwxr-x. 1 12191765 12191765 128 Apr  7 10:41 f2
$ xxd f2
0000000: 4920 6861 7665 2061 2064 7265 616d 0a74  I have a dream.t
0000010: 6861 7420 6f6e 6520 6461 7920 7468 6973  hat one day this
0000020: 206e 6174 696f 6e0a 7769 6c6c 2072 6973   nation.will ris
0000030: 6520 7570 2061 6e64 0a6c 6976 6520 6f75  e up and.live ou
0000040: 7420 7468 6520 7472 7565 0a6d 6561 6e69  t the true.meani
0000050: 6e67 206f 6620 6974 7320 6372 6565 640a  ng of its creed.
0000060: 7468 6174 2061 6c6c 206d 656e 2061 7265  that all men are
0000070: 2063 7265 6174 6564 2065 7175 616c 2e0a   created equal..
```

`ls –l f2`로 "f2" 파일의 크기를 확인할 수 있고 `xxd`로 파일의 내용을 16진수로 볼 수 있다.

### 4. Write a program "hw4.c" that opens f2 and shows each byte of it in hexadecimal number, decimal number, and character. Use printf("%x %d %c\n", ...) to display a number in various format.

See [HW 4](./hw04/main.c)

```text
49 73 I
20 32
68 104 h
61 97 a
76 118 v
65 101 e
20 32
61 97 a
20 32
64 100 d
...
71 113 q
75 117 u
61 97 a
6c 108 l
2e 46 .
a 10
```

`%x %d %c`는 각각 16진수, 10진수, 문자 자체를 출력하라는 명령이다.
`read(x, buf, 1);`는 `x`에서 한 글자씩 읽어나가며 `buf[0]`에 문자를 저장한다.
저장된 `buf[0]`는 `printf`를 통해 출력된다.

### 5. Compile "hw4.c" with `–g` option and run gdb to execute each instruction one by one. Use `p` or `x` to check the value of a variable.

```bash
$ gcc -g -o hw4 hw4.c
$ gdb hw4
GNU gdb (GDB) Fedora (7.5.1-38.fc18)
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/sp22/12191765/lect6/hw4...done.
(gdb) b main
Breakpoint 1 at 0x4005c4: file hw4.c, line 7.
(gdb) r
Starting program: /home/sp22/12191765/lect6/hw4

Breakpoint 1, main () at hw4.c:7
7           x = open("f2", O_RDONLY, 00777); // open f2 for reading
Missing separate debuginfos, use: debuginfo-install glibc-2.16-31.fc18.x86_64
(gdb) list
2       #include <stdio.h>
3
4       int main() {
5           int x, y;
6           char buf[20];
7           x = open("f2", O_RDONLY, 00777); // open f2 for reading
8           for (;;) {
9               y = read(x, buf, 1); // read next byte
10              if (y == 0)
11                  break; // we read all, exit the loop
(gdb) n
9               y = read(x, buf, 1); // read next byte
(gdb) p x
$1 = 7
(gdb) n
10              if (y == 0)
(gdb) p y
$2 = 1
(gdb) p buf[0]
$3 = 73 'I'
(gdb) x/4xb buf
0x7fffffffe420: 0x49    0x06    0x40    0x00
(gdb) n
12              printf("%x %d %c\n", buf[0], buf[0], buf[0]); // display
(gdb) list
7           x = open("f2", O_RDONLY, 00777); // open f2 for reading
8           for (;;) {
9               y = read(x, buf, 1); // read next byte
10              if (y == 0)
11                  break; // we read all, exit the loop
12              printf("%x %d %c\n", buf[0], buf[0], buf[0]); // display
13          }
14          return 0;
15      }
(gdb) b 15
Breakpoint 2 at 0x400632: file hw4.c, line 15.
(gdb) c
Continuing.
49 73 I
20 32
68 104 h
61 97 a
76 118 v
...
75 117 u
61 97 a
6c 108 l
2e 46 .
a 10


Breakpoint 2, main () at hw4.c:15
15      }
(gdb)
Continuing.
[Inferior 1 (process 11506) exited normally]
(gdb) q
```

GCC의 `-g` 옵션은 GDB에 정보를 제공하는 바이너리를 삽입하는 플래그다.
`gdb <filename>`을 통해 프로그램을 GDB로 디버깅할 수 있다.
`b`로 프로그램의 중단점을 설정할 수 있다.
중단점을 만날 때까지 계속 진행하는 `c` 명령과 같이 사용할 수 있다.
`p`는 변수의 값, 함수의 주소값을 볼 수 있는 포인트 명령어다.
`x`는 특정 범위의 메모리 값을 확인하는 명령어이다.

### 6. Write a program that creates a file and writes "hello there" in it. Use `open()` and `write()`. Confirm the result with `cat`.

See [HW 6](./hw06/main.c)

```bash
$ cat f3
hello there
```

`write`는 file descriptor를 이용해 파일에 주어진 바이트만큼 기록하고 저장하는 함수이다.
`cat`으로 "f3"에 저장된 내용을 확인하면 "hello there"이 정상적으로 기록된 것을 볼 수 있다.

### 7. Write a program that makes a copy for file "hw4.c" into another file "cphw4.c". Use `open()`, `read()`, and `write()`. Confirm that they are same with `cat` and `ls -l`.

See [HW 7](./hw07/main.c)

```bash
$ cat cphw4.c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int x, y;
    char buf[20];
    x = open("f2", O_RDONLY, 00777); // open f2 for reading
    for (;;) {
        y = read(x, buf, 1); // read next byte
        if (y == 0)
            break; // we read all, exit the loop
        printf("%x %d %c\n", buf[0], buf[0], buf[0]); // display
    }
    return 0;
}
```

"hw4.c"를 "cphw4.c" 이름으로 복사하는 프로그램의 소스코드이다.
`O_RDONLY`은 파일을 Read-only 모드로 여는 것을 뜻한다.
`O_RDWR | O_CREAT | O_TRUNC`는 파일이 없다면 새로 만들고, 존재한다면 내용을 덮어쓰는 모드이다.
`00777`으로 파일을 생성한다면 rwxrwxrwx 권한으로 파일을 생성할 것을 명령한다.

### 8. Write a program that makes a copy for file "hw4" (the executable file for "hw4.c") into another file "cphw4". Confirm that they are same with `xxd` and `ls -l`.

Execute cphw4 to see if it runs ok.

See [HW 8](./hw08/main.c)

```bash
$ xxd cphw4
0000000: 7f45 4c46 0201 0100 0000 0000 0000 0000  .ELF............
0000010: 0200 3e00 0100 0000 d004 4000 0000 0000  ..>.......@.....
0000020: 4000 0000 0000 0000 a014 0000 0000 0000  @...............
0000030: 0000 0000 4000 3800 0900 4000 2400 2100  ....@.8...@.$.!.
0000040: 0600 0000 0500 0000 4000 0000 0000 0000  ........@.......
...
0002690: 2e35 005f 4a76 5f52 6567 6973 7465 7243  .5._Jv_RegisterC
00026a0: 6c61 7373 6573 005f 5f54 4d43 5f45 4e44  lasses.__TMC_END
00026b0: 5f5f 005f 4954 4d5f 7265 6769 7374 6572  __._ITM_register
00026c0: 544d 436c 6f6e 6554 6162 6c65 005f 696e  TMCloneTable._in
00026d0: 6974 00                                  it.
$ ls -l | grep hw4$
-r-xr-x--T. 1 12191765 12191765 9939 Apr  7 11:04 cphw4
-rwxrwxr-x. 1 12191765 12191765 9939 Apr  7 10:44 hw4
$ ./cphw4
49 73 I
20 32
68 104 h
61 97 a
76 118 v
65 101 e
20 32
61 97 a
20 32
64 100 d
...
71 113 q
75 117 u
61 97 a
6c 108 l
2e 46 .
a 10
```

"hw4"를 "cphw4" 이름으로 복사하는 프로그램의 소스코드이다.
7번의 소스코드를 수정해 작성했다.
`while`을 이용해 코드를 간결하게 만들고 사용한 file descriptor를 정리해 재사용할 수 있게 해주는 `close` 함수를 호출해 사용한 리소스를 수거했다.
`xxd cphw4`으로 파일 내용이 같음을 확인있다.
`ls -l`는 `grep`을 이용해 "hw4"으로 끝나는 파일만 필터링해 표시했다.
마지막으로 직접 "cphw4"을 실행했을 때 "hw4"와 같은 결과가 나옴을 확인했다.

### 9. Repeat 7). But get the name of the files from the user. Confirm that the result of copy with `cat` and `ls -l`.

See [HW 9](./hw09/main.c)

```bash
$ ./hw
Enter src file name
hw4.c
Enter dest file name
newh4.c
hw4.c is copied into newh4.c successfully.
$ cat newh4.c
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int x, y;
    char buf[20];
    x = open("f2", O_RDONLY, 00777); // open f2 for reading
    for (;;) {
        y = read(x, buf, 1); // read next byte
        if (y == 0)
            break; // we read all, exit the loop
        printf("%x %d %c\n", buf[0], buf[0], buf[0]); // display
    }
    return 0;
}
```

8번과 유사하지만, 사용자에게 파일이름을 입력받을 수 있게 했다.
`fgets`를 이용해 띄어쓰기가 포함된 경로를 입력받을 수 있다.

### 10. Write "mycat" that displays the contents of a user-input file in the terminal in characters. Give a text file and a non-text file to "mycat" and explain the difference.

See [HW 10](./hw10/main.c)

```bash
$ ./mycat
Enter file name
f1
The content of f1 is:
I have a dream
that one day this nation
will rise up and
live out the true
meaning of its creed
that all men are created equal.
$ ./mycat
Enter file name
hw4
The content of hw4 is:
ELF>▒@@▒@8      @$!@@@@@▒88@8@@@
 ``48 ((`(`▒TT@T@DDP▒td@@44Q▒tR▒td``▒▒/lib64/ld-linux-x86-64.so.2GNU GNU▒.$▒9b▒֋Z▒▒B+SKu?▒▒!+ &__gmon_start__libc.so.6printfreadopen__libc_start_mainGLIBC_2.2.5ui      =▒`` `(`0`8`H▒H▒▒
...
```

9번에서 파일을 기록하는 부분을 `printf` 함수로 수정해 파일의 내용이 터미널에 기록되게 했다.
텍스트 파일은 내용물이 잘 나왔지만 실행 파일은 문자가 깨져서 나왔다.

### 11. Write "myxxd" that displays the contents of a user-input file in the terminal in hexadecimal numbers. Give a text file and a non-text file to "myxxd" and explain the difference. You need to use `printf("%x ", buf[i])` to display a byte in a hexadecimal number. Also declare the buffer as an array of unsigned char.

See [HW 11](./hw11/main.c)

```bash
$ ./myxxd
Enter file name
f1
The content of f1 is:
49 20 68 61 76 65 20 61 20 64 72 65 61 6d a 74 68 61 74 20 6f 6e 65 20 64 61 79 20 74 68 69 73 20 6e 61 74 69 6f 6e a 77 69 6c 6c 20 72 69 73 65 20 75 70 20 61 6e 64 a 6c 69 76 65 20 6f 75 74 20 74 68 65 20 74 72 75 65 a 6d 65 61 6e 69 6e 67 20 6f 66 20 69 74 73 20 63 72 65 65 64 a 74 68 61 74 20 61 6c 6c 20 6d 65 6e 20 61 72 65 20 63 72 65 61 74 65 64 20 65 71 75 61 6c 2e a
$ ./myxxd
Enter file name
hw4
The content of hw4 is:
7f 45 4c 46 2 1 1 0 0 0 0 0 0 0 0 0 2 0 3e 0 1 0 0 0 d0 4 40 0 0 0 0 0 40 0 0 0 0 0 0 0 a0 14 0 0 0 0 0 0 0 0 0 0 40 0 38 0 9 0 40 0 24 0 21 0 6 0 0 0 5 0 0 0 40 0 0 0 0 0 0 0 40 0 40 0 0 0 0 0 40 0 40 0 0 0 0 0 f8 1 0 0 0 0 0 0 f8 1 0 0 0 0 0 0 8 0 0 0 0 0 0 0 3 0 0 0 4 0 0 0 38 2 0 0 0 0 0 0 38 2 40 0 0 0 0 0 38 2 40 0 0 0 0 0 1c 0 0 0 0 0 0 0 1c 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 5 0 0 0 0 0 0 0 0 0 0 0 0 0 40 0 0 0 0 0 0 0 40 0 0 0 0 0 c...
```

10번 코드에서 반복문으로 주어진 문자열의 끝까지 문자를 순회하는 코드를 작성하고 `printf`에 `%x`으로 포매팅해 16진수로 출력할 수 있게 했다.
`unsigned char`로 오버플로우로 인한 버그가 생기지 않게 했다.
텍스트 파일과 실행 파일 모두 파일이 깨지지 않고 잘 열렸다.

### 12. Run following code and display "f8" with `cat` and `xxd` respectively. Explain the results.

```c
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd = open("f8", O_WRONLY | O_CREAT | O_TRUNC, 00777);
    write(fd, "ab", 2);
    int y = 10;
    write(fd, &y, 4);
    write(fd, "cd", 2);
    y = 235;
    write(fd, &y, 4);
    close(fd);
    return 0;
}
```

```bash
$ cat f8
ab
cd▒
$ xxd f8
0000000: 6162 0a00 0000 6364 eb00 0000            ab....cd....
```

`cat`으로 "f8"을 출력하면 글자가 깨져서 잘 알아볼 수 없다.
`xxd`로 보면 6162로 시작하는 것으로 보아 "ab"가 맨 앞에 기록된 것을 확인할 수 있다.
그다음 "0a"(\n)으로 줄 바꿈이 되었고 그 뒤 3(=4-1)칸이 0으로 채워졌다.
마찬가지로 "cd"기 6364로 기록되었고 그 뒤 "235"(ë) 아스키코드가 기록되었지만 터미널에선 글자가 깨져 확인할 수 없었다.
마지막으로 3칸이 0으로 채워졌다.

### 13. Write a program that divides a given file into three small files of roughly equal size. Use `fstat()` to find out the size of a file.

See [HW 13](./hw13/main.c)

```bash
$ ./hw
Enter file name to split
f9
f9 is split into f91, f92, and f93.
$ cat f91
I have a dream
that one day this nation
wi
$ cat f92
ll rise up and
live out the true
meaning o
$ cat f93
f its creed
that all men are created equal.
```

`fstat`는 `stat` 구조체에 파일 정보를 입력하는 함수이다.
파일의 전체 크기를 구해 `total_size`에 저장하고 3으로 나눈 값을 `segment_size`에 저장했다.
첫 번째, 두 번째 파일은 `segment_size`만큼 원본 파일에서 읽어 들여 저장하고 마지막 파일을 `total_size - segment_size * 2`으로 남은 부분을 전부 읽어 저장할 수 있게 했다.

### 14. What is wrong with following program?

```c
#include <stdio.h>

int main(void) {
    char temp0[20], *temp1[10], *temp2[10];
    printf("enter src file name\n");
    gets(temp0);
    temp1[0] = temp0;
    printf("enter dest file name\n");
    gets(temp0);
    temp2[0] = temp0;
    printf("src file:%s dest file:%s\n", temp1[0], temp2[0]);
    return 0;
}
```

`temp1[0]`과 `temp2[0]`에 `temp0`의 시작지점 포인터를 기록하게 하는 동작인데, 내용물을 복사하지 않아 두 번째 `gets(temp0);`에서 `temp0` 값이 덮어 씌워져 `temp1[0]`과 `temp2[0]`이 같은 값을 같게 된다.
아래와 같이 `strcpy`로 파일 내용을 복사해 해결할 수 있다.

See [HW 14](./hw14/main.c)

### 15. What is wrong with following program. Find the problem with GDB and fix it.

```c
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int x, x1;
    x = open("f1", O_RDONLY, 00777);
    x1 = open("f2", O_WRONLY | O_CREAT | O_TRUNC, 00777);
    char buf[512];
    int cnt = 0;
    int y;
    for (;;) {
        y = read(x, buf, 1);
        if (y == 0)
            break;
        cnt++;
    }
    write(x1, buf, cnt);
    return 0;
}
```

GCC에서 `-g` 플래그와 함께 컴파일하고 GDB로 디버깅했다.

```bash
$ gdb hw
GNU gdb (GDB) Fedora (7.5.1-38.fc18)
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/sp22/12191765/lect6/hw...done.
(gdb) b main
Breakpoint 1 at 0x4005c7: file hw15.c, line 6.
(gdb) r
Starting program: /home/sp22/12191765/lect6/hw

Breakpoint 1, main () at hw15.c:6
6           x = open("f1", O_RDONLY, 00777);
Missing separate debuginfos, use: debuginfo-install glibc-2.16-31.fc18.x86_64
(gdb) b 11
Breakpoint 2 at 0x400606: file hw15.c, line 11.
(gdb) c
Continuing.

Breakpoint 2, main () at hw15.c:12
12              y = read(x, buf, 1);
(gdb) x/8xb buf
0x7fffffffe240: 0x03    0x00    0x00    0x00    0x00    0x00    0x00    0x00
(gdb) c
Continuing.

Breakpoint 2, main () at hw15.c:12
12              y = read(x, buf, 1);
(gdb) x/8xb buf
0x7fffffffe240: 0x49    0x00    0x00    0x00    0x00    0x00    0x00    0x00
(gdb) c
Continuing.

Breakpoint 2, main () at hw15.c:12
12              y = read(x, buf, 1);
(gdb) x/8xb buf
0x7fffffffe240: 0x20    0x00    0x00    0x00    0x00    0x00    0x00    0x00
...
```

`read`가 실행될 때 마다 `buf[0]`의 맨 앞만 덮어 씌워지는 것을 볼 수 있다.
`buf`에 `cnt`를 더해 읽은 값을 저장하는 위치를 한 칸씩 뒤로 움직이게 해서 수정했다.

See [HW 15](./hw15/main.c)

마찬가지로 GCC에서 `-g` 플래그와 함께 컴파일하고 GDB로 프로그램이 잘 수정되었는지 확인했다.

```bash
$ gdb hw
GNU gdb (GDB) Fedora (7.5.1-38.fc18)
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/sp22/12191765/lect6/hw...done.
(gdb) b main
Breakpoint 1 at 0x4005c7: file hw15-0.c, line 6.
(gdb) r
Starting program: /home/sp22/12191765/lect6/hw

Breakpoint 1, main () at hw15-0.c:6
6           x = open("f1", O_RDONLY);
Missing separate debuginfos, use: debuginfo-install glibc-2.16-31.fc18.x86_64
(gdb) b 11
Breakpoint 2 at 0x400601: file hw15-0.c, line 11.
(gdb) c
Continuing.

Breakpoint 2, main () at hw15-0.c:12
12              y = read(x, buf + cnt, 1);
(gdb) x/8xb buf
0x7fffffffe240: 0x03    0x00    0x00    0x00    0x00    0x00    0x00    0x00
(gdb) c
Continuing.

Breakpoint 2, main () at hw15-0.c:12
12              y = read(x, buf + cnt, 1);
(gdb) x/8xb buf
0x7fffffffe240: 0x49    0x00    0x00    0x00    0x00    0x00    0x00    0x00
(gdb) c
Continuing.

Breakpoint 2, main () at hw15-0.c:12
12              y = read(x, buf + cnt, 1);
(gdb) x/8xb buf
0x7fffffffe240: 0x49    0x20    0x00    0x00    0x00    0x00    0x00    0x00
(gdb) c
Continuing.

Breakpoint 2, main () at hw15-0.c:12
12              y = read(x, buf + cnt, 1);
(gdb) x/8xb buf
0x7fffffffe240: 0x49    0x20    0x68    0x00    0x00    0x00    0x00    0x00
(gdb) c
Continuing.

Breakpoint 2, main () at hw15-0.c:12
12              y = read(x, buf + cnt, 1);
(gdb) x/8xb buf
0x7fffffffe240: 0x49    0x20    0x68    0x61    0x00    0x00    0x00    0x00
...
```

`buf`에 값이 앞에서부터 차례대로 기록되는 것을 확인할 수 있다.
