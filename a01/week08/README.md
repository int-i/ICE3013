# Midterm Exam

## Practice

### 1. Write a program that adds up the ascii number of a text file and print it.

If "f1" has

```text
ab
c
```

then, the output should be `61+62+a+63+a=13a` in hexadecimal number as follows.

```bash
$ ./sol01 f1
sum: 13a
```

See [Sol. 1](./sol01/main.c)

### 2. Write a program thar modifies any given wave file such that it repeats the first half of the sound.

```bash
$ ./sol02 swvader.wav
```

The above should modifies "swvader.wav" such that it contains "yes my yes my" sound instead of "yes my master".

See [Sol. 2](./sol02/main.c)

### 3. Write a program that creates a child. The parent and child both print their PID's, but make sure the child always runs first.

```bash
$ ./sol03
child: 19019
parent: 19018
```

See [Sol. 3](./sol03/main.c)
