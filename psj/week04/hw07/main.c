#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int main(void) {
    int x1 = open("hw4.c", O_RDONLY);
    int x2 = open("cphw4.c", O_RDWR | O_CREAT | O_TRUNC,  00777);
    char buf[BUFFER_SIZE];
    int y;
    for (;;) {
        y = read(x1, buf, BUFFER_SIZE);
        if (y == 0) {
            break;
        }
        write(x2, buf, y);
    }
    return 0;
}
