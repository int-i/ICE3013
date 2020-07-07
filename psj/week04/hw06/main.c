#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int f = open("f3", O_RDWR | O_CREAT | O_TRUNC, 00777); // create f3
    write(f, "hello there", 11); // write 11 bytes in f3
    return 0;
}
