#include <stdio.h>
#include <string.h>

int main(void) {
    char y[100];
    printf("enter a string\n");
    scanf("%s", y); // error becuase y has no space for a string
    printf("you entered %s\n", y);
    return 0;
}
