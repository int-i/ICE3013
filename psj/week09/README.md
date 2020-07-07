# Exec, Exit, Wait 1

## Homework

### 1. Try below and explain why the output is "I am ex01" when "ex2" runs.

See [HW 1](./hw01/)

```bash
$ gcc -o ex01 hw01/ex01.c
$ gcc -o ex02 hw01/ex02.c
$ ./ex02
I am ex01
```

`execve`가 "ex02" 프로세스를 "ex01" 프로세스로 덮어씌웠다.
따라서 `execve` 이후의 "I am ex02"가 출력되지 않고 "ex01"의 "I am ex01"가 출력되었다.

### 2. Run "myexec" below. Explain the result.

See [HW 2](./hw02/main.c)

```bash
$ ./myexec
ex01  ex02  hw01_01_01.c  hw01_01_02.c  hw01_02.c  myexec
```

`argv`는 마지막에 `NULL`을 넣어 배열의 끝을 알려줘야 한다.
`execve`는 파일이름, 실행인자 배열, 환경 배열을 인자로 받는다.

### 3-1. Run "myexec" below and explain the result.

See [HW 3-1](./hw03_01/main.c)

The above program will exec to `/bin/cat f1` which will print the contents of f1.

```bash
$ ./myexec
asdf
```

`argv`는 `main`의 `argv`와 같이 공백을 기준으로 값을 나눠서 배열에 집어넣어야 한다.
출력 결과는 `/bin/cat f1`의 실행 결과와 같다.

### 3-2. Change "myexec" such that it execs to `/bin/ls -l`.

See [HW 3-2](./hw03_02/main.c)

```bash
$ ./myexec
total 60
-rwxrwxr-x. 1 12191765 12191765 8508 May 12 10:35 ex01
-rwxrwxr-x. 1 12191765 12191765 8560 May 12 10:46 ex02
-rw-rw-r--. 1 12191765 12191765    5 May 12 11:02 f1
-rw-rw-r--. 1 12191765 12191765    5 May 12 11:03 f2
-rw-rw-r--. 1 12191765 12191765   79 May 12 10:34 hw01_01_01.c
-rw-rw-r--. 1 12191765 12191765  133 May 12 10:46 hw01_01_02.c
-rw-rw-r--. 1 12191765 12191765  137 May 12 10:42 hw01_02.c
-rw-rw-r--. 1 12191765 12191765  207 May 12 11:06 hw01_03.c
-rwxrwxr-x. 1 12191765 12191765 8557 May 12 11:06 myexec
```

3-1과 마찬가지로 공백 단위로 명령어를 끊어 배열에 집어넣는다.
출력 결과는 `/bin/ls -l`의 실행 결과와 같다.

### 3-3. Change "myexec" such that it execs to `/bin/cp f1 f2`.

See [HW 3-3](./hw03_03/main.c)

```bash
$ cat f1
asdf
$ ./myexec
$ cat f2
asdf
```

3-1과 마찬가지로 공백 단위로 명령어를 끊어 배열에 집어넣는다.
실행 결과는 `/bin/cp f1 f2`의 실행 결과와 같다.

### 3-4. Change "myexec" such that it runs `/bin/ls -l` and prints "job done" after `/bin/ls -l` is finished.

See [HW 3-4](./hw03_04/main.c)

```bash
$ ./myexec
total 60
-rwxrwxr-x. 1 12191765 12191765 8508 May 12 10:35 ex01
-rwxrwxr-x. 1 12191765 12191765 8560 May 12 10:46 ex02
-rw-rw-r--. 1 12191765 12191765    5 May 12 11:02 f1
-rw-rw-r--. 1 12191765 12191765    5 May 12 11:03 f2
-rw-rw-r--. 1 12191765 12191765   79 May 12 10:34 hw01_01_01.c
-rw-rw-r--. 1 12191765 12191765  133 May 12 10:46 hw01_01_02.c
-rw-rw-r--. 1 12191765 12191765  137 May 12 10:42 hw01_02.c
-rw-rw-r--. 1 12191765 12191765  207 May 12 11:06 hw01_03.c
-rwxrwxr-x. 1 12191765 12191765 8557 May 12 11:06 myexec
job done
```

`execve`는 프로세스를 덮어쓰기 때문에 `ls -l` 이후 `print`가 호출되지 않는다.
따라서 `fork`를 이용해 새로운 프로세스를 만들어 명령어를 실행시키고 부모 프로세스는 `wait`로 자식 프로세스가 종료되길 기다려야한다.
`wait`의 인자는 status 포인터지만 여기에서는 자식 프로세스의 종료 결과를 사용하지 않을 것이기 때문에 `NULL`을 대입했다.

### 3-5. Change "myexec" such that it reads a command and execs to the given command.

See [HW 3-5](./hw03_05/main.c)

```bash
$ cat f1
asdf
$ ./myexec
command> /bin/cat f1
asdf
$ ./myexec
command> /bin/cp f1 f2
$ cat f2
asdf
```

`fgets`를 이용해 사용자의 입력을 받고 `strtok`으로 공백 단위로 토큰을 나눈다.
토큰을 `execve`에 넘겨 명령어를 실행시킨다.

### 3-6. Same as 3-5), but "myexec" will repeat the process 5 times.

See [HW 3-6](./hw03_06/main.c)

```bash
$ ./myexec
command> /bin/cat f1
asdf
command> /bin/ls
ex01  ex02  f1  f2  hw01_01_01.c  hw01_01_02.c  hw01_02.c  hw01_03.c  myexec
command> /bin/ps -f
UID        PID  PPID  C STIME TTY          TIME CMD
12191765 15412 15411  0 09:45 pts/76   00:00:00 -bash
12191765 24590 15412  0 13:14 pts/76   00:00:00 ./myexec
12191765 24593 24590  0 13:15 pts/76   00:00:00 /bin/ps -f
command> /bin/echo hello
hello
command> /bin/echo hi
hi
```

3-5와 비슷하지만 반복문과 `fork`를 이용해 부모프로세스로 자식프로세스를 생성하고 기다리고 자식프로세스로 명령어를 실행시킨다.
마찬가지로 자식 프로세스의 종료 결과를 사용하지 않을 것이기 때문에 `wait`의 인자로 `NULL`을 대입했다.

### 3-7. Same as 3-6), but change the prompt to the current location and "$" as follows. You may need `getcwd`.

See [HW 3-7](./hw03_07/main.c)

```bash
$ ./myexec
/home/sp22/12191765/lect10$ /bin/cat f1
asdf
/home/sp22/12191765/lect10$ /bin/ls
ex01  ex02  f1  f2  hw01_01_01.c  hw01_01_02.c  hw01_02.c  hw01_03.c  myexec
/home/sp22/12191765/lect10$ /bin/ps -f
UID        PID  PPID  C STIME TTY          TIME CMD
12191765 15412 15411  0 09:45 pts/76   00:00:00 -bash
12191765 25640 15412  0 14:24 pts/76   00:00:00 ./myexec
12191765 25649 25640  0 14:25 pts/76   00:00:00 /bin/ps -f
/home/sp22/12191765/lect10$ /bin/echo hello
hello
/home/sp22/12191765/lect10$ /bin/echo hi
hi
```

`getcwd`는 현재 작업 디렉토리를 가져오는 함수이다.
3-6에서 `printf("command> ");` 부분만 `printf("%s$ ", dirname);`으로 고쳐주면 된다.
