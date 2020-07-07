# Linux Basic Command 2

## Lecture 3 Homework

### 1. Make a file with `vi`.

```bash
vi f1
```

### 2. Start insertion with `i` key and type following.

```text
Hello, this is my first session in the vi editor.
This is the second line of text.
```

### 3. Return to command mode with `esc`. Save and exit with `:wq`.

```text
esc
:wq
```

### 4. Reopen the file.

```bash
vi f1
```

### 5. Use `j`, `k`, `h`, `l` to move the cursor around. Move the cursor to the word "first". Use `x` key to delete the word "first". The result should be as follows.

```text
Hello, this is my session in the vi editor.
This is the second line of text.
```

### 6. Insert "third" as follows.

```text
Hello, this is my third session in the vi editor.
This is the second line of text.
```

### 7. Add a new line as follows. Use `o` key.

```text
Hello, this is my third session in the vi editor. 
Insert a new line here.
This is the second line of text.
```

### 8. Change the beginning as follows. Use `x` and `i` key.

```text
Hi there, this is my third session in the vi editor.
Insert a new line here.
This is the second line of text.
```

### 9. Add more at the end. Use `a` key.

```text
Hi there, this is my third session in the vi editor. Adding more at the end.
Insert a new line here.
This is the second line of text.
```

### 10. Delete the last line. Use `dd`.

```text
Hi there, this is my third session in the vi editor. Adding more at the end.
Insert a new line here.
```

### 11. Add few more lines. Use `o`.

```text
Hi there, this is my third session in the vi editor. Adding more at the end.
Insert a new line here.
One more line.
Another line.
And yet another line.
```

### 12. Change the last line.

```text
Hi there, this is my third session in the vi editor. Adding more at the end.
Insert a new line here.
One more line.
Another line.
And yet another but last line. And this is the end.
```

### 13. Copy and paste as follows. Use `2yy` to copy two lines at the current cursor; move the cursor to another location and use `p` to paste them at that location.

```text
Hi there, this is my third session in the vi editor. Adding more at the end.
One more line.
Another line.
Insert a new line here.
One more line.
Another line.
And yet another but last line. And this is the end.
```

### 14. Go to line 6 with `:6` and make change as follows.

```text
Hi there, this is my third session in the vi editor. Adding more at the end.
One more line.
Another line.
Insert a new line here.
One more line.
The 6th line.
And yet another but last line. And this is the end.
```

### 15. Write a simple c program and compile and run.

Write a program:

```bash
$ vi ex1.c
```

```c
#include <stdio.h>
void main(){
   printf("hi there\n");
}
```

Compile:

```bash
$ gcc –o ex1 ex1.c
```

Run:

```bash
$ ./ex1
hi there
```

## Lecture 4 Homework

### 1. Login to the system. Show the current directory. Show what files are in your directory. 

```bash
$ ls
d1  d2  ex1  ex1.c  f1  f3  f4
```

### 2. Go to "/etc" directory. "file *" will show the information for all files in the current directory. Combine "file *" and "grep" using the pipe symbol(|) to display file information only for text files.

```bash
$ cd /etc
$ file * | grep text
adjtime:                 ASCII text
aliases:                 ASCII text
anacrontab:              ASCII text
ant.conf:                ASCII text
anthy-conf:              ASCII text
asound.conf:             ASCII text
atmsigd.conf:            ASCII text
bashrc:                  ASCII text
brltty.conf:             assembler source, UTF-8 Unicode text
```

### 3. Find the location of the password file ("passwd"), the location of C header files such as "stdio.h", and the location of utility programs (or Linux commands) such as "ls". Use "whereis" commad.

```bash
$ whereis passwd
passwd: /bin/passwd /usr/bin/passwd /etc/passwd /usr/share/man/man5/passwd.5.gz /usr/share/man/man1/passwd.1.gz
$ whereis stdio.h
stdio: /usr/include/stdio.h /usr/share/man/man3/stdio.3.gz
```

### 4. Go to your login directory ("cd" without arguments will move you to your login directory). Make ex1.c using vi. Compile with "gcc" and run.

```bash
$ vi ex1.c
```

```c
#include <stdio.h>
void main(){
   printf("hello\n");
}
```

```bash
$ gcc -o ex1 ex1.c
$ ./ex1
hello
```

To compile with g++, change void main() => int main()

```cpp
#include <stdio.h>
int main(){
   printf("hello\n);
}
```

```bash
$ g++ -o ex1 ex1.c
$ ./ex1
hello
```

### 5. Display the contents of ex1.c using cat and xxd. With xxd, you can see the ascii code for each character in ex1.c. Find the ascii codes for the first line of the program: "#include <stdio.h>".

```bash
$ cat ex1.c
```

```c
#include <stdio.h>

int main() {
    printf("hello\n");
}
```

```bash
$ xxd ex1.c
0000000: 2369 6e63 6c75 6465 203c 7374 6469 6f2e  #include <stdio.
0000010: 683e 0a0a 696e 7420 6d61 696e 2829 207b  h>..int main() {
0000020: 0a20 2020 2070 7269 6e74 6628 2268 656c  .    printf("hel
0000030: 6c6f 5c6e 2229 3b0a 7d0a                 lo\n");.}.
```

### 6. Display the contents of ex1 (the executable file). You cannot use "cat" to see ex1. Why? 

기계어 파일이기 때문에 사람이 읽을 수 없다.

#### 6-1) The compiler has translated the C statements in ex1.c into machine instructions and stored in ex1:

> 55               -- push rbp
> 48 89 e5         -- mov rbp, rsp
> bf f0 05 40 00    -– mov edi, 0x400df0
> .........

Find these machine instructions in ex1 with xxd. Use "/pattern" command in vi to search for a string.

```bash
$ xxd ex1 > x
$ vi x

$ xxd ex1 | grep 5548
0000520: e97b ffff ffe9 76ff ffff 6690 5548 89e5  .{....v...f.UH..
$ xxd ex1 | grep bff0
0000530: bff0 0540 00e8 d6fe ffff 5dc3 0f1f 4000  ...@......]...@.
```

### 7. Copy ex1.c to ex2.c, ex3.c, and ex4.c. Remove ex2.c. Rename ex3.c to y.c.

```bash
$ cp ex1.c ex2.c
$ cp ex1.c ex3.c
$ cp ex1.c y.c
```

### 8. Make a subdirectory. Copy y.c in this subdirectory.

```bash
$ mkdir sub
$ cp y.c sub/y.c
```

### 9. Redirect the output of ex1 to another file using ">" symbol.

```bash
$ ./ex1 > f1
```

### 10. Use grep to search "hello" in all files (use -nr option).

```bash
$ file * | grep -nr hello
sub/y.c:4:    printf("hello\n");
ex1.c:4:    printf("hello\n");
f4:1:hello
ex4.c:4:    printf("hello\n");
f1:1:hello
Binary file ex1 matches
f3:1:hello
ex3.c:4:    printf("hello\n");
ex2.c:4:    printf("hello\n");
d2/f4:1:hello
y.c:4:    printf("hello\n");
ex3.3:4:    printf("hello\n");
x:96:00005f0: 6865 6c6c 6f00 0000 011b 033b 3400 0000  hello......;4...
d1/f1:1:hello
d1/f2:1:hello
```

### 11. Find out what processes exist in your system. Use "ps -ef".

```bash
$ ps -ef
UID        PID  PPID  C STIME TTY          TIME CMD
root         1     0  0  2019 ?        00:00:42 /usr/lib/systemd/systemd --switc
root         2     0  0  2019 ?        00:00:02 [kthreadd]
root         3     2  0  2019 ?        00:00:11 [ksoftirqd/0]
root         5     2  0  2019 ?        00:00:00 [kworker/0:0H]
root         7     2  0  2019 ?        00:00:00 [kworker/u:0H]
root         8     2  0  2019 ?        00:00:01 [migration/0]
root         9     2  0  2019 ?        00:00:00 [rcu_bh]
…
```

### 12. "ps -ef" shows all the processes in the system. How do you know which ones are yours? Use "tty" for this purpose. Note that when a user logs in, the system allocates a terminal, and you can find the terminal number with "tty" command.

```bash
$ tty
/dev/pts/20
$ ps -ef | grep tty/20
12191765 19434 16299  0 11:48 pts/20   00:00:00 grep --color=auto tty/20
```

### 13. Modify ex1.c so that it receives two numbers from the user and prints the sum. Use scanf() for this.

```c
#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d + %d = %d\n", a, b, a + b);
}
```

```bash
$ gcc -o ex1 ex1.c
$ ./ex1
1
20
1 + 20 = 21
```

### 14. Modify ex1.c so that it contains an infinite loop after printing "hello".

```c
#include <stdio.h>

int main() {
    printf("hello");
    fflush(stdout);  // to make it print hello immediately
    for(;;);
}
```

```bash
$ gcc -o ex1 ex1.c
$ ./ex1
hello
```

### 15. Run the program with & at the end, and use ps to check its status.

```bash
$ ./ex1 &
$ ps
$ ./ex1 & ps
[4] 19521
hello  PID TTY          TIME CMD
16299 pts/20   00:00:00 bash
17317 pts/20   00:00:00 vim
17477 pts/20   00:00:00 vim
17729 pts/20   00:00:00 vim
19521 pts/20   00:00:00 ex1
19522 pts/20   00:00:00 ps
```

### 16. Kill it with "kill" command.

```bash
$ ps
  PID TTY          TIME CMD
16299 pts/20   00:00:00 bash
17317 pts/20   00:00:00 vim
17477 pts/20   00:00:00 vim
17729 pts/20   00:00:00 vim
19521 pts/20   00:00:58 ex1
19530 pts/20   00:00:00 ps
-bash-4.2$ kill 19521
```

### 17. Run the program again without & at the end. Open another login window, find out the process ID of the process running in the first window, and kill it.

```bash
$ ./ex1
$ ps
$ ps
  PID TTY          TIME CMD
16299 pts/20   00:00:00 bash
17317 pts/20   00:00:00 vim
17477 pts/20   00:00:00 vim
17729 pts/20   00:00:00 vim
19766 pts/20   00:00:06 ex1
19768 pts/20   00:00:00 ps
$ kill 19766
```

### 18. Use "objdump -D -M intel ex1" to dump the assembly code of ex1.c. Find <main>.

```bash
$ objdump -D -M intel ex1 | grep main
00000000004004a0 <__libc_start_main@plt>:
  4004f4:       e8 a7 ff ff ff          call   4004a0 <__libc_start_main@plt>
00000000004005bc <main>:
4005e2:       eb fe                   jmp    4005e2 <main+0x26>
```

### 19. Run following and tell the difference between gets and fgets

```c
#include <stdio.h>
#include <string.h>
int main(){
   char buf[20];
   printf("enter a sentence\n");
   gets(buf);
   printf("I got %s from you. length:%d\n", buf, strlen(buf));
   printf("enter the same sentence again\n");
   fgets(buf, 20, stdin);
   printf("I got %s from you. length:%d\n", buf, strlen(buf));
}
```

```bash
$ vi diff.c
$ gcc -o diff diff.c
diff.c: In function ‘main’:
diff.c:6:4: warning: ‘gets’ is deprecated (declared at /usr/include/stdio.h:640) [-Wdeprecated-declarations]
$ ./diff
```

gets는 100자 제한이 있지만, fgets는 최대입력글자를 입력받아 설정할 수 있다.

### 20. Write a program to read a sentence and echo it as follows. Use gets() or fgets(). Do "man gets" or "man fgets" to find out the usage of them.

```bash
$ man gets
       gets() reads a line from stdin into the buffer pointed to  by  s  until
       either a terminating newline or EOF, which it replaces with a null byte
       ('\0').  No check for buffer overrun is performed (see BUGS below).
$ man fgets
       fgets() reads in at most one less than size characters from stream  and
       stores  them  into  the buffer pointed to by s.  Reading stops after an
       EOF or a newline.  If a newline is read, it is stored into the  buffer.
       A  terminating  null  byte ('\0') is stored after the last character in
       the buffer.
```

Enter a sentence
aa bcd e e ff aa bcd bcd hijk lmn al bcd
You entered aa bcd e e ff aa bcd bcd hijk lmn al bcd

```bash
$ ./diff
enter a sentence
aa bcd e e ff aa bcd bcd hijk lmn al bcd
I got aa bcd e e ff aa bcd bcd hijk lmn al bcd from you. length:40
enter the same sentence again
aa bcd e e ff aa bcd bcd hijk lmn al bcd
I got aa bcd e e ff aa bc from you. length:19
Segmentation fault (core dumped)
```
