# File 2

## Homework

### 1. Read "swvader03.wav" with `xxd`. Interpret all fields in the header.

First copy "swvader03.wav" file from "../../linuxer1" directory into current directory.
`.` means current directory.

```bash
$ cp ../../linuxer2/swvader03.wav .
```

Look at the file with `xxd`.

```bash
$ xxd swvader03.wav > x
$ vi x
```

```text
0000000: 5249 4646 3476 0000 5741 5645 666d 7420  RIFF4v..WAVEfmt
0000010: 1000 0000 0100 0100 2256 0000 2256 0000  ........"V.."V..
0000020: 0100 0800 6461 7461 1076 0000 8080 8080  ....data.v......
0000030: 8080 8080 8080 8080 8080 7f80 8080 7f80  ................
0000040: 7f7f 7f7f 807f 7f7f 7f7f 8080 8080 8080  ................
0000050: 8080 8080 8080 8080 8080 8080 8080 8080  ................
0000060: 8080 8080 8080 8080 8080 8080 8080 8080  ................
0000070: 8080 8080 8080 7f7f 7f7f 7f7f 7f7f 7f7f  ................
0000080: 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f  ................
0000090: 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f  ................
00000a0: 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f  ................
00000b0: 7f7f 7f7f 7f7f 7f7f 7f7f 7f80 8080 8080  ................
00000c0: 8080 8080 8080 8080 8080 8080 8080 8080  ................
00000d0: 8080 8080 8080 8080 8080 8080 8080 8080  ................
00000e0: 8080 8080 8080 8080 8080 8080 8080 8080  ................
00000f0: 8080 8080 807f 7f7f 7f7f 7f7f 7f7f 7f7f  ................
0000100: 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f  ................
0000110: 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f80 8080  ................
0000120: 8080 8080 8080 8080 8080 7f7f 7f7f 7f7f  ................
0000130: 8080 8080 8080 8080 807f 7f7f 7f7f 7f7f  ................
0000140: 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f 7f7f  ................
0000150: 7f7f 7f80 807f 7f7f 7f7f 7f7f 7f7f 7f80  ................
0000160: 8080 8080 8080 8080 8080 8080 8080 8080  ................
0000170: 8080 8080 8080 8080 8080 8080 8080 8080  ................
0000180: 8080 8181 8181 8181 8181 8181 8181 8181  ................
0000190: 8181 8181 8181 8181 8180 8080 8080 807f  ................
00001a0: 7f7f 7f7f 7f7f 7f7f 7e7e 7e7e 7e7e 7e7e  ........~~~~~~~~
00001b0: 7d7e 7e7e 7e7e 7d7d 7d7d 7d7e 7e7e 7e7e  }~~~~~}}}}}~~~~~
00001c0: 7e7e 7d7e 7e7f 7e7e 7e7e 7e7e 7e7f 7f7f  ~~}~~.~~~~~~~...
...
```

The answer should show the byte sequence and the value of each field as follows:

- Chunk ID: RIFF (0x52 0x49 0x46 0x46)
- Chunk Size: 30260 (0x00007634)
- Format: WAVE (0x57 0x41 0x56 0x45)
- Subchunk1 ID: fmt (0x66 0x6d 0x74 0x20)
- Subchunk1 Size: 16 (0x00000010)
- Audio Format: 1 (0x0001)
- Num Channels: 1 (0x0001)
- Sample Rate: 22050 (0x00005622)
- Byte Rate: 22050 (0x00005622)
- Block Align: 1 (0x0001)
- Bits per Sample: 8 (0x0008)
- Subchunk2 ID: data (0x64 0x61 0x74 0x61)
- Subchunk2 Size: 30224 (0x00007610)

숫자는 Little-endian, 문자열은 Big-endian임을 유의해서 해석해야 한다.

### 2. Write a program that reads "swvader03.wav" and displays the content as above.

See [HW 2](./hw02/main.c)

```text
Chunk ID: RIFF
Chunk Size: 30260
Format: WAVE
Subchunk1 ID: fmt
Subchunk1 Size: 16
Audio Format: 1
Num Channels: 1
Sample Rate: 22050
Byte Rate: 22050
Block Align: 1
Bits per Sample: 8
Subchunk2 ID: data
Subchunk2 Size: 30224
```

파일 포맷을 크기에 맞게 변수로 정의하고 차례대로 `read` 함수로 읽었다.
문자열은 맨 뒤에 "\0"을 붙여 `printf` 함수에서 올바르게 문자열을 인식해 출력될 수 있게 했다.

### 3. Same as 2), but display the content in file "sw2-wav.txt". Using `write()` to write into a text file is very hard. Use `fopen()` and `fprintf()` for formatted output.

See [HW 3](./hw03/main.c)

```bash
$ ./hw3
$ cat sw2-wav.txt
Chunk ID: RIFF
Chunk Size: 30260
Format: WAVE
Subchunk1 ID: fmt
Subchunk1 Size: 16
Audio Format: 1
Num Channels: 1
Sample Rate: 22050
Byte Rate: 22050
Block Align: 1
Bits per Sample: 8
Subchunk2 ID: data
Subchunk2 Size: 30224
```

2번 코드를 재사용해서 코드를 작성했다.
다만 `fopen`을 이용해 파일 스트림을 생성하고 `printf`를 `fprintf`로 바꿔 파일에 기록하게 했다.
사용한 파일 스트림은 `fclose`로 닫아주었다.

### 4. "swvader03.wav" contains a sentence, "Yes, my master". Write a program that modifies the file such that it contains only "master". Move the file read pointer to the start of the actual sound data with `lseek()` and write 0 for half of the sound data, since "Yes, my" and "master" take about half of the sound data each. It will be better that you copy "swvader03.wav" to "sw2.wav" and modify "sw2.wav". When you modified the file, you need to download it to your PC using "psftp".

```bash
$ cp swvader03.wav sw2.wav
```

See [HW 4](./hw04/main.c)

"swvader03.wav"의 사본을 만들고 파일을 수정했다.
"swvader03.wav"을 다운로드해 들어보니 음성의 앞 부분부터 중간부분을 지우면 "Yes, my"가 지워질 것 같았다.
우선, 데이터의 전체 크기를 구하기 위해 `lseek`로 40번째 바이트로 이동했다.
그리고 `memset`을 이용해 모든 비트가 0인 제로 버퍼를 만들어 데이터 청크의 절반을 덮어씌웠다.
결과적으로 음성파일의 앞부분은 소리가 안 나오고 뒤는 "master"로 정상적으로 재생되었다.

### 5. Write a program that modifies the wav file such that it contains "master" twice. That is, when you play this file you should here "master master".

```bash
$ cp swvader03.wav sw2.wav
```

See [HW 5](./hw05/main.c)

4번에서처럼 "swvader03.wav"의 사본을 만들고 파일을 수정했다.
4번과 다른점은 "Yes, my"를 0으로 채우는 것이 아닌 "master"로 대체하는 것이다.
마찬가지로 우선 데이터의 전체 크기를 구하기 위해 `lseek`로 40번째 바이트로 이동했다.
그리고 데이터 청크의 중간 부분부터 끝까지를 `read`로 읽어 `buf`에 저장하고 이를 데이터 청크가 시작되는 44바이트로 이동해 `wirte`를 이용해 데이터 청크 앞부분을 덮어씌웠다.
수정된 음성파일을 들어보니 "master master"가 나오게 되었다.
