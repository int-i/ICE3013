#include <stdio.h>
#include <string.h>

int main(void) {
    char str[100];
    printf("Enter a string: \n");
    scanf("%s", str);
    printf("The length is %zu\n", strlen(str));
    return 0;
}
