# Process related System Call

## Homework

### 1. Try "hw01" below. Who is the parent of "hw01"?

See [HW 1](./hw01/main.c)

```bash
$ gcc -o hw01 hw01.c
$ ./hw01 &
[1] 23088
PID:23088, PPID:21406
$ ps -f
UID        PID  PPID  C STIME TTY          TIME CMD
12191765 21406 21405  0 10:18 pts/4    00:00:00 -bash
12191765 23088 21406 21 10:32 pts/4    00:00:14 ./hw01
12191765 23251 21406  0 10:33 pts/4    00:00:00 ps -f
$ kill 23088
```

`for(;;)`는 무한반복을 통해 프로세스를 종료되지 않고 유지할 수 있게 하는 코드이고, `&`는 bash에서 여러 개의 명령어를 추가적으로 실행할 수 있게 한다.
`ps` 명령어는 현재 사용되고 있는 프로세스 목록을 보여주는 함수로 `-f`는 목록을 포맷팅하여 보여주는 것을 의미한다.
`ps -f` 명령을 통해 사용 중인 프로세스 목록을 보면 "hw01" 프로그램의 PPID는 bash의 PID임을 알 수 있다.
따라서 "hw01"의 부모 프로세스는 bash이다.

### 2. Try "hw02" below. Why do we have two hello's? What are the PID of "hw02" and "hw02"'s child? Who is the parent of "hw02"?

See [HW 2](./hw02/main.c)

```bash
$ gcc -o hw02 hw02.c
$ ./hw02 &
[1] 23928
hello
hello
$ ps -f
UID        PID  PPID  C STIME TTY          TIME CMD
12191765 21406 21405  0 10:18 pts/4    00:00:00 -bash
12191765 23928 21406 13 10:39 pts/4    00:00:02 ./hw02
12191765 23929 23928 18 10:39 pts/4    00:00:03 ./hw02
12191765 23945 21406  0 10:39 pts/4    00:00:00 ps -f
$ kill 23928 23929
```

"hw02"가 `fork`로 프로세스를 복제했기 때문에 "hello"가 2번 출력된다.
`ps -f` 명령어를 통해 프로세스 PPID를 보면, bash를 PPID로 가지는 프로세스 23928이 부모 프로세스이고 프로세스 23929가 복제된 프로세스임을 알 수 있다.

### 3. Modify "hw02.c" such that it prints its own pid and the parent pid. Confirm the result with `ps -ef`. Who is the parent of the parent of "hw03"? Who is the parent of the parent of the parent of "hw03"? Follow the parent link until you reach PID 0 and show all of them.

See [HW 3](./hw03/main.c)

```bash
$ gcc -o hw03 hw03.c
$ ./hw03 &
[1] 24492
hello. my pid is 24492
and my parent pid is 21406
hello. my pid is 24493
and my parent pid is 24492
$ ps -ef | grep hw03
12191765 24492 21406 17 10:55 pts/4    00:00:02 ./hw03
12191765 24493 24492 17 10:55 pts/4    00:00:02 ./hw03
12191765 24498 21406  0 10:55 pts/4    00:00:00 grep --color=auto hw03
$ kill 24492 24493
```

`ps` 명령어의 `e` 옵션은 모든 프로세스를 출력하는 기능이다.
첫 번째, 두 번째 줄 출력에 해당하는 부모 프로세스는 PID가 24492이며 PPID는 bash의 PID인 21406이다.
나머지 출력인 자식 프로세스의 PID는 24493이며 PPID는 `fork`의 원본 프로세스의 PID인 24492이다.

### 4. Try below "hw04.c". Which "hello" is displayed by the parent and which "hello" is by the child?

See [HW 4](./hw04/main.c)

```bash
$ gcc -o hw04 hw04.c
$ ./hw04 &
[1] 24540
hello: 24541
hello: 0
$ ps -f
UID        PID  PPID  C STIME TTY          TIME CMD
12191765 21406 21405  0 10:18 pts/4    00:00:00 -bash
12191765 24540 21406 14 10:57 pts/4    00:00:01 ./hw04
12191765 24541 24540 16 10:57 pts/4    00:00:01 ./hw04
12191765 24553 21406  0 10:57 pts/4    00:00:00 ps -f
$ kill 24540 24541
```

`fork`는 성공할 경우 자식의 PID를 부모에게 전달하며, 자식은 0을 반환 받는다.
부모 프로세스의 `x`는 자식 프로세스 값인 24541이 저장될 것이고 `fork`로 인해 복제된 자식 프로세스의 `x`에는 0이 저장될 것이다.
따라서 첫 번째 hello는 부모 프로세스에서 출력된 것이며, 그 아래는 자식 프로세스에서 출력된 것이다.

### 5. Try below "hw05.c" and show all ancestor processes of "hw05" (parent, parent of parent, etc).

See [HW 5](./hw05/main.c)

```bash
$ gcc -o hw05 hw05.c
$ ./hw05 &
[1] 25511
hello: 25512
hello: 0
$ ps -f
UID        PID  PPID  C STIME TTY          TIME CMD
12191765 21406 21405  0 10:18 pts/4    00:00:00 -bash
12191765 25511 21406 14 11:19 pts/4    00:00:07 ./hw05
12191765 25512 25511 14 11:19 pts/4    00:00:07 ./hw05
12191765 25522 21406  0 11:19 pts/4    00:00:00 ps -f
$ kill 25511 25512
```

PPID를 따라가며 `ps`의 출력값을 읽어보면, bash 프로세스로부터 "hw05(25511)" 프로세스가 생성되었으며 "hw05(25511)"부터 "hw05(25512)" 프로세스가 생성되었다.

### 6. Try below "hw06.c". Which message was displayed by the parent and which one by the child?

See [HW 6](./hw06/main.c)

```bash
$ gcc -o hw06 hw06.c
$ ./hw06
hi: 25569
hello: 0
```

`x`는 `fork`로부터 반환된 값이기 때문에 `x`가 0이면 현재 프로세스는 자식 프로세스이고, 0이 아니면 부모 프로세스이다.
따라서 "hi"는 부모 프로세스에서 출력된 값이고, "hello"는 복제된 자식 프로세스에서 출력된 값이다.

### 7. Try below "hw07.c". How many "hello" do you see? Explain why you have that many "hello". Draw the process tree.

See [HW 7](./hw07/main.c)

```bash
$ gcc -o hw07 hw07.c
$ ./hw07
hello: 25736 25737
hello: 0 25738
hello: 0 0
hello: 25736 0
```

`fork`를 한 번하면 총 2개에 프로세스가 생성된다.
연속적으로 `fork`를 두 번 하게 되면, 처음에 생긴 프로세스 각각 `fork`를 수행하게 되므로 2^2개의 프로세스가 생성된다.
첫 번째 출력은 `x`, `y` 모두 0이 아니기 때문에 최초의 부모 프로세스로부터 생성된 것이다.
두 번째와 세 번째 출력은 `x`가 0이기 때문에 첫 번째 `fork`로 복사된 프로세스에서 생성된 것으로, 두 번째 출력은 1번만 복사된 것, 세 번째는 2번 복사된 프로세스이다.
마지막 출력은 부모 프로세스로부터 두 번째 `fork`에서 복사된 프로세스에서 출력된 것을 `x`는 0이 아니지만 `y`는 0임에서 알 수 있다.

### 8. Try below "hw08.c". How many "hello" do you see? Explain why you have that many "hello".

See [HW 8](./hw08/main.c)

```bash
$ gcc -o hw08 hw08.c
$ ./hw08
hello: 25893
hello: 0
hello: 25894
hello: 0
hello: 25895
hello: 0
```

첫 두 줄 "hello"는 최초의 부모 프로세스와 첫 번째 `fork`로부터 생성된 자식 프로세스로부터 출력되었다.
나머지 프로세스는 7번처럼 2개의 프로세스로부터 프로세스를 하나씩 생성했기 때문에 총 4개의 프로세스가 되고 각각의 프로세스가 "hello"을 출력하므로 총 2+2^2개의 "hello"가 출력된다.

### 9. Try below "hw09.c". When you run "hw09", how many processes run at the same time? Which process finishes first and which process finishes last? Show the finishing order of the processes. Run "hw09" again and compare the finishing order with that of the first run.

See [HW 9](./hw09/main.c)

```bash
$ gcc -std=c99 -o hw09 hw09.c
$ ./hw09
0-th child running 0-th iteration
1-th child running 0-th iteration
3-th child running 0-th iteration
parent exits
4-th child running 0-th iteration
2-th child running 0-th iteration
0-th child running 1-th iteration
1-th child running 1-th iteration
3-th child running 1-th iteration
4-th child running 1-th iteration
2-th child running 1-th iteration
0-th child running 2-th iteration
1-th child running 2-th iteration
3-th child running 2-th iteration
4-th child running 2-th iteration
2-th child running 2-th iteration
0-th child running 3-th iteration
1-th child running 3-th iteration
3-th child running 3-th iteration
4-th child running 3-th iteration
2-th child running 3-th iteration
0-th child running 4-th iteration
1-th child running 4-th iteration
3-th child running 4-th iteration
4-th child running 4-th iteration
2-th child running 4-th iteration
0-th child running 5-th iteration
1-th child running 5-th iteration
3-th child running 5-th iteration
4-th child running 5-th iteration
2-th child running 5-th iteration
0-th child running 6-th iteration
1-th child running 6-th iteration
3-th child running 6-th iteration
4-th child running 6-th iteration
2-th child running 6-th iteration
0-th child running 7-th iteration
1-th child running 7-th iteration
3-th child running 7-th iteration
4-th child running 7-th iteration
2-th child running 7-th iteration
0-th child running 8-th iteration
1-th child running 8-th iteration
3-th child running 8-th iteration
4-th child running 8-th iteration
2-th child running 8-th iteration
0-th child running 9-th iteration
1-th child running 9-th iteration
3-th child running 9-th iteration
4-th child running 9-th iteration
2-th child running 9-th iteration
```

`fork`를 총 5번 수행하므로 최종적으로는 하나의 부모 프로세스와 5개의 자식 프로세스가 생성된다.
부모 프로세스는 "parent exits"를 출력하고 자식 프로세스보다 먼저 종료된다.
이때 자식프로세스는 모두 고아 프로세스가 되어 PPID가 init 프로세스의 PID인 1을 가리키게 된다.

자식 프로세스는 0부터 9까지 순회하며 `printf`로 문자열을 출력한다.
이때 `fflush(stdout)`는 표준출력스트림을 비워주는 역할로, 버퍼에 문자열을 넣고 기다리지 말고 바로 출력하기 위해 사용한다.
`sleep(1)` 자식 프로세스가 부모 프로세스보다 나중에 종료됨을 보장하기 위해 프로세스 실행 시간에 딜레이를 넣은 것이다.
프로세스가 반복문 순회를 마쳤다면 `exit(EXIT_SUCCESS)`를 통해 자식 프로세스를 종료한다.
따라서 프로그램은 총 5개의 자식 프로세스로부터 5*10번 `printf`를 호출할 것이다.

### 10. If you delete `exit(0)` in "hw09.c", how many processes will be created? Confirm your answer by modifying the code such that each process displays its own pid.

See [HW 10](./hw10/main.c)

```bash
$ gcc -std=c99 -o hw10 hw10.c
$ ./hw10
0-th child running 0-th iteration(pid: 18713)
3-th child running 0-th iteration(pid: 18716)
parent exits
4-th child running 0-th iteration(pid: 18717)
2-th child running 0-th iteration(pid: 18715)
1-th child running 0-th iteration(pid: 18714)
0-th child running 1-th iteration(pid: 18713)
3-th child running 1-th iteration(pid: 18716)
4-th child running 1-th iteration(pid: 18717)
2-th child running 1-th iteration(pid: 18715)
1-th child running 1-th iteration(pid: 18714)
0-th child running 2-th iteration(pid: 18713)
3-th child running 2-th iteration(pid: 18716)
4-th child running 2-th iteration(pid: 18717)
2-th child running 2-th iteration(pid: 18715)
1-th child running 2-th iteration(pid: 18714)
0-th child running 3-th iteration(pid: 18713)
3-th child running 3-th iteration(pid: 18716)
4-th child running 3-th iteration(pid: 18717)
2-th child running 3-th iteration(pid: 18715)
1-th child running 3-th iteration(pid: 18714)
0-th child running 4-th iteration(pid: 18713)
3-th child running 4-th iteration(pid: 18716)
4-th child running 4-th iteration(pid: 18717)
2-th child running 4-th iteration(pid: 18715)
1-th child running 4-th iteration(pid: 18714)
0-th child running 5-th iteration(pid: 18713)
3-th child running 5-th iteration(pid: 18716)
4-th child running 5-th iteration(pid: 18717)
2-th child running 5-th iteration(pid: 18715)
1-th child running 5-th iteration(pid: 18714)
0-th child running 6-th iteration(pid: 18713)
3-th child running 6-th iteration(pid: 18716)
4-th child running 6-th iteration(pid: 18717)
2-th child running 6-th iteration(pid: 18715)
1-th child running 6-th iteration(pid: 18714)
0-th child running 7-th iteration(pid: 18713)
3-th child running 7-th iteration(pid: 18716)
4-th child running 7-th iteration(pid: 18717)
2-th child running 7-th iteration(pid: 18715)
1-th child running 7-th iteration(pid: 18714)
0-th child running 8-th iteration(pid: 18713)
3-th child running 8-th iteration(pid: 18716)
4-th child running 8-th iteration(pid: 18717)
2-th child running 8-th iteration(pid: 18715)
1-th child running 8-th iteration(pid: 18714)
0-th child running 9-th iteration(pid: 18713)
3-th child running 9-th iteration(pid: 18716)
4-th child running 9-th iteration(pid: 18717)
2-th child running 9-th iteration(pid: 18715)
1-th child running 9-th iteration(pid: 18714)
1-th child running 0-th iteration(pid: 18720)
3-th child running 0-th iteration(pid: 18722)
parent exits
parent exits
4-th child running 0-th iteration(pid: 18724)
4-th child running 0-th iteration(pid: 18723)
parent exits
2-th child running 0-th iteration(pid: 18721)
3-th child running 0-th iteration(pid: 18725)
parent exits
2-th child running 0-th iteration(pid: 18727)
parent exits
4-th child running 0-th iteration(pid: 18729)
4-th child running 0-th iteration(pid: 18726)
3-th child running 0-th iteration(pid: 18728)
1-th child running 1-th iteration(pid: 18720)
3-th child running 1-th iteration(pid: 18722)
4-th child running 1-th iteration(pid: 18724)
4-th child running 1-th iteration(pid: 18723)
2-th child running 1-th iteration(pid: 18721)
3-th child running 1-th iteration(pid: 18725)
2-th child running 1-th iteration(pid: 18727)
4-th child running 1-th iteration(pid: 18729)
3-th child running 1-th iteration(pid: 18728)
4-th child running 1-th iteration(pid: 18726)
...
$ ./hw10 | grep -c "iteration"
310
```

만약 `exit(EXIT_SUCCESS)`를 제거한다면 자식 프로세스가 10번 `printf`를 한 이후에 다시 상위 반복문으로 돌아와 새로운 자식 프로세스를 생성한다.
가장 말단의 자식만 `printf`를 할 수 있지만, 가장 말단의 자식 프로세스가 아니더라도 `fork`를 통해 새로운 프로세스를 계속 생성할 수 있다.

이는 이분법으로 증식하는 세포 같이 생각할 수 있다.
5회 반복 시 2^0+2^1+2^2+2^3+2^4개의 자식 프로세스가 생성되며, 따라서 31개의 자식 프로세스로부터 310번 `printf`가 호출될 것이다.
