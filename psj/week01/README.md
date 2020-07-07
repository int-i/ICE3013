# Linux Basic Command 1

## Do following steps.

### 1. Log in to a Linux server. Find your login directory with `pwd`. Find your user ID with `whoami`.

```bash
$ pwd
/home/sp22/12191765
$ whoami
12191765
```

### 2. Go up the file tree with `..`, display the current location with `pwd`, and find other students directory name with `ls`.

```bash
$ cd ..
$ pwd
/home/sp22
$ ls
12161911  12171989  12181738  12181745  12181756  12181839  12181857  12191765  12194182  12200019
12171868  12174823  12181741  12181751  12181778  12181841  12191759  12191827  12194291  12200144
```

### 3. Pick one of the student IDs (suppose it was 12345) and try to enter his/her directory with `cd`.

What happens?

```bash
$ cd 12345
-bash: cd: 12161911/: Permission denied
```

### 4. Use `ls -l` to see the file permission of the directory you tried to enter.

> ............
> drwx------ 2 12345 12345 4096 Feb 27 11:47 12345
> ............
>
> d: this file is a directory
> rwx: the owner can read/write/execute this file
> --- : the group member has no read/write/execute permission
> --- : other people has no read/write/execute permission
> 2   : there are two links to this file
> 12345 : the user ID of the owner of this file
> 12345 : the group ID of of the owner of this file
> 4096   : the byte size of this file
> Feb 27 11:47 : the creation time or last modification time of this file
> 12345 : file name

```bash
$ ls -l
total 80
drwx------. 3 12161911 12161911 4096 Mar 17 10:46 12161911
drwx------. 2 12171868 12171868 4096 Mar 11 15:20 12171868
drwx------. 3 12171989 12171989 4096 Mar 17 10:51 12171989
drwx------. 2 12174823 12174823 4096 Mar 11 15:20 12174823
drwx------. 2 12181738 12181738 4096 Mar 11 15:20 12181738
drwx------. 3 12181741 12181741 4096 Mar 17 10:49 12181741
drwx------. 2 12181745 12181745 4096 Mar 11 15:20 12181745
drwx------. 2 12181751 12181751 4096 Mar 11 15:20 12181751
drwx------. 4 12181756 12181756 4096 Mar 17 10:36 12181756
drwx------. 2 12181778 12181778 4096 Mar 17 02:27 12181778
drwx------. 2 12181839 12181839 4096 Mar 11 15:20 12181839
drwx------. 2 12181841 12181841 4096 Mar 11 15:20 12181841
drwx------. 2 12181857 12181857 4096 Mar 11 15:20 12181857
drwx------. 4 12191759 12191759 4096 Mar 17 10:51 12191759
drwx------. 2 12191765 12191765 4096 Mar 11 15:20 12191765
drwx------. 2 12191827 12191827 4096 Mar 11 15:20 12191827
drwx------. 2 12194182 12194182 4096 Mar 11 15:20 12194182
drwx------. 2 12194291 12194291 4096 Mar 11 15:20 12194291
drwx------. 2 12200019 12200019 4096 Mar 11 15:20 12200019
drwx------. 2 12200144 12200144 4096 Mar 11 15:20 12200144
```

Explain why you couldn't enter the directory you picked.

There is no permission to access the directory because I am not the directory owner and have no read/write/execute permission.

### 5. Find out your current location again with `pwd`.

```bash
$ pwd
/home/sp22
```

### 6. Go to the root directory with `cd /` and make sure you are really at the top directory with `pwd`.

```bash
$ cd /
$ pwd
/
```

### 7. How many files you have in the root directory? Some of them are not directory files. Find them with `ls -l`. Use `file` command to see more detailed info.

```bash
$ ls -l
total 62
lrwxrwxrwx.   1 root root     7 Feb 26  2013 bin -> usr/bin
dr-xr-xr-x.   4 root root  1024 Jun  4  2013 boot
drwxr-xr-x.  19 root root  3500 Dec 30 16:02 dev
drwxr-xr-x. 157 root root 12288 Mar 17 03:11 etc
drwxr-xr-x.  13 root root  4096 Mar 11 15:33 home
lrwxrwxrwx.   1 root root     7 Feb 26  2013 lib -> usr/lib
lrwxrwxrwx.   1 root root     9 Feb 26  2013 lib64 -> usr/lib64
drwx------.   2 root root 16384 Feb 26  2013 lost+found
drwxr-xr-x.   2 root root  4096 Jul 19  2012 media
drwxr-xr-x.   2 root root  4096 Jul 19  2012 mnt
drwxr-xr-x.   2 root root  4096 Jul 19  2012 opt
dr-xr-xr-x. 241 root root     0 Dec 30 16:02 proc
dr-xr-x---.  11 root root  4096 Aug 28  2016 root
drwxr-xr-x.  42 root root  1340 Mar 16 17:04 run
lrwxrwxrwx.   1 root root     8 Feb 26  2013 sbin -> usr/sbin
drwxr-xr-x.   2 root root  4096 Jul 19  2012 srv
dr-xr-xr-x.  13 root root     0 Dec 30 16:02 sys
drwxrwxrwt.   9 root root   220 Mar 17 10:51 tmp
drwxr-xr-x.  13 root root  4096 Feb 26  2013 usr
drwxr-xr-x.  21 root root  4096 Feb 26  2013 var
$ file *
bin:        symbolic link to `usr/bin'
boot:       directory
dev:        directory
etc:        directory
home:       directory
lib:        symbolic link to `usr/lib'
lib64:      symbolic link to `usr/lib64'
lost+found: directory
media:      directory
mnt:        directory
opt:        directory
proc:       directory
root:       directory
run:        directory
sbin:       symbolic link to `usr/sbin'
srv:        directory
sys:        directory
tmp:        sticky directory
usr:        directory
var:        directory
$ file lib
lib: symbolic link to `usr/lib'
```

### 8. `*` is a wild card character meaning it will be replaced by all file names in the current directory.

```bash
$ file *
```

is same as

```bash
$ file app bin boot dev .... (all file names in the current directory)
```

```bash
$ file b*
```

is same as

```bash
$ file bin boot
```

### 9. If you want to go back to your login directory (suppose it was `/home/sp1/12345`), you can cd with absolute path, cd with relative path, or just `cd`.

- cd /home/sp1/12345 - go to absolute path `/home/sp1/12345`
- cd home/sp1/12345 - go to "home" in the current directory and go to `sp1` and then to `12345`, that is go to relative directory `home/sp1/12345`
- cd - go to the login directory of the current user

Use one of above methods to go back to your login directory (or home directory).

### 10. Confirm your current location with `pwd`.

```bash
$pwd
/home/sp22/12191765
```

### 11. List all files in your directory with `ls` command.

### 12. Try `echo` command.

```bash
$ echo korea
korea
$ echo hello
hello
```

### 11. Try `echo` with `>` symbol. `>` is called "standard output redirection".

```bash
$ echo hello > f1
```

`>` sends the result to `f1` so there is no output shown in the terminal but you will have f1 in the current directory.

### 12. Do `ls` to see you can find f1 in the current directory. Show its content with `cat`.

```bash
$ ls
f1
$ cat f1
hello
```

### 13. Make a directory, d1, with `mkdir`.

```bash
$ mkdir d1
```

### 14. Copy `f1` into directory `d1`.

```bash
$ cp f1 d1   -- make a copy of f1 inside directory d1 under the same name.
$ cd d1
$ ls
$ cat f1 
hello
$ cd ..
$ cp f1 d1/f2  -- make a copy of f1 inside d1 under another name f2
$ cd d1
$ ls
f1  f2
```

## 2. Do followings and explain what happens and why.

```bash
$ cd
$ ls
d1  f1
$ ls –l
total 8
drwxrwxr-x. 2 12191765 12191765 4096 Mar 17 11:06 d1
-rw-rw-r--. 1 12191765 12191765    6 Mar 17 11:05 f1
$ ls –al
total 16
drwx------.  3 12191765 12191765 4096 Mar 17 11:05 .
drwxr-xr-x. 22 root     root     4096 Mar 11 15:20 ..
drwxrwxr-x.  2 12191765 12191765 4096 Mar 17 11:06 d1
-rw-rw-r--.  1 12191765 12191765    6 Mar 17 11:05 f1
$ cd /
$ cd bin
$ ls 
[                                    gvfs-rm                            pkcon
a2p                                  gvfs-save                          pkcs11_eventmgr
ab                                   gvfs-set-attribute                 pkcs11_inspect
abrt-action-analyze-backtrace        gvfs-trash                         pkcs11_listcerts
...
$ ls bz*
bzcat  bzcmp  bzdiff  bzgrep  bzip2  bzip2recover  bzless  bzmore  bzr
$ cd 
$ pwd
/home/sp22/12191765
$ man ls
$ echo hello
hello
$ echo hello > f4
$ ls
d1  f1  f4
$ cp f4 f2
$ cat f4 
hello
$ cat f2 
hello
$ cat f2 > f3
$ ls -l f*
-rw-rw-r--. 1 12191765 12191765 6 Mar 17 11:05 f1
-rw-rw-r--. 1 12191765 12191765 6 Mar 17 11:10 f2
-rw-rw-r--. 1 12191765 12191765 6 Mar 17 11:11 f3
-rw-rw-r--. 1 12191765 12191765 6 Mar 17 11:09 f4
$ rm f2
$ ls
d1  f1  f3  f4
$ cat f4 
hello
$ xxd f4
0000000: 6865 6c6c 6f0a                           hello.
$ mkdir d2
$ cp f4 d2
$ cd d2
$ pwd
/home/sp22/12191765/d2
$ ls
f4
$ cd ..
$ grep -nr "he" *
d1/f1:1:hello
d1/f2:1:hello
d2/f4:1:hello
f1:1:hello
f3:1:hello
f4:1:hello
$ ps
PID TTY          TIME CMD
28881 pts/18   00:00:00 bash
31734 pts/18   00:00:00 ps
$ ps –ef
UID        PID  PPID  C STIME TTY          TIME CMD
root         1     0  0  2019 ?        00:00:35 /usr/lib/systemd/systemd --switched-root --system --deserialize 23
root         2     0  0  2019 ?        00:00:01 [kthreadd]
root         3     2  0  2019 ?        00:00:10 [ksoftirqd/0]
root         5     2  0  2019 ?        00:00:00 [kworker/0:0H]
root         7     2  0  2019 ?        00:00:00 [kworker/u:0H]
root         8     2  0  2019 ?        00:00:01 [migration/0]
root         9     2  0  2019 ?        00:00:00 [rcu_bh]
root        10     2  0  2019 ?        00:14:35 [rcu_sched]
...
$ ps –ef | more
PID TTY      STAT   TIME COMMAND
28881 pts/18   Ss     0:00 -bashUSER=12191765 LOGNAME=12191765 HOME=/home/sp22/12191765 PATH=/usr/local/bin:/usr/bin MAI
L=/var/mail/12191765 SHELL=/bin/bash SSH_CLIENT=114.205.38.207 50716 22 SSH_CONNECTION=114.205.38.207 50716 165.246.38.1
52 22 SSH_TTY=/dev/pts/18 TERM=xterm-256color SELINUX_ROLE_REQUESTED= SELINUX_LEVEL_REQUESTED= SELINUX_USE_CURRENT_RANGE
= XDG_SESSION_ID=2067 XDG_RUNTIME_DIR=/run/user/1880
...
```

## 3. Find out the usage of following commands. Use them in a Linux server and explain what happens.

> chmod, clear, gzip, date, dd, df, diff, dmesg, du, env, exit, file, find, head, ifconfig, ln, mount, netstat, stat, tail, time, touch, tty, gunzip, whereis, which, whoami

- chmod - change file mode bits
- clear  clears  your screen if this is possible.
- gzip, gunzip, zcat - compress or expand filesdate Display the current time in the given FORMAT, or set the system date.
- dd - convert and copy a file
- df - report file system disk space usage
- diff - compare files line by line
- dmesg - print or control the kernel ring buffer
- du - estimate file space usage
- env - run a program in a modified environment
- file — determine file type
- find - search for files in a directory hierarchy
- head - output the first part of files
- ifconfig - configure a network interface
- ln - make links between files
- netstat  - Print network connections, routing tables, interface statistics, masquerade connections, and multicast memberships
- stat - display file or file system status
- tail - output the last part of files
- time - time a simple command or give resource usage
- touch - change file timestamps
- tty - print the file name of the terminal connected to standard input
- whereis - locate the binary, source, and manual page files for a command
- which - shows the full path of (shell) commands.
- whoami - print effective userid
