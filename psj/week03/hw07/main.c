#include <stdio.h>
#include <string.h>

int main(void) {
    while (1) {
        char str[100];
        printf("Enter a string: \n");
        scanf("%s", str);
        printf("You entered %s. length=%zu\n", str, strlen(str));
        if (strcmp(str, "hello") == 0) {
            printf("Yes it is hello. Bye.\n");
            break;
        } else {
            printf("No it is not hello\n");
        }
    }
    return 0;
}
