# Exec, Exit, Wait 2

## Homework

### 1. Try the shell example. What is the difference between your shell and the system shell?

See [HW 1](./hw01/main.c)

```bash
$ ./hw01
$ /bin/ls
I am child to execute /bin/ls
ex01  f1  hw01    hw01_01_01.c  hw01_02.c  myexec
ex02  f2  hw01.c  hw01_01_02.c  hw01_03.c
$ ls
I am child to execute ls
Fail to execute: No such file or directory
...
```

명령어를 10개까지만 실행시킬 수 있고 `cp f1 f2` 같이 인자가 주어지는 명령어는 실행시킬 수 없다.
또한, 명령어에 "/bin/ls"와 같이 실행파일의 전체 경로를 써줘야 한다.

### 2. Find all ancestor processes of your shell.

```bash
$ ps -f
UID        PID  PPID  C STIME TTY          TIME CMD
12191765  4197  4196  0 23:23 pts/58   00:00:00 -bash
12191765  4593  4197  0 23:38 pts/58   00:00:00 ./hw01
12191765  4602  4197  0 23:38 pts/58   00:00:00 ps -f
$ pstree -sp 4593
sshd(4192)───sshd(4196)───bash(4197)───hw01(4593)
```

`pstree`를 이용하면 프로세스의 부모-자식 구조를 트리형태로 볼 수 있다.

`-s`는 "show parents"로 선택된 프로세스의 부모를 같이 보여주고, `-p`는 "show pids"로 PID를 함께 출력하는 옵션이다.

즉, 위 명령은 PID인 4593 인 "hw01"와 부모 프로세스를 PID와 함께 출력하는 명령이다.

### 3. (Builtin Command) Change the shell such that it exits when the user types "exit".

See [HW 3](./hw03/main.c)

```bash
$ ./hw03
$ /bin/ls
I am child to execute /bin/ls
ex01  f1  hw01    hw01_01_01.c  hw01_02.c  hw03    myexec
ex02  f2  hw01.c  hw01_01_02.c  hw01_03.c  hw03.c
$ exit
```

`exit`은 프로그램을 종료시키는 명령으로 `fork`가 실행되기 전에 `strcmp`로 명령을 검사해야 부모 프로세스를 종료시킬 수 있다.

### 4. Change the shell such that it can handle a command with arguments. Use `gets()` or `fgets()` to read the command.

See [HW 4](./hw04/main.c)

```bash
$ ./hw04
$ /bin/ls
I am child to execute /bin/ls
ex01  f1  hw01    hw01_01_01.c  hw01_02.c  hw03    hw04    myexec
ex02  f2  hw01.c  hw01_01_02.c  hw01_03.c  hw03.c  hw04.c
$ /bin/ls -l
I am child to execute /bin/ls
total 108
-rwxrwxr-x. 1 12191765 12191765 8508 May 12 10:35 ex01
-rwxrwxr-x. 1 12191765 12191765 8560 May 12 10:46 ex02
-rw-rw-r--. 1 12191765 12191765    5 May 12 11:02 f1
-rw-rw-r--. 1 12191765 12191765    5 May 12 12:58 f2
-rwxrwxr-x. 1 12191765 12191765 8869 May 13 09:05 hw01
-rw-rw-r--. 1 12191765 12191765  682 May 13 09:05 hw01.c
-rw-rw-r--. 1 12191765 12191765   79 May 12 10:34 hw01_01_01.c
-rw-rw-r--. 1 12191765 12191765  133 May 12 10:46 hw01_01_02.c
-rw-rw-r--. 1 12191765 12191765  137 May 12 10:42 hw01_02.c
-rw-rw-r--. 1 12191765 12191765  828 May 12 14:24 hw01_03.c
-rwxrwxr-x. 1 12191765 12191765 8921 May 13 09:19 hw03
-rw-rw-r--. 1 12191765 12191765  659 May 13 09:19 hw03.c
-rwxrwxr-x. 1 12191765 12191765 9008 May 13 09:25 hw04
-rw-rw-r--. 1 12191765 12191765  897 May 13 09:25 hw04.c
-rwxrwxr-x. 1 12191765 12191765 8909 May 12 14:24 myexec
$ /bin/cat f1 f2
I am child to execute /bin/cat
asdf
asdf
$ exit
```

`fgets`로 사용자로부터 공백을 포함한 명령어 전체를 받아올 수 있다.
그 후, `strtok`를 이용해 공백 단위로 명령을 나눠주고 Null Terminated Array 형태로 만들어 `execve`에 전달하면 된다.

### 5. (Handling &) Change the shell such that it can handle "&" at the end of the command.

See [HW 5](./hw05/main.c)

```bash
$ ./hw04
$ loop
I am child to execute loop
^C
$ ./hw05
$ loop &
I am child to execute loop
$ /bin/ls
I am child to execute /bin/ls
ex01  f2      hw01_01_01.c  hw01_03.c  hw04    hw05.c  myexec
ex02  hw01    hw01_01_02.c  hw03       hw04.c  loop
f1    hw01.c  hw01_02.c     hw03.c     hw05    loop.c
$ exit
```

사용자로부터 받아온 명령어의 마지막 토큰의 첫 글자가 "&"인지 확인하는 방식으로 명령어의 백그라운드 여부를 결정했다.
만약, 명령어를 백그라운드에서 실행해야 된다면 자식 프로세스의 종료를 기다리지 않고 다음 명령을 입력 받을 수 있게하고, 백그라운드 명령이 아니라면 `wait` 함수를 이용해 자식 프로세스가 종료되길 기다린다.

### 6. (Handling relative path) Make your shell handle relative paths assuming the executable file always exists in "/bin" directory. When the user enters only the command name (e.g. `ls -l`, `cp f1 f2`, etc), build a full path such as "/bin/ls", "/bin/cp", etc. and perform exec. Use `sprintf()` to build the full path.

See [HW 6](./hw06/main.c)

```bash
$ ./hw06
$ ls
I am child to execute ls
ex01  f2      hw01_01_01.c  hw01_03.c  hw04    hw05.c  loop
ex02  hw01    hw01_01_02.c  hw03       hw04.c  hw06    loop.c
f1    hw01.c  hw01_02.c     hw03.c     hw05    hw06.c  myexec
$ /bin/ls
I am child to execute /bin/ls
ex01  f2      hw01_01_01.c  hw01_03.c  hw04    hw05.c  loop
ex02  hw01    hw01_01_02.c  hw03       hw04.c  hw06    loop.c
f1    hw01.c  hw01_02.c     hw03.c     hw05    hw06.c  myexec
$ exit
```

`sprintf` 함수는 문자열을 특정 포맷으로 만들어주는 함수이다.

입력 받은 명령의 실행 파일의 경로가 "." 또는 "/"으로 시작한다면 이는 파일의 모든 경로를 입력한 것이므로 경로 앞에 "/bin"을 붙일 필요가 없다.
하지만 경로가 "." 또는 "/"으로 시작하지 않는다면, 이는 "/bin" 폴더의 실행 파일을 가리키는 것으로 유추할 수 있다.

따라서 `sprintf` 함수로 경로 앞에 "/bin"을 붙여 `execve` 함수에 전달함으로써 해결할 수 있다.

#### 6-1. `Use getenv("PATH")` to retrieve PATH environment variable and use `strtok()` to extract each system path. Display each system path line by line.

See [HW 6-1](./hw06_01/main.c)

```bash
$ ./hw06_01
/usr/lib64/ccache
/usr/local/bin
/usr/bin
/usr/local/sbin
/usr/sbin
/home/sp22/12191765/.local/bin
/home/sp22/12191765/bin
.
```

`getenv` 함수는 환경변수 문자열을 가져오는 함수이다.

`PATH` 환경 변수는 ":"으로 구분되어 있기 때문에 `strtok` 함수로 문자열을 잘라 출력하면 된다.

### 7. (Handling relative path) Change the shell such that it can handle relative path for the command in general. The shell will search the `PATH` environment variable to compute the full path of the command when it is given as a relative path name. Use `getenv("PATH")` to obtain the pointer to the value of the `PATH` environment variable. Note you need to copy the string of the `PATH` variable into another char array before you start extracting each path component with `strtok()` since `strtok()` destroys the original string.

See [HW 7](./hw07/main.c)

```bash
$ ./hw07
$ ls
I am child to execute ls
ex01  f2      hw01_01_01.c  hw01_03.c  hw04    hw05.c  hw07    loop.c
ex02  hw01    hw01_01_02.c  hw03       hw04.c  hw06    hw07.c  myexec
f1    hw01.c  hw01_02.c     hw03.c     hw05    hw06.c  loop
$ /bin/ls
I am child to execute /bin/ls
ex01  f2      hw01_01_01.c  hw01_03.c  hw04    hw05.c  hw07    loop.c
ex02  hw01    hw01_01_02.c  hw03       hw04.c  hw06    hw07.c  myexec
f1    hw01.c  hw01_02.c     hw03.c     hw05    hw06.c  loop
$ exit
```

6번의 코드를 재사용했다.
실행 파일 경로 앞에 "/bin"을 붙여주는 부분을 `PATH` 환경 변수를 붙여주게 수정하면 된다.
`execve` 함수는 실행에 실패할 시 -1을 반환하는 것을 이용해 `while`로 `execve` 함수 실행이 성공할 때까지 `env`를 바꿔가며 실행시키면 된다.

### 8. `dup(x)` duplicates `fd[x]` in the first empty entry in the `fd` table. Run following program and explain the output. Assume `f1` has "hello my boy".

See [HW 8](./hw08/main.c)

```bash
$ cat f1
hello my boy
$ ./hw08
old_fd=3, new_fd=4
buf=hello
buf= my b
```

`dup`는 파일 디스크립터를 복제하는 함수이다.
`old_fd`를 복제한 `new_fd`는 "f1"을 가리키는 파일 디스크립터로, 커서를 공유하며 파일을 연속적으로 읽기 때문에 위와 같은 결과가 나왔다.

### 9. (Standard output redirection) Explain the output of the following code.

See [HW 9](./hw09/main.c)

```bash
$ ./hw09
old_fd=3
$ cat f2
old_fd=3, new_fd=1
```

1은 표준 출력 파일 디스크립터를 의미한다.

파일 디스크립터는 작은 수부터 차례대로 할당하는데 `close`로 1짜리 파일 디스크립터를 비워줬기 때문에 `dup`로 복사되는 파일 디스크립터의 값은 1이 된다.
따라서 1은 표준 출력이 아닌 "f2"를 가리키는 파일 디스크립터의 복사본이 되었으므로, "hi there"은 표준 출력이 아닌 "f2"에 쓰여지게 된다.

### 10. (Standard output redirection) Change the shell such that it can handle standard output redirection.

See [HW 10](./hw10/main.c)

```bash
$ ./hw10
$ ls
I am child to execute ls
ex01  f3      hw01_01_01.c  hw03    hw05    hw07    hw09    loop
ex02  f4      hw01_01_02.c  hw03.c  hw05.c  hw07.c  hw09.c  loop.c
f1    hw01    hw01_02.c     hw04    hw06    hw08    hw10    myexec
f2    hw01.c  hw01_03.c     hw04.c  hw06.c  hw08.c  hw10.c
$ ls > f3
I am child to execute ls
$ cat f3
I am child to execute cat
ex01
ex02
f1
f2
f3
f4
hw01
hw01.c
hw01_01_01.c
hw01_01_02.c
hw01_02.c
hw01_03.c
hw03
hw03.c
hw04
hw04.c
hw05
hw05.c
hw06
hw06.c
hw07
hw07.c
hw08
hw08.c
hw09
hw09.c
hw10
hw10.c
loop
loop.c
myexec
$ exit
$ cat f3
ex01
ex02
f1
f2
f3
f4
hw01
hw01.c
hw01_01_01.c
hw01_01_02.c
hw01_02.c
hw01_03.c
hw03
hw03.c
hw04
hw04.c
hw05
hw05.c
hw06
hw06.c
hw07
hw07.c
hw08
hw08.c
hw09
hw09.c
hw10
hw10.c
loop
loop.c
myexec
```

`dup2` 함수는 파일 디스크립터를 대체하는 함수로, 기존 디스크립터로 가는 호출을 새로운 디스크립터로 가게 수정한다.
문제에서는 마지막에서 2번째 문자가 ">" 일 때, 표준 출력을 사용자가 지정한 파일 디스크립터로 대체해 `printf` 함수의 출력을 파일에 작성하게 했다. 
