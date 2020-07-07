#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char* y = (char*) malloc(sizeof(char) * 10);
    strcpy(y, "hello2");
    free(y);
    return 0;
}
