#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char* strs[100];
    int i = 0;
    while (1) {
        printf("Enter a string\n");
        strs[i] = (char*) malloc(sizeof(char) * 100);
        scanf("%s", strs[i]);
        if (strcmp(strs[i], "end") == 0) {
            printf("Strings entered so far are\n");
            break;
        }
        i += 1;
    }
    int j;
    for (j = 0; j < i; j += 1) {
        printf("%s ", strs[j]);
    }
    return 0;
}
