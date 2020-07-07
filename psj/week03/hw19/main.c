#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char* strarr[10] = { NULL };
    strarr[0] = "hello";
    strarr[1] = (char*) malloc(sizeof(char) * 100);
    strcpy(strarr[1], "bye");
    printf("%s %s\n", strarr[0], strarr[1]);
    return 0;
}
