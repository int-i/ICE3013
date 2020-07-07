// 폴더 열기에 필요한 헤더
#include <dirent.h>
// 파일 헤더
#include <fcntl.h>
// 입출력 헤더
#include <stdio.h>
// 시스템 헤더
#include <stdlib.h>
// 문자열 헤더
#include <string.h>
// stat 구조체 헤더
#include <sys/stat.h>
// 파일 헤더
#include <unistd.h>

// 프로그램 인자를 받는 main 함수
int main(int argc, char* argv[]) {
    // argc는 인자 갯수
    // argv는 인자 내용
    if (argc == 3) { // 인자 갯수가 2개일 때만 작동, 프로그램 명 포함되니 argc는 3임
        DIR* dirp = opendir("./"); // 폴더 열기 ./는 현재폴더를 의미함.
        // dirp는 폴더 구조체, 현재 폴더에 대한 정보를 담고 있음
        if (dirp == NULL) { // 만약 폴더 열기에 실패하면
            perror("Fail to open directory"); // 오류 메세지를 출력하고
            exit(EXIT_FAILURE); // 실패 반환 코드로 프로그램 종료 
        }
        struct dirent* dp; // 폴더 구조체의 내부 포맷 정의
        // dirent는 폴더의 파일 순회에 사용되는 구조체임
        while ((dp = readdir(dirp)) != NULL) { // 더 이상 읽을 폴더 내용이 없을 때까지 반복
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) { // 만약 폴더 경로가 . 이나 .. 이 아니라면
                int fd = open(dp->d_name, O_RDWR, 00777); // 읽기쓰기 모드로 파일 열기
                // fd는 파일 디스크립터
                if (fd == -1) { // 파일 읽기가 실패하면
                    // 스킵
                    // 폴더 같은 애들은 여기서 걸러짐
                    continue;
                }
                struct stat s; // 파일 구조체 선언
                // s는 파일 구조체로 파일에 대한 정보를 담을 예정
                fstat(fd, &s); // fd의 정보를 s에 담음
                char* buf = malloc(sizeof(char) * s.st_size); // 파일 크기만큼 메모리를 동적할당 함
                // buf는 읽은 파일을 내용을 담을 배열임 
                read(fd, buf, s.st_size); // 파일 내용을 모두 읽어서 buf에 저장
                for (int i = 0; i < s.st_size; i += 1) { // 파일 처음부터 끝까지 buf 배열을 순회하며
                    // i는 현재 검사중인 buf 위치
                    if (buf[i] == argv[1][0]) { // buf[i] 문자가 첫번쨰 인자면(문자기 때문에 [0]으로 가져옴)
                        buf[i] = argv[2][0]; // buf[i]를 두번쨰 인자로 치환한다. (문자기 때문에 [0]으로 가져옴)
                    }
                }
                lseek(fd, 0, SEEK_SET); // 파일 맨 앞으로 돌아와서
                write(fd, buf, s.st_size); // buf를 파일에 덮어쓰운다.
                free(buf); // 동적할당한 메모리를 해지한다.
                close(fd); // 사용한 파일 디스크립터를 해지한다.
            }
        }
        closedir(dirp); // 사용한 폴더 포인터를 해지한다.
    } else {
        fprintf(stderr, "Invalid arguments\n"); // 표준오류출력으로 메세지를 출력한다,
        exit(EXIT_FAILURE); // 실패 반환 코드로 프로그램 종료 
    }
    return 0; // 0으로 종료
}
