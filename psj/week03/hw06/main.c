#include <stdio.h>
#include <string.h>

int main(void) {
    char str[100];
    printf("Enter a string: \n");
    scanf("%s", str);
    int i;
    for (i = 0; i < strlen(str); i += 1) {
        printf("%c\n", str[i]);
    }
    return 0;
}
