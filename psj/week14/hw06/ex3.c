#include <unistd.h>

int main(void) {
    if (fork() == 0) {
        for (;;);
    } else {
        if (fork() == 0) {
            for (;;);
        }
    }
    for (;;);
    return 0;
}
