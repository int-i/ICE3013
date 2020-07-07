#include <stdio.h>
#include <unistd.h>

int main(void) {
    char* argv[] = {
        "/bin/cp",
        "f1",
        "f2",
        NULL
    };
    execve(argv[0], argv, NULL);
    return 0;
}
