#include <stdio.h>
#include <unistd.h>

int main(void) {
    char* argv[] = {
        "/bin/cat",
        "f1",
        NULL,
    };
    execve(argv[0], argv, NULL);
    return 0;
}
