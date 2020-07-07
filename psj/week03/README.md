# String

## Homework

### 1. [A char constant is an ascii number. A string constant is an address where it is stored in the string area] Explain the result for following code.

```c
#include <stdio.h>
#include <string.h> // you need this header file for string functions
void main() {
    char x, y;
    x = 'a';
    y = 97;
    printf("%d %c %d %c\n", x, x, y, y);
    char* x1 = "hello";
    printf("%s %p %s %p\n", x1, x1, "hello", "hello"); // use %p for address
}
```

```text
97 a 97 a
hello 0x40064d hello 0x40064d
```

첫 번째 `printf`는 `%d`는 문자의 아스키코드 값, `%c`는 문자 자체를 출력하라는 뜻으로 `'a'`와 `'a'`의 아스키 코드 97을 출력했다.
두 번째 `printf`는 `%s`는 문자열, `%p`는 주소를 출력하라는 뜻으로 `"hello"`와 이것이 저장된 주소가 출력되었는데 같은 곳에 저장된 값이기 때문에 동일한 주소를 출력했다.

### 2. [A char constant is an ascii number] Try following code and explain the result.

```c
#include <stdio.h>

void main() {
    char x[10]; // x is a character array with 10 rooms
    x[0] = 'a';
    x[1] = 'b';
    x[2] = 'c';
    x[3] = 'd';
    x[4] = 'e';
    x[5] = 'f';
    x[6] = 'g';
    x[7] = 'h';
    x[8] = 'i';
    x[9] = 'j';
    int i;
    for (i = 0; i < 10; i++) {
        printf("%d %c \n", x[i], x[i]); // print each character with its ascii number
    }
}
```

```bash
$ gcc hello.c -o hello
$ ./hello
97 a
98 b
99 c
100 d
101 e
102 f
103 g
104 h
105 i
106 j
```

문자 배열 `x`의 요소를 순회하는 반복문을 통해 `x`의 아스키코드와 `x` 자체를 출력했다.

### 3. Try below. Compare the result with that of Problem 2).

```c
#include <stdio.h>

void main() {
    char x[10]; // x is a character array with 10 rooms
    int i;
    for (i = 0; i < 10; i++) {
        x[i] = i + 97;
    }
    for (i = 0; i < 10; i++) {
        printf("%d %c \n", x[i], x[i]); // print each character with its ascii number
    }
}
```

```bash
$ gcc hello.c -o hello
$ ./hello
97 a
98 b
99 c
100 d
101 e
102 f
103 g
104 h
105 i
106 j
```

문제 2번과 동일한 결과가 나왔다. a의 아스키코드를 기준으로 1씩 증가하는 반복문으로 아스키코드 값을 증가시키며 출력한 결과 a부터 j까지의 알파벳이 출력되었다.

### 4. Declare a character array with 128 rooms. Store 0 to 127 in this array and print the corresponding character for each ascii code in the array. Find ASCII table in the Internet and confirm the results.

See [HW 4](./hw04/main.c)

```bash
$ gcc hello.c -o hello
-bash-4.2$ ./hello
0  0
1  1
2  2
3  3
4  4
5  5
6  6
7  7
8 8
9        9
10
 10
...
118 v 118
119 w 119
120 x 120
121 y 121
122 z 122
123 { 123
124 | 124
125 } 125
126 ~ 126
127 127
```

0부터 127까지 증가하는 반복문을 통해 아스키코드표와 동일한 결과를 얻을 수 있었다.

### 5. [`strlen`] Read a string and display its length.

See [HW 5](./hw05/main.c)

```bash
$ gcc hello.c -o hello
$ ./hello
Enter a string:
hello
The length is 5
```

### 6. [A string is a char array ending with 0] Read a string and display each character in different lines.

See [HW 6](./hw06/main.c)

```bash
$ gcc hello.c -o hello
$ ./hello
Enter a string:
hello
h
e
l
l
o
```

### 6-1. [A string is a char array ending with 0] Try below and explain the result. Use g++ to compile.

```c
#include <stdio.h>
#include <string.h>

void main() {
    char x[10];
    strcpy(x, "hello");
    strcpy(x, "hi");
    int i;
    for (i = 0; i < 10; i++) {
        printf("%d ", x[i]);
    }
}
```

```bash
$ g++ hello.cpp -o hello
$ ./hello
104 105 0 108 111 0 0 0 0 0
```

`x`에 `strcpy`로 문자열 값을 복사해 `'h', 'i', '\0', 'l', 'o', '\0'` 값이 들어갔다.
이를 반복문을 통해 아스키코드를 출력한 결과 `104 105 0 108 111 0`가 출력되었다.

### 7. [`strlen`, `strcmp`] Write a program that keeps reading a string, displaying its length, and checking whether it is `hello`. If the input string is `hello`, the program stops.

See [HW 7](./hw07/main.c)

```bash
$ gcc hello.c -o hello
$ ./hello
Enter a string:
hi
You enteredrm hello.chello. Bye.-bash-4.2$ gcc hello.c -o hello
-bash-4.2$ nano hello.c
-bash-4.2$ gcc hello.c -o hello
-bash-4.2$ ./hello
Enter a string:
hi
You entered hi. length=2
No it is not hello
Enter a string:
hello
You entered hello. length=5
Yes it is hello. Bye.
```

### 8. [`strcpy`] Read a string and copy it to three other string variables and change the first letter of them to `a`, `b`, and `c`, respectivley, and display them.

See [HW 8](./hw08/main.c)

```bash
$ gcc hello.c -o hello
$ ./hello
Enter a string:
hello
After copying and changing the first letter
aello
bello
cello
```

### 9. [string constant] A string constant such as `hello` is an address. Explain the result of following code.

See [HW 9](./hw09/main.c)

```bash
$ gcc hello.c -o hello
$ ./hello
hello hi bye
0x400640 0x400646 0x400649
```

`"hello"`의 길이는 `'\0'`을 포함해 6자이다. 따라서 `"hi"` 값의 주소는 `"hello"` 주소에 6만큼 더한 곳부터 시작한다.
마찬가지로 `"hi"`의 길이는 `'\0'`을 포함해 3자이므로 `"bye"`는 `"hi"`의 주소에 3만큼 더한 곳부터 시작한다.

### 10. [string constant is an address] Try below and explain why we have an error.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char *x, *y, *z;
    x = "hello";
    y = "hi";
    z = "bye";
    printf("%s %s %s\n", x, y, z);
    printf("%p %p %p\n", x, y, z);
    return 0;
}
```

`x`는 배열이기 때문에 문자열을 직접 대입할 수 없다.
따라서 `strcpy`를 이용해 문자열 내용을 배열에 복사해야한다.

### 11. [You need memory space for `strcpy`] Try below and explain why we have an error. How can you fix it?

```c
#include <stdio.h>
#include <string.h>

int main() {
    char* y;
    y = "hello1"; // this is ok
    strcpy(y, "hello2"); // error because y has no space for "hello2"
    return 0;
}
```

See [HW 11](./hw11/main.c)

`y`에 문자열 리터럴을 대입하면 읽기 메모리에 할당되기 때문에 수정할 수 없다.
따러서 동적할당을 통해 공간을 확보해야 다른 문자열을 저장할 수 있다.

### 12. [You need memory space for `scanf`] Try below and explain why you have an error. Fix it.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char* y;
    printf("enter a string\n");
    scanf("%s", y); // error becuase y has no space for a string
    printf("you entered %s\n", y);
    return 0;
}
```

See [HW 12](./hw12/main.c)

`char*`는 단순히 `y`가 할당 받은 공간을 가리키는 포인터에 불과하다.
`y`의 크기를 명시해 `y`가 운영체제로부터 공간을 할당받아 문자열을 저장할 공간이 있어야 한다.

### 13. [char pointer array] Define a character pointer array and store/display strings as below.

See [HW 13](./hw13/main.c)

```bash
$ gcc hello.c -o hello
$ ./hello
hi bye hello
```

### 14. [char pointer array, `strcmp`, `new`] Write a program that keeps reading strings and store them in a character pointer array. It stops when the user enters `end` and displays all strings entered so far. Use `new` to allocate memory and use g++ to compile.

See [HW 14](./hw14/main.c)

```text
Enter a string
hi
Enter a string
aaa
Enter a string
bbb
Enter a string
end
Strings entered so far are
hi aaa bbb
```

### 15. [`gets`, `fgets`] Read the same sentence with `gets()` and `fgets()` and explain the difference. (Ignore warning for `gets`. It is a security warning because gets can cause security problem.)

See [HW 15](./hw15/main.c)

```bash
$ gcc hello.c -o hello
hello.c: In function ‘main’:
hello.c:7:5: warning: ‘gets’ is deprecated (declared at /usr/include/stdio.h:640) [-Wdeprecated-declarations]
$ ./hello
enter a sentence
aaaa bbb cc d
sentence length after gets:13
61 61 61 61 20 62 62 62 20 63 63 20 64
enter the same sentence
aaaa bbb cc d
sentence length after fgets:14
61 61 61 61 20 62 62 62 20 63 63 20 64 a 
```

`gets`는 100자 제한이 있지만, `fgets`는 최대입력글자를 입력받아 설정할 수 있다.

### 16. [`strtok`] Use `strtok` to extract words from a sentence and store them in an array. Display the number of words as below. Note that you need to copy the sentence to another string variable before doing `strtok` because `strtok` will destroy the original sentence.

See [HW 16](./hw16/main.c)

```text
Enter a sentence
aa bcd e e ff aa bcd bcd hijk lmn al bcd
You entered aa bcd e e ff aa bcd bcd hijk lmn al bcd

There were 12 words
aa
bcd
e
e
ff
aa
bcd
bcd
hijk
lmn
al
bcd

The original sentence was: aa bcd e e ff aa bcd bcd hijk lmn al bcd
```

### 17. [char pointer array, `new`, `strcmp`] Write a program that keeps reading a name and stores it in a character pointer array until the user enters bye. The program should display all names after it sees `bye`.

See [HW 17](./hw17/main.c)

```text
Enter a name
kim han kook
Enter a name
park dong il
Enter a name
hong gil dong
Enter a name
bye
There were 3 names.
kim han kook
park dong il
hong gil dong
```

### 18. [There is a hidden 0 at the end of a string] Try below and explain why it behaves strange. How can you fix it?

```c
#include <stdio.h>
#include <string.h>

int main() {
    int x1;
    char x2[12];
    x1 = 33;
    strcpy(x2, "abcdefghijkl");
    printf("%d %s", x1, x2);
    return 0;
}
```

```bash
$ gcc hello.c -o hello
$ ./hello
0 abcdefghijkl
```

`strcpy`로 `x2`에 복사되는 문자열의 크기는 `"\0"`을 포함해서 13자이다.
따라서 `x1`의 크기를 13으로 지정해야 오작동하지 않는다.
`x1`이 0으로 수정된 이유는 스택 오버플로우로 인한 오작동으로 추정된다.

수업시간에 제공하는 리눅스 서버의 gcc(v4.7.2)에서는 `-fstack-protector-all`으로 스택 프로텍터를 활성화했을 때 오류가 발생하지 않고 `33 abcdefghijkl`이 출력된다.
최신버전의 gcc에서는 아래와 같은 오류가 출력된다.

```text
check.c: In function ‘main’:
check.c:8:5: warning: ‘__builtin_memcpy’ writing 13 bytes into a region of size 12 overflows the destination [-Wstringop-overflow=]
     strcpy(x2, "abcdefghijkl");
     ^~~~~~~~~~~~~~~~~~~~~~~~~~
```

### 19. [You need memeory space for `strcpy`] What is wrong with the following program? How can you fix it?

```c
#include <stdio.h>
#include <string.h>

int main() {
    char* strarr[10] = { NULL };
    strarr[0] = "hello";
    strcpy(strarr[1], "bye");
    printf("%s %s\n", strarr[0], strarr[1]);
    return 0;
}
```

See [HW 19](./hw19/main.c)

`strarr[1]`을 동적할당해야 한다.

### 20. [char pointer array, `new`, `strcmp`] Write a program that reads a long sentence and displays the frequency of each word as below. It also prints the word that has the maximum frequency.

See [HW 20](./hw20/main.c)

```text
Enter a sentence
aa bcd e e ff aa bcd bcd hijk lmn al bcd
You entered aa bcd e e ff aa bcd bcd hijk lmn al bcd
There were 12 words: aa bcd e e ff aa bcd bcd hijk lmn al bcd
Frequencies: aa 2 bcd 4 e 2 ff 1 hijk 1 lmn 1 al 1
The word with the max freq: bcd
```
