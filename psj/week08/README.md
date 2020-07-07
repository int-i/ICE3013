# Midterm Exam

## Practice

### 1. Write a program that reads a file and change all space characters to 'a'.

For example if "f1" is:

```text
 h  ll o
```

```bash
$ ./sol01 f1
$ cat f1
ahaallao
```

See [Sol. 1](./sol01/main.c)

### 2. Modify your code in Problem 1 such that it can change a given character to another given character in a file.

For example if "f1" is:

```text
h ll o hi
```

The following will change 'h' to 'b' in f1 file.

```bash
$ ./sol02 f1 h b
$ cat f1
b ll o bi
```

See [Sol. 2](./sol02/main.c)

### 3. Modify your code in Problem 2 such that it can repeat the same process (chainging a given character to another given character) for all files in the current directory.

For example,

```bash
$ ./sol03 h b
```

will change 'h' to 'b' for all files(excluding directory file) in the current directory.

See [Sol. 3](./sol03/main.c)

### (Before revised) 3. Modify your code in Problem 2 such that it can delete the indicated character in all files in the current directory.

See [Sol. 3 Previous](./sol03_prev/main.c)
