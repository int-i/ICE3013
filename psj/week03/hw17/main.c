#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_COUNT 100
#define MAX_NAME_LENGTH 100

int main(void) {
    char* names[MAX_INPUT_COUNT];
    char name[MAX_NAME_LENGTH];
    int i = 0;
    while (1) {
        printf("Enter a name\n");
        fgets(name, MAX_NAME_LENGTH, stdin);
        if (strcmp(name, "bye\n") == 0) {
            break;
        }
        names[i] = (char*) malloc(sizeof(char) * MAX_NAME_LENGTH);
        strcpy(names[i], name);
        i += 1;
    }
    printf("There were %d names.\n", i);
    for (int j = 0; j < i; j += 1) {
        printf("%s", names[j]);
    }
    return 0;
}
