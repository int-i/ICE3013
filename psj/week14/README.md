# Signal

## Homework

### 1. Try to kill "ex1" and "ex2" in Section 1 with `^C`. What happens? You cannot kill "ex2" with `^C`, just leave it and go to homework 1-1).

See [HW 1](./hw01/)

```bash
$ ./ex1
^C
$ ./ex2
^CI am ok
^CI am ok
^CI am ok
...
```

"ex1"은 Ctrl+C로 종료되지만 "ex2"는 종료되지 않고 계속 실행된다.
이는 `signal`로 `SIGINT`의 입력에 대해 동작을 덮어씌워 프로세스를 종료하는 기본 동작이 사라졌기 때문이다.

### 1-1. Open another putty window and find the pid of "ex2" by `ps -ef | grep 12345` where 12345 is your student ID. Suppose "ex2"'s pid is 334455. Send `SIGINT`(signal number 2) to "ex2" with `kill -2 334455` What happens? Explain the result.

```bash
$ ./ex2
^CI am ok
I am ok
```

```bash
$ ps -ef | grep 12191765
root      5596  1006  0 10:47 ?        00:00:00 sshd: 12191765 [priv]
12191765  5601  5596  0 10:47 ?        00:00:00 sshd: 12191765@pts/51
12191765  5602  5601  0 10:47 pts/51   00:00:00 -bash
root      7745  1006  0 11:12 ?        00:00:00 sshd: 12191765 [priv]
12191765  7752  7745  0 11:12 ?        00:00:00 sshd: 12191765@pts/126
12191765  7753  7752  0 11:12 pts/126  00:00:00 -bash
12191765  8678  5602  6 11:15 pts/51   00:00:01 ./ex2
12191765  8691  7753  0 11:15 pts/126  00:00:00 ps -ef
12191765  8692  7753  0 11:15 pts/126  00:00:00 grep --color=auto 12191765
$ kill -2 8691
```

`ps -ef | grep 12191765`으로 나의 계정에서 실행되는 프로세스 목록을 확인할 수 있다.

`kill -2 8691`으로 프로세스를 종료시키려 했지만 프로세스는 종료되지 않았다.

### 2. You can kill "ex2" as follows. Why SIGINT (signal 2) cannot kill ex2 while SIGTERM (signal 15) can?

```bash
$ ./ex2
^CI am ok
Terminated
```

```bash
$ ps -ef | grep 12191765
root      5596  1006  0 10:47 ?        00:00:00 sshd: 12191765 [priv]
12191765  5601  5596  0 10:47 ?        00:00:00 sshd: 12191765@pts/51
12191765  5602  5601  0 10:47 pts/51   00:00:00 -bash
root      7745  1006  0 11:12 ?        00:00:00 sshd: 12191765 [priv]
12191765  7752  7745  0 11:12 ?        00:00:00 sshd: 12191765@pts/126
12191765  7753  7752  0 11:12 pts/126  00:00:00 -bash
12191765  8860  5602  8 11:21 pts/51   00:00:00 ./ex2
12191765  8861  7753  0 11:21 pts/126  00:00:00 ps -ef
12191765  8862  7753  0 11:21 pts/126  00:00:00 grep --color=auto 12191765
$ kill -15 8860
```

`kill -15 8860`를 입력하지 프로세스가 종료되었다.

15는 `SIGTERM`으로 이 시그널에 대해서는 동작이 정의되지 않았기 때문에 기본 동작인 프로세스 종료가 실행되었다.

### 2-1. Change ex2.c as follows. Now compile and run "ex2" and try to kill it with `SIGINT` and `SIGTERM` in another window. Assume "ex2" has PID 334455. Explain the result.

See [HW 2-1](./hw02_01/ex2.c)

```bash
$ ./ex2
I am ok
I am ok
```

```bash
$ ps -ef | grep 12191765
root      5596  1006  0 10:47 ?        00:00:00 sshd: 12191765 [priv]
12191765  5601  5596  0 10:47 ?        00:00:00 sshd: 12191765@pts/51
12191765  5602  5601  0 10:47 pts/51   00:00:00 -bash
root      7745  1006  0 11:12 ?        00:00:00 sshd: 12191765 [priv]
12191765  7752  7745  0 11:12 ?        00:00:00 sshd: 12191765@pts/126
12191765  7753  7752  0 11:12 pts/126  00:00:00 -bash
12191765  9084  5602  8 11:24 pts/51   00:00:00 ./ex2
12191765  9092  7753  0 11:24 pts/126  00:00:00 ps -ef
12191765  9093  7753  0 11:24 pts/126  00:00:00 grep --color=auto 12191765
$ kill -2 9084
$ kill -15 9084
```

`signal`로 `SIGTERM`에 대한 동작을 정의하자 프로세스가 종료되지 않고 계속 실행된다.

시그널에 대한 동작이 정의되었기 때문에 기본 동작인 프로세스 종료가 호출되지 않는다.

### 3. You can also kill "ex2" by closing the terminal where "ex2" is running. Confirm this by first finding out the pid of "ex2" with `ps –ef | grep 1234` (assuming your student id is 1234) in another terminal, close the terminal where "ex2" is currently running, and find this pid again with `ps –ef | grep 1234` in the second window. Explain why "ex2" dies in this case.

```bash
$ ps -ef | grep 12191765
root      5596  1006  0 10:47 ?        00:00:00 sshd: 12191765 [priv]
12191765  5601  5596  0 10:47 ?        00:00:00 sshd: 12191765@pts/51
12191765  5602  5601  0 10:47 pts/51   00:00:00 -bash
root      7745  1006  0 11:12 ?        00:00:00 sshd: 12191765 [priv]
12191765  7752  7745  0 11:12 ?        00:00:00 sshd: 12191765@pts/126
12191765  7753  7752  0 11:12 pts/126  00:00:00 -bash
12191765  9226  7753  8 11:31 pts/126  00:00:02 ./ex2
12191765  9234  5602  0 11:32 pts/51   00:00:00 ps -ef
12191765  9235  5602  0 11:32 pts/51   00:00:00 grep --color=auto 12191765
(after closing terminal)
$ ps -ef | grep 12191765
root      5596  1006  0 10:47 ?        00:00:00 sshd: 12191765 [priv]
12191765  5601  5596  0 10:47 ?        00:00:00 sshd: 12191765@pts/51
12191765  5602  5601  0 10:47 pts/51   00:00:00 -bash
12191765  9240  5602  0 11:32 pts/51   00:00:00 ps -ef
12191765  9241  5602  0 11:32 pts/51   00:00:00 grep --color=auto 12191765
```

터미널을 종료하면 `SIGHUP` 프로세스에 시그널이 전달된다.

프로세스에 `SIGHUP`에 대한 동작은 정의되지 않았기 때문에 기본 동작인 프로세스 종료가 실행되었다.

### 4. How can you prevent "ex2" from being killed even when you close the terminal?

See [HW 4](./hw04/ex2.c)

```bash
$ ps -ef | grep 12191765
root      5596  1006  0 10:47 ?        00:00:00 sshd: 12191765 [priv]
12191765  5601  5596  0 10:47 ?        00:00:00 sshd: 12191765@pts/51
12191765  5602  5601  0 10:47 pts/51   00:00:00 -bash
root      9435  1006  0 11:38 ?        00:00:00 sshd: 12191765 [priv]
12191765  9449  9435  0 11:38 ?        00:00:00 sshd: 12191765@pts/95
12191765  9450  9449  0 11:38 pts/95   00:00:00 -bash
12191765  9593  9450  8 11:39 pts/95   00:00:00 ./ex2
12191765  9595  5602  0 11:39 pts/51   00:00:00 ps -ef
12191765  9596  5602  0 11:39 pts/51   00:00:00 grep --color=auto 12191765
(after closing terminal)
$ ps -ef | grep 12191765
root      5596  1006  0 10:47 ?        00:00:00 sshd: 12191765 [priv]
12191765  5601  5596  0 10:47 ?        00:00:00 sshd: 12191765@pts/51
12191765  5602  5601  0 10:47 pts/51   00:00:00 -bash
12191765  9593     1  8 11:39 ?        00:00:00 ./ex2
12191765  9605  5602  0 11:39 pts/51   00:00:00 ps -ef
12191765  9606  5602  0 11:39 pts/51   00:00:00 grep --color=auto 12191765
```

`signal`로 `SIGHUP`에 대한 동작을 프로세스 종료 이외의 것으로 정의하면 된다.

### 5. If you were successful in problem 4 in preventing "ex2" from being killed, how can you still kill "ex2"?

```bash
$ ps -ef | grep 12191765
root      5596  1006  0 10:47 ?        00:00:00 sshd: 12191765 [priv]
12191765  5601  5596  0 10:47 ?        00:00:00 sshd: 12191765@pts/51
12191765  5602  5601  0 10:47 pts/51   00:00:00 -bash
12191765  9593     1  8 11:39 ?        00:00:00 ./ex2
12191765  9605  5602  0 11:39 pts/51   00:00:00 ps -ef
12191765  9606  5602  0 11:39 pts/51   00:00:00 grep --color=auto 12191765
$ kill -9 9593
$ ps -ef | grep 12191765
root      5596  1006  0 10:47 ?        00:00:00 sshd: 12191765 [priv]
12191765  5601  5596  0 10:47 ?        00:00:00 sshd: 12191765@pts/51
12191765  5602  5601  0 10:47 pts/51   00:00:00 -bash
12191765 10140  5602  0 11:42 pts/51   00:00:00 ps -ef
12191765 10141  5602  0 11:42 pts/51   00:00:00 grep --color=auto 12191765
```

`kill -9 9593`으로 프로세스를 종료시킬 수 있다.

9는 `SIGKILL`로 새로운 동작을 정의할 수 없는 시그널이기 때문에 항상 프로세스를 종료시킨다.

### 6. Write a program("ex3.c") that forks two children as below. All three processes (the parent and the two children) run infinite loops. Run this program and find the pids of the three processes in another window. Kill the parent (`kill -15 parent-pid`) and observe what happens to the children.

See [HW 6](./hw06/ex3.c)

```bash
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
12191765  1228   337  2 09:01 pts/94   00:00:02 ./ex3
12191765  1232  1228  2 09:01 pts/94   00:00:02 ./ex3
12191765  1235  1228  2 09:01 pts/94   00:00:02 ./ex3
root      1238  1006  0 09:02 ?        00:00:00 sshd: 12191765 [priv]
12191765  1247  1238  0 09:02 ?        00:00:00 sshd: 12191765@pts/101
12191765  1248  1247  0 09:02 pts/101  00:00:00 -bash
12191765  1700  1248  0 09:03 pts/101  00:00:00 ps -ef
12191765  1701  1248  0 09:03 pts/101  00:00:00 grep --color=auto 12191765
$ kill -15 1228
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
12191765  1232     1  2 09:01 pts/94   00:00:03 ./ex3
12191765  1235     1  2 09:01 pts/94   00:00:03 ./ex3
root      1238  1006  0 09:02 ?        00:00:00 sshd: 12191765 [priv]
12191765  1247  1238  0 09:02 ?        00:00:00 sshd: 12191765@pts/101
12191765  1248  1247  0 09:02 pts/101  00:00:00 -bash
12191765  1724  1248  0 09:03 pts/101  00:00:00 ps -ef
12191765  1725  1248  0 09:03 pts/101  00:00:00 grep --color=auto 12191765
```

총 3개의 프로세스가 무한루프를 돌며 실행된다.

`kill -15 1228`으로 `SIGTERM`을 발생시켜 부모 프로세스를 죽이자 자식 프로세스의 PPID가 1이 되었다.
부모 프로세스가 자식 프로세스보다 먼저 종료되면 자식 프로세스는 고아 프로세스가 되며 PPID가 1로 변경된다.

### 7. Same as 6), but this time kill the shell of the terminal where ex3 is running with `kill -9 114455`, where 114455 is the pid of the shell. What happens to the three processes (the parent and the two children)? Why the three children die and how can you prevent the three processes from being killed?

```bash
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
root      1238  1006  0 09:02 ?        00:00:00 sshd: 12191765 [priv]
12191765  1247  1238  0 09:02 ?        00:00:00 sshd: 12191765@pts/101
12191765  1248  1247  0 09:02 pts/101  00:00:00 -bash
12191765  2184  1248  2 09:06 pts/101  00:00:00 ./ex3
12191765  2185  2184  2 09:06 pts/101  00:00:00 ./ex3
12191765  2186  2184  2 09:06 pts/101  00:00:00 ./ex3
12191765  2187   337  0 09:06 pts/94   00:00:00 ps -ef
12191765  2188   337  0 09:06 pts/94   00:00:00 grep --color=auto 12191765
$ kill -9 1248
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
12191765  2299   337  0 09:07 pts/94   00:00:00 ps -ef
12191765  2300   337  0 09:07 pts/94   00:00:00 grep --color=auto 12191765
```

6번과 마찬가지로 총 3개의 프로세스가 무한루프를 돌며 실행된다.

`kill -9 1248`으로 `SIGKILL`을 발생시켜 bash 프로세스를 죽이자 그 자식 프로세스인 "ex3"들이 따라서 죽었다.
터미널이 죽으면 `SIGHUP`를 발생시키는데 `SIGHUP`는 해당 프로세스 뿐만 아니라 그 자식 프로세스들에게도 전달되기 때문에 모든 "ex3" 프로세스가 죽었다.

`signal`로 `SIGHUP`에 대한 동작을 프로세스 종료 이외의 것으로 정의하면 프로세스가 죽지 않고 살아남을 수 있다.

### 8. Same as 6), but this time kill one of the children instead of the parent. What happens to the dead child? Can you remove this dead child (zombie) with signal 9? How can you remove this dead child?

```bash
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
root      2564  1006  0 09:11 ?        00:00:00 sshd: 12191765 [priv]
12191765  2574  2564  0 09:11 ?        00:00:00 sshd: 12191765@pts/105
12191765  2575  2574  0 09:11 pts/105  00:00:00 -bash
12191765  2718  2575  4 09:11 pts/105  00:00:00 ./ex3
12191765  2719  2718  8 09:11 pts/105  00:00:00 ./ex3
12191765  2720  2718  4 09:11 pts/105  00:00:00 ./ex3
12191765  2721   337  0 09:11 pts/94   00:00:00 ps -ef
12191765  2722   337  0 09:11 pts/94   00:00:00 grep --color=auto 12191765
$ kill 2719
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
root      2564  1006  0 09:11 ?        00:00:00 sshd: 12191765 [priv]
12191765  2574  2564  0 09:11 ?        00:00:00 sshd: 12191765@pts/105
12191765  2575  2574  0 09:11 pts/105  00:00:00 -bash
12191765  2718  2575  4 09:11 pts/105  00:00:00 ./ex3
12191765  2719  2718  7 09:11 pts/105  00:00:01 [ex3] <defunct>
12191765  2720  2718  4 09:11 pts/105  00:00:00 ./ex3
12191765  2723   337  0 09:11 pts/94   00:00:00 ps -ef
12191765  2724   337  0 09:11 pts/94   00:00:00 grep --color=auto 12191765
$ kill -9 2719
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
root      2564  1006  0 09:11 ?        00:00:00 sshd: 12191765 [priv]
12191765  2574  2564  0 09:11 ?        00:00:00 sshd: 12191765@pts/105
12191765  2575  2574  0 09:11 pts/105  00:00:00 -bash
12191765  2718  2575  3 09:11 pts/105  00:00:01 ./ex3
12191765  2719  2718  3 09:11 pts/105  00:00:01 [ex3] <defunct>
12191765  2720  2718  3 09:11 pts/105  00:00:01 ./ex3
12191765  2725   337  0 09:12 pts/94   00:00:00 ps -ef
12191765  2726   337  0 09:12 pts/94   00:00:00 grep --color=auto 12191765
$ kill 2718
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
root      2564  1006  0 09:11 ?        00:00:00 sshd: 12191765 [priv]
12191765  2574  2564  0 09:11 ?        00:00:00 sshd: 12191765@pts/105
12191765  2575  2574  0 09:11 pts/105  00:00:00 -bash
12191765  2720     1  4 09:11 pts/105  00:00:02 ./ex3
12191765  2728   337  0 09:12 pts/94   00:00:00 ps -ef
12191765  2729   337  0 09:12 pts/94   00:00:00 grep --color=auto 12191765
```

자식 프로세스가 종료되었지만 부모 프로세스가 자식 프로세스의 종료 상태를 회수하지 않았을 경우에 자식 프로세스를 좀비 프로세스라 한다.
`<defunct>`는 현재 프로세스가 좀비 상태임을 의미한다.

좀비 프로세스는 이미 죽은 상태이기 때문에 `SIGKILL`로도 사라지지 않고 남아있다.

`kill 2718`으로 부모 프로세스를 죽이면 좀비 프로세스가 사라진다.

### 9. In problem 8), how can you prevent the generation of a zombie child? Modify your code in 6) to prevent the generation of zombie child. Remember the parent cannot wait in `wait()` since the parent should run its infinite loop too. The parent should prepare a handler for `SIGCHLD` signal and call `wait()` inside this handler.

See [HW 9](./hw09/ex3.c)

```bash
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
root      2564  1006  0 09:11 ?        00:00:00 sshd: 12191765 [priv]
12191765  2574  2564  0 09:11 ?        00:00:00 sshd: 12191765@pts/105
12191765  2575  2574  0 09:11 pts/105  00:00:00 -bash
12191765  3823  2575  2 09:33 pts/105  00:00:00 ./ex3
12191765  3824  3823  2 09:33 pts/105  00:00:00 ./ex3
12191765  3825  3823  2 09:33 pts/105  00:00:00 ./ex3
12191765  3826   337  0 09:33 pts/94   00:00:00 ps -ef
12191765  3827   337  0 09:33 pts/94   00:00:00 grep --color=auto 12191765
$ kill 3824
$ ps -ef | grep 12191765
root       332  1006  0 08:57 ?        00:00:00 sshd: 12191765 [priv]
12191765   336   332  0 08:57 ?        00:00:00 sshd: 12191765@pts/94
12191765   337   336  0 08:57 pts/94   00:00:00 -bash
root      2564  1006  0 09:11 ?        00:00:00 sshd: 12191765 [priv]
12191765  2574  2564  0 09:11 ?        00:00:00 sshd: 12191765@pts/105
12191765  2575  2574  0 09:11 pts/105  00:00:00 -bash
12191765  3823  2575  2 09:33 pts/105  00:00:00 ./ex3
12191765  3825  3823  2 09:33 pts/105  00:00:00 ./ex3
12191765  3828   337  0 09:33 pts/94   00:00:00 ps -ef
12191765  3829   337  0 09:33 pts/94   00:00:00 grep --color=auto 12191765
```

`wait`는 프로세스의 상태가 바뀌는 것을 기다리는 함수이다.

자식 프로세스가 종료되면 부모 프로세스에 `SIGCHLD`를 전달한다.
`SIGCHLD`을 받으면 `wait` 함수를 호출해 부모 프로세스가 자식 프로세스의 종료 상태를 회수하도록 한다.

결과적으로 자식 프로세스만 죽이더라도 좀비 프로세스가 되지 않고 정상적으로 종료된다.
