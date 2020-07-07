#include <stdio.h>
#include <string.h>

int main(void) {
    char str[100];
    printf("Enter a string: \n");
    scanf("%s", str);
    printf("After copying and changing the first letter\n");
    char a[100];
    char b[100];
    char c[100];
    strcpy(a, str);
    a[0] = 'a';
    printf("%s\n", a);
    strcpy(b, str);
    b[0] = 'b';
    printf("%s\n", b);
    strcpy(c, str);
    c[0] = 'c';
    printf("%s\n", c);
    return 0;
}
