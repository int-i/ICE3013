#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc == 2) {
        FILE* stream = fopen(argv[1], "r");
        if (stream == NULL) {
            perror("Fail to open");
            exit(EXIT_FAILURE);
        }
        int sum = 0;
        char buf;
        while (fread(&buf, sizeof(char), 1, stream) > 0) {
            sum += buf;
        }
        printf("sum: %x", sum);
        fclose(stream);
    } else {
        fprintf(stderr, "Invalid arguments\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
